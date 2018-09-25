#include <interestRates/compoundedRate.hpp>
#include <cmath>
#include <iostream>

namespace julian {
  /** \brief Calculates future value
      
      Method calculates the future value of 1 currency unit on the basis of annualized interest rate and interest accrual period.
      \f[\textrm{Future Value} = (1 + \textrm{Interest Rate})^{\textrm{Accrual Period}}\f] 
  */
  double CompoundedRate::getCapitalization(double r, double t) const {
    return pow( (1 + r), t);
  }

  /** \brief Calculates interest rate
      
      Method calculates the annualized interest rate on the basis of future value of interest rate value and interest accrual period.
      \f[\textrm{Interest Rate} = \sqrt[\textrm{Accrual Period}]{\textrm{Future Value}}-1\f]
  */
  double CompoundedRate::getRate(double x, double t) const {
    return pow(x, 1/t)-1;
  }

  /** \brief Virtual copy constructor
      
      Method is an implementation of virtual copy constructor.
  */
  CompoundedRate* CompoundedRate::clone() const {
    return new CompoundedRate(*this);
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, CompoundedRate&) {
    s << "Compounding: Compounded";
    return s;
  }

  /** \brief Info about class
      
      Method returns string that containing information about class. 
  */
  std::string CompoundedRate::info() const {
    return "Compounded";
  }
}  // namespace julian
