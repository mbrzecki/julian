#include <instruments/FixedCashFlow.hpp>
#include <utils/formatters.hpp>
#include <iomanip>
#include <utils/formatters.hpp>
namespace julian {

  /** \brief constructor
   *
   *  Creates FixedCashFlow basing on provided dates and amount
   */
  FixedCashFlow::FixedCashFlow(Date start, Date end, Date payment, double amount,
			       double notional, bool notional_is_paid) {
    accrual_start_ = start;
    accrual_end_ = end;
    payment_date_ = payment;
    amount_ = amount;
    notional_ = notional;
    notional_is_paid_ = notional_is_paid;
  }

  /** \brief constructor
   *
   *  Creates FixedCashFlow basing on provided dates, interest rate and quoting  
   */
  FixedCashFlow::FixedCashFlow(Date start, Date end, Date payment,double quote,
			       double notional, InterestRate rate, bool notional_is_paid) {
    accrual_start_ = start;
    accrual_end_ = end;
    payment_date_ = payment;
    notional_ = notional;
    notional_is_paid_ = notional_is_paid;
    amount_ = notional*rate.coupon(start, end, quote);
  }

  /** \brief discounts the cashflow
     *
     *  Method discount the cashflow on the curve valuation date.  
     */
  double FixedCashFlow::price(const SmartPointer<ir::Curve>& disc) {
    return getCF() * disc->DF(payment_date_);
  }

  /** \brief virtual copy constructor 
   */
  FixedCashFlow* FixedCashFlow::clone() const {
    return new FixedCashFlow(*this);
  }

  /** \brief returns payment date
   */
  Date FixedCashFlow::getDate() const {
    return payment_date_;
  }

  /** \brief returns CF
   */
  double FixedCashFlow::getCF() const {
    if (notional_is_paid_) {
      return notional_ + amount_;
    }
    return amount_;
  }

  /** \brief prints discounted the cashflow
   *
   *  Method calculates discounted cashflow on the curve valuation date and then prints it 
   */
  double FixedCashFlow::value(const SmartPointer<ir::Curve>& disc) {
    double df = disc->DF(payment_date_);
    if (df > 0 ) {
      std::cout << payment_date_
		<< std::setw(18) << formatter::currency(this->getCF())
		<< std::setw(16) << std::setprecision(7) << df
		<< std::setw(16) << formatter::currency(df*this->getCF())  << "\n";
    }
    return df * this->getCF();
  }

  /** \brief calculates new CF value basing on quoting and interest rate provided
   *
   */    
  void FixedCashFlow::setCashFlow(double quote, const InterestRate& rate) {
    amount_ = notional_ * rate.coupon(accrual_start_, accrual_end_, quote);
  }

  /** \brief sets new CF value
   */
  void FixedCashFlow::setCashFlow(double amount) {
    amount_ = amount;
  }

  /** \brief Increases CF by provided amount 
   */
  void FixedCashFlow::addToCashFlow(double amount) {
    amount_ += amount;
  }

  /** \brief Increases CF by amount calculated using quote and rate provided
   */
  void FixedCashFlow::addToCashFlow(double quote, InterestRate rate) {
    amount_ += notional_ * rate.coupon(accrual_start_, accrual_end_, quote);
  }

  /** \brief returns notional
   */
  double FixedCashFlow::getNotional() const {
    return notional_;
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, FixedCashFlow& f) {
    s << f.payment_date_ << "\t" << formatter::currency(f.getCF());
    return s;
  }
}  // namespace julian
