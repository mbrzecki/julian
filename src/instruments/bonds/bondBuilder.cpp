#include <instruments/bonds/BondBuilder.hpp>
#include <instruments/CashFlowBuilder.hpp>

namespace julian {

  /** \brief default constructor
   */
  BuildBond::BuildBond(){
    reset();
  }

  /** \brief sets notional
   */
  BuildBond& BuildBond::withNotional(const double& input){
    notional_ = input;
    return *this;
  }

  /** \brief sets calendar
   */
  BuildBond& BuildBond::usingCalendar(const Calendar& input){
    calendar_ = input;
    return *this;
  }

  /** \brief sets start date
   */  
  BuildBond& BuildBond::withStartDate(const Date& input){
    start_date_ = input;
    return *this;
  }

  /** \brief sets commence of trading date
   */  
  BuildBond& BuildBond::withCommenceOfTradingDate(const Date& input){
    commence_of_trading_date_ = input;
    return *this;
  }

  /** \brief sets maturity date
   */  
  BuildBond& BuildBond::withMaturityDate(const Date& input){
    maturity_date_ = input;
    return *this;
  }

  
  /** \brief sets maturity
   */ 
  BuildBond& BuildBond::withTenor(const Tenor& input){
    maturity_ = input;
    return *this;
  }

  /** \brief sets frequency of payment
   */ 
  BuildBond& BuildBond::withFrequencyOfPayment(const Frequency& input){
    payment_frequency_ = input;
    return *this;
  }

  /** \brief sets bond coupon
   */ 
  BuildBond& BuildBond::withCoupon(const double& input){
    coupon_ = input;
    return *this;
  }

  /** \brief sets face value for zero-coupon bond
   */     
  BuildBond& BuildBond::withFaceValue(const double& input) {
    face_amount_ = input;
    return *this;
  }
  
  /** \brief sets bond margin
   */ 
  BuildBond& BuildBond::withMargin(const double& input) {
    margin_ = input;
    return *this;
  }
  
  /** \brief sets interest rate convention
   */ 
  BuildBond& BuildBond::withInterestRate(const InterestRate& input){
    rate_ = input;
    return *this;
  }

  /** \brief resets inputs to default values
   *
   * * Notional is set to 100.0.
   * * Coupon is set to 0.0
   *
   * \remarks method used in constructor so keep it non-virtual
   */
  void BuildBond::reset(){
    notional_ = 100.0;

    maturity_ = 0*YEAR;
    coupon_ = 0.0;
    margin_ = 0.0;
    payment_frequency_ = Frequency::NOFREQ;
  }

  /** \brief calculates 
   *
   */
  void BuildBond::datesCalculation() {
    BOOST_ASSERT_MSG(start_date_.isValid(),
		     "Start date was not declared.");
    if (!commence_of_trading_date_.isValid())
      commence_of_trading_date_ = calendar_.getSpot(start_date_);

    if ( maturity_.getNumberOfUnits() !=0 && (!maturity_date_.isValid()))
      maturity_date_ = calendar_.settlementDate(start_date_, maturity_);
  }

  /** \brief  builds FixedIncomeBond on the basis of provided inputs.
   *
   */
  BuildBond::operator FixedIncomeBond() {
    datesCalculation();
    
    CashFlowVector cfs = CashFlowBuilder()
      .usingCalendar(calendar_)
      .withStartDate(start_date_)
      .withEndDate(maturity_date_)
      .withNotional(notional_)
      .withInterestRate(rate_)
      .withQuote(coupon_)
      .withPaymentFrequency(payment_frequency_)
      .withExchangeOfNotional(true)
      .buildFixedCashFlows();

    FixedIncomeBond bond(start_date_, maturity_date_, notional_, coupon_, rate_,cfs , payment_frequency_);

    reset();
    return bond;
  }

  /** \brief builds FixedIncomeBond on the basis of provided inputs.
   *
   */
  BuildBond::operator FloatingRateBond() {
    datesCalculation();

    CashFlowVector temp_cfs = CashFlowBuilder()
      .usingCalendar(calendar_)
      .withStartDate(start_date_)
      .withEndDate(maturity_date_)
      .withNotional(notional_)
      .withInterestRate(rate_)
      .withAdditiveMargin(margin_)
      .withPaymentFrequency(payment_frequency_)
      .withExchangeOfNotional(false)
      .buildFloatingCashFlows();
    CashFlowVector temp_cfs2 = CashFlowBuilder()
      .usingCalendar(calendar_)
      .withStartDate(start_date_)
      .withEndDate(maturity_date_)
      .withNotional(notional_)
      .withInterestRate(rate_)
      .withAdditiveMargin(margin_)
      .withPaymentFrequency(payment_frequency_)
      .withExchangeOfNotional(true)
      .buildFloatingCashFlows();
    CashFlowVector cfs;
    FixedCashFlow first(start_date_, commence_of_trading_date_,commence_of_trading_date_, 0.0, -notional_, true);
    cfs.addCashFlow(first);
    for (int i = 1; i < temp_cfs.size()-1; i++) {
      cfs.addCashFlow(temp_cfs[i]);
    }
    cfs.addCashFlow(temp_cfs2[temp_cfs2.size()-1]);
    FloatingRateBond bond(start_date_, maturity_date_, notional_, margin_, rate_, cfs , payment_frequency_);
    
    reset();
    return bond;
  }

  /** \brief builds ZeroCouponBond on the basis of provided inputs.
   *
   */
  BuildBond::operator ZeroCouponBond() {
    datesCalculation();
    InterestRate rate;
    CashFlowVector cfv;
    cfv.addCashFlow(FixedCashFlow(start_date_, start_date_,    start_date_,   0.0, -face_amount_*notional_, rate, true));
    cfv.addCashFlow(FixedCashFlow(start_date_, maturity_date_, maturity_date_,0.0,  notional_, rate, true));
    ZeroCouponBond bond(start_date_, maturity_date_, notional_, cfv);
    reset();
    return bond;
  }
}  // namespace julian
