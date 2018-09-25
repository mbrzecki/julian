#include <instruments/linear/deposit.hpp>
#include <iomanip>
#include <utility>
#include <utils/formatters.hpp>

namespace julian {

  /** \brief constructor
   *
   */
  Deposit::Deposit(Date trade_date, Date start_date, Date end_date, InterestRate rate, double notional, double quoting):
    trade_date_(trade_date), rate_(rate), quoting_(quoting) {
    cfs_.addCashFlow(FixedCashFlow(start_date, start_date, start_date, 0, - notional, true));
    cfs_.addCashFlow(FixedCashFlow(start_date, end_date, end_date, quoting, notional, rate, true));
  }

  /** \brief calculates price of deposit by summing the discounted CFs
      \param c discounting curve
   */
  double Deposit::price(const SmartPointer<ir::Curve>& c) {
    return cfs_.prize(c);
  }

  /** \brief calculates price of deposit by summing the discounted CFs
      \param c discounting curve
   */
  double Deposit::price(const SmartPointer<ir::Curve>& c, const SmartPointer<ir::Curve>& ,const SmartPointer<ir::Curve>& ,const SmartPointer<ir::Curve>&) {
    return price(c);
  }

  /**
   * \brief Method calibrate is used by root finding estimator. 
   *
   * The estimator calibrates curve by finding the root of this method. 
   */
  double Deposit::calibrate(const SmartPointer<ir::Curve>& ,const SmartPointer<ir::Curve>& ,const SmartPointer<ir::Curve>& calibrated) {
    return price(calibrated);
  }

  /**
   * \brief Method calibrate is used by root finding estimator. 
   *
   * The estimator calibrates curve by finding the root of this method. 
   */
  double Deposit::calibrate(const SmartPointer<ir::Curve>& calibrated) {
    return price(calibrated);
  }
  
  /**
   * \brief returns maturity of deposit 
   */
  Date Deposit::getDate() const {
    return cfs_[1]->getDate();
  }

  /**
   * \brief changes quoting of the deposit
   *
   */
  void Deposit::changeQuoting(double input) {
    quoting_ = input;
    cfs_.updateCashFlows(input, rate_);
  }

  /**
   * \brief Returns interest rates convention of deposit
   */
  InterestRate Deposit::getInterestRate() const {
    return rate_;
  }

  /**
   * \brief Returns the sets of cashflows associated with deposit
   * 
   * \note Second Cash Flow Vector is empty
   */
  std::pair<CashFlowVector, CashFlowVector> Deposit::getCFs() const {
    CashFlowVector cfs_temp;
    std::pair<CashFlowVector, CashFlowVector> ret(cfs_, cfs_temp);
    return ret;
  }

  /**
   * \brief Implies quoting of benchmark instrument from interest rate curves provided. 
   *
   */
  double Deposit::getParRate(const SmartPointer<ir::Curve>& ,
			     const SmartPointer<ir::Curve>& ,
			     const SmartPointer<ir::Curve>& calibrated) {
    return calibrated->fwdRate(cfs_[0]->getDate(), cfs_[1]->getDate(), rate_);
  }

  /** \brief Returns quoting
   */
  double Deposit::getQuoting() {
    return quoting_;
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, Deposit& d) {
    Date sd = d.cfs_[0]->getDate();
    Date ed = d.cfs_[1]->getDate();

    s << "Object: Deposit"
      << "\nTradeDate: " << d.trade_date_
      << "\nStartDate: " << sd 
      << "\nMaturity: " << ed 
      << "\nNotional: " << formatter::currency(- d.cfs_[0]->getCF())
      << "\nRate: " << std::setprecision(5) << formatter::percentage(d.quoting_)
      << " (" << d.rate_ << ")\n";

    return s;
  }

  /** \brief prints price and CFs of deposit using curve provided
   */
  void Deposit::valuation(const SmartPointer<ir::Curve>& curve, const SmartPointer<ir::Curve>&, const SmartPointer<ir::Curve>&, const SmartPointer<ir::Curve>&) {
    this->valuation(curve);
  }

  /** \brief prints price and CFs of deposit
   */
  void Deposit::valuation(const SmartPointer<ir::Curve>& curve) {
    std::cout << *this << "\n";
    std::cout << "Date"
	      << std::setw(23) << "CF"
	      << std::setw(15) << "DF "
	      << std::setw(14) << "DCF\n";
    cfs_.valuation(curve);
    std::cout << "Value of deposit: "
	      << formatter::currency(price(curve))
	      << "\n\n";
  }
  /** \brief returns the name of instrument: Deposit
   */
  std::string Deposit::info() const {
    return "Deposit";
  }
  
  /** \brief Virtual copy constructor
   */
  Deposit* Deposit::clone() const {
    return new Deposit(*this);
  }

}  // namespace julian
