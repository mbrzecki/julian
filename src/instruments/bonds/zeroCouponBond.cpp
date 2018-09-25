#include <instruments/bonds/zeroCouponBond.hpp>
#include <utils/formatters.hpp>
#include <iomanip>

namespace julian {

  /** \brief returns the bond's principal  
   */
  double ZeroCouponBond::getPrincipal() const {
    return principal_;
  }

  /** \brief returns the bond's maturity  
   */
  Date ZeroCouponBond::getDate() const {
    return maturity_date_;
  }

  /** \brief prize bond
   * \param curve Interest rate curve used to discount CFs
   * \return price of bonds
   */
  double ZeroCouponBond::prize(const SmartPointer<ir::Curve>& curve) const {
    return cash_flows_.prize(curve);
  }

  /** \brief prize bond
   * \param curve Interest rate curve used to discount CFs
   * \return price of bonds
   */
  double ZeroCouponBond::prize(const SmartPointer<ir::Curve>& curve,
			       const SmartPointer<ir::Curve>&) const {
    return cash_flows_.prize(curve);
  }

  /** \brief bond valuation
   * \param curve Interest rate curve used to discount CFs
   */
  void ZeroCouponBond::valuation(const SmartPointer<ir::Curve>& curve) const {
    cash_flows_.valuation(curve);
    std::cout << "\nPrice " << formatter::currency(cash_flows_.prize(curve));
    std::cout << std::endl;
  }

  /** \brief bond valuation
   * \param curve Interest rate curve used to discount CFs
   */
  void ZeroCouponBond::valuation(const SmartPointer<ir::Curve>& curve,
				 const SmartPointer<ir::Curve>&) const {
    cash_flows_.valuation(curve);
    std::cout << "\nPrice " << formatter::currency(cash_flows_.prize(curve));
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, ZeroCouponBond& b) {
    s << "Object: ZeroCouponBond"
      << "\nStartDate: " << b.issue_date_
      << "\nMaturity: "<< b.maturity_date_
      << "\nNotional: " << formatter::currency(b.principal_) << std::endl;

  return s;
  }

  /** \brief virtual copy constructor
   */
  ZeroCouponBond* ZeroCouponBond::clone() const {
    return new ZeroCouponBond(*this);
  }

}  // namespace julian
