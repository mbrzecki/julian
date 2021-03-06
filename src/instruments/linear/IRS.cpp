#include <instruments/linear/IRS.hpp>
#include <iomanip>
#include <utils/formatters.hpp>
#include <mathematics/numericalAlgorithms/derivativeRootFinder.hpp>
namespace julian {

  /** \brief changes quoting of the IRS
   */
  void IRS::changeQuoting(double input) {
    quoting_ = input;
    fixed_leg_.updateCashFlows(quoting_, fixed_leg_rate_);
  }

  /** \brief Method calibrate is used by root finding estimator. 
   *
   * The estimator calibrates curve by finding the root of this method.
   *
   * Calibrated curve is used to price the fixed leg. 
   */
  double IRS::calibrate(const SmartPointer<ir::Curve>& calibrated) {
    return fixed_leg_.prize(calibrated);
  }
  
  /** \brief Method calibrate is used by root finding estimator. 
   *
   * The estimator calibrates curve by finding the root of this method.
   *
   * Calibrated curve is used as projection curve for floating leg.
   * Discounting curve is used to prize fixed and floating leg. 
   */
  double IRS::calibrate(const SmartPointer<ir::Curve>& discounting ,const SmartPointer<ir::Curve>& ,const SmartPointer<ir::Curve>&  calibrated) {
    floating_leg_.updateCashFlows(calibrated);
    return fixed_leg_.prize(discounting) + floating_leg_.prize(discounting);
  }

  /** \brief calculates price of IRS by summing the discounted CFs
   *
   * Projecting curve is used to estimate CFs generated by floating leg. 
   * Discounting curve is used to discount CFs of both leg.
   *
   *  \param discounting discounting curve
   *  \param projecting projecting curve
   */
  double IRS::price(const SmartPointer<ir::Curve>& discounting,const SmartPointer<ir::Curve>& projecting, const SmartPointer<ir::Curve>&, const SmartPointer<ir::Curve>&) {
    floating_leg_.updateCashFlows(projecting);
    return fixed_leg_.prize(discounting) + floating_leg_.prize(discounting);
  }

  /** \brief calculates price of IRS by summing the discounted CFs
   *  \param c discounting curve
   */
  double IRS::price(const SmartPointer<ir::Curve>& c) {
    return price(c,c,c,c);
  }

  /**
   * \brief returns maturity of IRS
   */
  Date IRS::getDate() const {
    return maturity_date_;
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, IRS& irs) {
    std::string fixed;
    switch(irs.fixed_leg_freq_) {
    case NOFREQ: fixed = "NotDefined";break;
    case MONTHLY: fixed = "Monthly";break;
    case QUARTERLY: fixed = "Quarter";break;
    case SEMIANNUALLY: fixed = "Semiannul";break;
    case ANNUALLY: fixed = "Annual";break;
    }
    
    std::string floating;
    switch(irs.floating_leg_freq_) {
    case NOFREQ: fixed = "NotDefined";break;
    case MONTHLY: fixed = "Monthly";break;
    case QUARTERLY: floating = "Quarter";break;
    case SEMIANNUALLY: floating = "Semiannual";break;
    case ANNUALLY: floating = "Annual";break;
    }
  
    s << "Object: InterestRateSwap"
      << "\nTradeDate: " << irs.trade_date_
      << "\nStartDate: " << irs.start_date_
      << "\nMaturity: " << irs.maturity_date_ 
      << "\nNotional: " << formatter::currency(irs.notional_)
      << "\nQuoting: " << std::fixed << std::setprecision(4) << formatter::percentage(irs.quoting_)
      << "\nFixedLeg: " << fixed << " " << irs.fixed_leg_rate_
      << "\nFloatingLeg: "<< floating << " " << irs.floating_leg_rate_ << "\n\n";

    return s;
  }

  
  /** \brief prints price and CFs of IRS
   */
  void IRS::valuation(const SmartPointer<ir::Curve>& discounting,const SmartPointer<ir::Curve>& projecting, const SmartPointer<ir::Curve>&, const SmartPointer<ir::Curve>&) {
    floating_leg_.updateCashFlows(projecting);

    std::cout << "Fixed Leg Cash Flows\n";
    double price_fix = fixed_leg_.valuation(discounting);
    std::cout << "Price of fixed leg: " << formatter::currency(price_fix); 
    std::cout << "\n\nFloating Leg Cash Flows\n";
    double price_flo = floating_leg_.valuation(discounting);
    std::cout << "Price of floating leg: " << formatter::currency(price_flo) << "\n";
    std::cout << "\nPrice of IRS: " << formatter::currency(price_flo + price_fix) << "\n\n";
  }

  /** \brief prints price and CFs of IRS
   */
  void IRS::valuation(const SmartPointer<ir::Curve>& c) {
    valuation(c, c, c, c);
  }

  /** \brief Returns quoting
   */
  double IRS::getQuoting() {
    return quoting_;
  }

  /** \brief Virtual copy constructor
   */
  IRS* IRS::clone() const {
    return new IRS(*this);
  }

  /** \brief Implies quoting of benchmark instrument from interest rate curves provided. 
   *
   */
  double IRS::getParRate(const SmartPointer<ir::Curve>& discounting,const  SmartPointer<ir::Curve>& ,const SmartPointer<ir::Curve>& ) {
    auto dates = fixed_leg_.getDates();
    double den = 0.0;
    for (unsigned int i = 1 ; i < dates.size(); i++) {
      den += discounting->DF(dates.at(i)) * fixed_leg_rate_.yf(dates.at(i-1), dates.at(i));
    }
    return (discounting->DF(dates.front()) - discounting->DF(dates.back())) / den;
  }

  /** \brief Returns the sets of cashflows associated with IRS
   */
  std::pair<CashFlowVector, CashFlowVector> IRS::getCFs() const {
    std::pair<CashFlowVector, CashFlowVector> cfs_pair(fixed_leg_, floating_leg_);
    return cfs_pair;
  }

  /** \brief Returns interest rates convention of fixed leg
   */
  InterestRate IRS::getInterestRate() const {
    return fixed_leg_rate_;
  }

  
  /**
   * \brief Returns a name of instrument: FRA 
   */
  std::string IRS::info() const {
    return "IRS";
  }
  
}  // namespace julian
