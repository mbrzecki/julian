#include <instruments/bonds/floatingRateBond.hpp>
#include <mathematics/numericalAlgorithms/derivativeRootFinder.hpp>
#include <mathematics/numericalAlgorithms/bracketingRootFinder.hpp>
#include <utils/formatters.hpp>
#include <iomanip>

namespace julian {

  /** \brief bond valuation
   * \param curve Interest rate curve used to discount CFs
   */
  void FloatingRateBond::valuation(const SmartPointer<ir::Curve>& curve) const {
    auto cfs = cash_flows_;
    cfs.updateCashFlows(curve);
    cfs.valuation(curve);
    std::cout << "\nPrice " << formatter::currency(cfs.prize(curve));
    std::cout << std::endl;
  }

  /** \brief bond valuation
   * \param discounting_curve Interest rate curve used to discount CFs
   * \param projection_curve Interest rate curve used to project future CFs
   */
  void FloatingRateBond::valuation(const SmartPointer<ir::Curve>& discounting_curve,
				   const SmartPointer<ir::Curve>& projection_curve) const {
    auto cfs = cash_flows_;
    cfs.updateCashFlows(projection_curve);
    cfs.valuation(discounting_curve);

    std::cout << "\nPrice " << formatter::currency(cfs.prize(discounting_curve));
  }

  /** \brief prize bond
   * \param curve Interest rate curve used to discount CFs
   * \return price of bonds
   */
  double FloatingRateBond::prize(const SmartPointer<ir::Curve>& curve) const {
    auto cfs = cash_flows_;
    cfs.updateCashFlows(curve);
    return cfs.prize(curve);
  }

  /** \brief prize bond
   * \param discounting_curve Interest rate curve used to discount CFs
   * \param projection_curve Interest rate curve used to estimate CFs
   * \return price of bonds
   */
  double FloatingRateBond::prize(const SmartPointer<ir::Curve>& discounting_curve,
				 const SmartPointer<ir::Curve>& projection_curve) const {
    auto cfs = cash_flows_;
    cfs.updateCashFlows(projection_curve);
    return cfs.prize(discounting_curve);
  }

  /** \brief returns the bond's principal  
   */
  double FloatingRateBond::getPrincipal() const {
    return principal_;
  }

  /** \brief returns the bond's maturity  
   */
  Date FloatingRateBond::getDate() const {
    return maturity_date_;
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, FloatingRateBond& b) {
    std::string freq;
  
    switch(b.payment_frequency_) {
    case 0:  freq = "NotGiven";break;
    case 1:  freq = "Monthly";break;
    case 3:  freq = "Quaterly";break;
    case 6:  freq = "Semiannually";break;
    case 12: freq = "Annually";break; 
    }
  
    s << "Object: FloatingRateBond"
      << "\nStartDate: " << b.issue_date_ 
      << "\nMaturity: "<< b.maturity_date_
      << "\nCouponFrequency: " << freq
      << "\nNotional: " << formatter::currency(b.principal_) 
      << "\nMargin " << std::setprecision(5) << std::fixed << formatter::percentage(b.margin_)
      << " (" << b.rate_ << ")\n";

    return s;
  }

  /** \brief virtual copy constructor
   */
  FloatingRateBond* FloatingRateBond::clone() const {
    return new FloatingRateBond(*this);
  }
}  // namespace julian
