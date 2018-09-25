#include <instruments/FloatingCashFlow.hpp>
#include <utils/utils.hpp>
#include <utils/formatters.hpp>
#include <iomanip>

namespace julian {

  /** \brief constructor
   *
   *  Creates FloatingCashFlow basing on provided dates and amount
   */
  FloatingCashFlow::FloatingCashFlow(Date acc_start, Date acc_end, Date fix_start,
				     Date fix_end, Date payment, double n,
				     double additive_margin, double multiplicative_margin, bool notional_is_paid):
    accrual_start_(acc_start), accrual_end_(acc_end), fixing_start_(fix_start), fixing_end_(fix_end), payment_date_(payment),
    notional_(n), additive_margin_(additive_margin), multiplicative_margin_(multiplicative_margin), notional_is_paid_(notional_is_paid)  {}

  /** \brief discounts the cashflow
   *
   *  Method discount the cashflow on the curve valuation date.  
   */
  double FloatingCashFlow::price(const SmartPointer<ir::Curve>& disc) {
    if (disc->getValuationDate() == payment_date_)
      return 0.0;
    return amount_ * disc->DF(payment_date_);
  }
  
  /** \brief returns payment date
   */
  Date FloatingCashFlow::getDate() const {
    return payment_date_;
  }

  /** \brief prints discounted cashflows
   *
   *  Method calculates discounted cashflow on the curve valuation date and then prints it 
   */
  double FloatingCashFlow::value(const SmartPointer<ir::Curve>& disc) {
    double df = disc->DF(payment_date_);
    if (df > 0.0) {
      std::cout << payment_date_ 
		<< std::setw(18) << formatter::currency(amount_)
		<< std::setw(16) << std::setprecision(7) << df
		<< std::setw(16) << formatter::currency(amount_ * df)
		<< std::endl;
    }
    return df * amount_;
  }

  /** \brief virtual copy constructor 
   */
  FloatingCashFlow* FloatingCashFlow::clone() const {
    return new FloatingCashFlow(*this);
  }

  /** \brief sets the cash flow
   */
  void FloatingCashFlow::setCashFlow(double input) {
    amount_ = input;
  }

  /** \brief calculates new CF value basing on quoting and interest rate provided
   */ 
  void FloatingCashFlow::setCashFlow(double quote, const InterestRate& rate) {
    if (notional_is_paid_) {
      amount_ = notional_ * (additive_margin_ + multiplicative_margin_ * rate.capitalization(accrual_start_, accrual_end_, quote));
    } else {
      amount_ = notional_ * (additive_margin_ + multiplicative_margin_ * rate.coupon(accrual_start_, accrual_end_, quote));
    }
  }

  /** \brief sets new CF value basing on interest rate curve
   */
  void FloatingCashFlow::setCashFlow(const SmartPointer<ir::Curve>& c) {
    Date val_date = c->getValuationDate();
    if (val_date <= fixing_start_) {
      if (notional_is_paid_) {
	amount_ = notional_ * (additive_margin_ +  multiplicative_margin_ * c->capitalization(accrual_start_, accrual_end_)) ;
      } else {
	amount_ = notional_ * (additive_margin_ +  multiplicative_margin_ * c->coupon(accrual_start_, accrual_end_)) ;
      }
    }
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, FloatingCashFlow& cf) {
    s << cf.payment_date_ << "\t" << formatter::currency(cf.amount_);
    return s;
  }

  /** \brief returns CF
   */
  double FloatingCashFlow::getCF() const {
    return amount_;
  }

  /** \brief returns notional
   */
  double FloatingCashFlow::getNotional() const {
    return notional_;
  }
  
}  // namespace julian
