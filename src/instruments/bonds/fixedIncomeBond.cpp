#include <instruments/bonds/fixedIncomeBond.hpp>
#include <mathematics/numericalAlgorithms/derivativeRootFinder.hpp>
#include <mathematics/numericalAlgorithms/bracketingRootFinder.hpp>
#include <utils/formatters.hpp>
#include <iomanip>

namespace julian {
  /** \brief bond valuation
   * \param curve Interest rate curve used to discount CFs
   */
  void FixedIncomeBond::valuation(const SmartPointer<ir::Curve>& curve) const {
    cash_flows_.valuation(curve);
    std::cout << "\nPrice " << formatter::currency(cash_flows_.prize(curve));
  }

  /** \brief bond valuation
   * \param curve Interest rate curve used to discount CFs
   */
  void FixedIncomeBond::valuation(const SmartPointer<ir::Curve>& curve,
				  const SmartPointer<ir::Curve>&) const {
    cash_flows_.valuation(curve);
    std::cout << "\nPrice " << formatter::currency(cash_flows_.prize(curve));
    std::cout << std::endl;
  }
  

  /** \brief prize bond
   * \param curve Interest rate curve used to discount CFs
   * \return price of bonds
   */
  double FixedIncomeBond::prize(const SmartPointer<ir::Curve>& curve) const {
    return cash_flows_.prize(curve);
  }
  /** \brief prize bond
   * \param curve Interest rate curve used to discount CFs
   * \remark second curve is not used
   * \return price of bonds
   */
  double FixedIncomeBond::prize(const SmartPointer<ir::Curve>& curve,
				const SmartPointer<ir::Curve>&) const {
    return cash_flows_.prize(curve);
  }

  /** \brief returns the bond's principal  
   */
  double FixedIncomeBond::getPrincipal() const {
    return principal_;
  }

  /** \brief returns the bond's maturity  
   */
  Date FixedIncomeBond::getDate() const {
    return maturity_date_;
  }

  /** \brief returns the coupon  
   */
  double FixedIncomeBond::getCoupon() const {
    return coupon_;
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, FixedIncomeBond& b) {
    std::string freq;
    switch(b.payment_frequency_) {
    case 0:  freq = "NotGiven"; break;
    case 1:  freq = "Monthly"; break;
    case 3:  freq = "Quaterly"; break;
    case 6:  freq = "Semiannually"; break;
    case 12: freq = "Annually"; break;
    }

    s << "Object: FixedIncomeBond"
      << "\nStartDate: " << b.issue_date_
      << "\nMaturity: "<< b.maturity_date_
      << "\nCouponFrequency: " << freq
      << "\nNotional: " << formatter::currency(b.principal_)
      << "\nCoupon: " << std::setprecision(5) << std::fixed
      << formatter::percentage(b.coupon_) << " (" << b.rate_ << ")\n";

    return s;
  }

  /** \brief virtual copy constructor
   */
  FixedIncomeBond* FixedIncomeBond::clone() const {
    return new FixedIncomeBond(*this);
  }
}  // namepsace julian
