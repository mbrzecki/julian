#include <instruments/linear/FRA.hpp>
#include <iomanip>
#include <utils/formatters.hpp>

namespace julian {

  /** \brief constructor
   *
   */
  FRA::FRA(Date trade_date, Date fixing_date, Date value_date, Date maturity_date, InterestRate rate, double notional, double fixing, double quoting):
    trade_date_(trade_date), fixing_date_(fixing_date), value_date_(value_date), maturity_date_(maturity_date),
    rate_(rate), notional_(notional), fixing_(fixing), quote_(quoting) {
    fixed_leg_.addCashFlow( FixedCashFlow(value_date, maturity_date, maturity_date, quote_, notional, rate, false) );
    floating_leg_.addCashFlow( FloatingCashFlow(fixing_date, maturity_date, value_date, maturity_date, maturity_date, - notional, 0.0, 1.0, false) );
  }

  /**
   * \brief changes quoting of the FRA
   *
   */
  void FRA::changeQuoting(double input) {
    quote_ = input;
    fixed_leg_.updateCashFlows(quote_, rate_);
  }

  /**
   * \brief Method calibrate is used by root finding estimator. 
   *
   * The estimator calibrates curve by finding the root of this method. 
   */
  double FRA::calibrate(const SmartPointer<ir::Curve>& calibrated) {
    return -notional_ * calibrated->DF(value_date_) +  (notional_ + fixed_leg_[0]->getCF()) * calibrated->DF(maturity_date_);
  }
  
  /**
   * \brief Method calibrate is used by root finding estimator. 
   *
   * The estimator calibrates curve by finding the root of this method. 
   */
  double FRA::calibrate(const SmartPointer<ir::Curve>&  ,const SmartPointer<ir::Curve>& ,const SmartPointer<ir::Curve>& calibrated) {
    double ret = -notional_ * calibrated->DF(value_date_) +  (notional_ + fixed_leg_[0]->getCF()) * calibrated->DF(maturity_date_);
    return ret;
  }

  /** \brief calculates price of FRA by summing the discounted CFs of fixed and floating leg
   *
   *  Method uses different curve to estimate forward rates and different curve to calculate discount factors
   *
   *  \param discounting discounting curve
   *  \param projecting projecting curve
   */
  double FRA::price(const SmartPointer<ir::Curve>& discounting, const SmartPointer<ir::Curve>& projecting, const SmartPointer<ir::Curve>& , const SmartPointer<ir::Curve>&) {
    if (discounting->getValuationDate() > fixing_date_) {
      floating_leg_.updateCashFlows(fixing_, rate_);
    } else {
      floating_leg_.updateCashFlows(projecting);
    }
    double fl = floating_leg_.prize(discounting);
    double fx = fixed_leg_.prize(discounting);
    return fl + fx;
  }

  /** \brief calculates price of FRA by summing the discounted CFs of fixed and floating leg
   *
   *  Method uses the same curve to estimate forward rates and different curve to calculate discount factors
   *
   *  \param c interest rates curve
   *  \returns returns the price of FRA 
   */
  double FRA::price(const SmartPointer<ir::Curve>& c) {
    return price(c, c, c, c);
  }

  /**
   * \brief returns maturity of FRA 
   */
  Date FRA::getDate() const {
    return maturity_date_;
  }

  /**
   * \brief Returns a name of instrument: FRA 
   */
  std::string FRA::info() const {
    return "FRA";
  }
  
  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s,FRA& fra) {       
    s << "Object: ForwardRateAgreement"
      << "\nTradeDate: " << fra.trade_date_
      << "\nFixingDate: " << fra.fixing_date_
      << "\nValueDate: " << fra.value_date_
      << "\nMaturityDate: " << fra.maturity_date_
      << "\nNotional: " << formatter::currency(fra.notional_)
      << "\nRate: " << fra.rate_
      << "\nQuote: " << std::setprecision(4) << std::fixed << formatter::percentage(fra.quote_);

    return s;
  }

  /** \brief prints price and CFs of FRA using different curve for discounting and projecting forward rates
   */
  void FRA::valuation(const SmartPointer<ir::Curve>& discounting, const SmartPointer<ir::Curve>& projecting, const SmartPointer<ir::Curve>&, const SmartPointer<ir::Curve>&) {
    std::cout << *this << std::endl;
    std::cout << "\nFixed CF\n"
	      << value_date_ << " " << fixed_leg_[0]->getCF() * discounting->DF(value_date_, maturity_date_) << " " << discounting->DF(value_date_)  << "\n\n" 
	      << "Floating CF\n"
	      << value_date_ << " " << floating_leg_[0]->getCF() * discounting->DF(value_date_, maturity_date_) << " " << discounting->DF(value_date_)  << "\n\n"; 
    std::cout << "Price: " << price(discounting, projecting, projecting, projecting) << "\n\n";  
  }

  /** \brief prints price and CFs of FRA using the same curve for discounting and projecting forward rates
   */
  void FRA::valuation(const SmartPointer<ir::Curve>& c) {
    valuation(c, c, c, c);
  }

  /**
   * \brief Implies quoting of benchmark instrument from interest rate curves provided. 
   *
   */
  double FRA::getParRate(const SmartPointer<ir::Curve>&,const SmartPointer<ir::Curve>&,const SmartPointer<ir::Curve>& calibrated) {
    return calibrated->fwdRate(value_date_, maturity_date_, rate_);
  }

  /** \brief Returns quoting
   */
  double FRA::getQuoting() {    
    return quote_;
  }

  /** \brief Virtual copy constructor
   */
  FRA* FRA::clone() const {
    return new FRA(*this);
  }

  /**
   * \brief Returns the sets of cashflows associated with FRA
   * 
   * \note Second Cash Flow Vector is empty
   */
  std::pair<CashFlowVector, CashFlowVector> FRA::getCFs() const {
    CashFlowVector fix;
    CashFlowVector flo;
    FixedCashFlow cf1(value_date_, value_date_, value_date_   , 0.0,                  - notional_,true );
    FixedCashFlow cf2(value_date_, value_date_, maturity_date_, fixed_leg_[0]->getCF(), notional_,true );

    fix.addCashFlow(cf1);
    fix.addCashFlow(cf2);

    std::pair<CashFlowVector, CashFlowVector> cfs_pair(fix,flo);
    return cfs_pair;
  }

  InterestRate FRA::getInterestRate() const {
    return rate_;
  }

}  // namespace julian
