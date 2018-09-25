#include <interestRates/fractionRate.hpp>
#include <cmath>
#include <iostream>

namespace julian {

  /** \brief Calculates future value
   *
   *  Method calculates the future value of 1 currency unit on the basis of annualized interest rate and interest accrual period.
   * \f[\textrm{Future Value} = (1 + \textrm{Interest Rate} \div \textrm{frequency} )^{\textrm{frequency} \times \textrm{Accrual Period}}\f] 
   *
   */

  double FractionRate::getCapitalization(double r, double t) const {
    return pow( (1 + r/ frequency_), t*frequency_);
  }

  /** \brief Calculates interest rate
      
      Method calculates the annualized interest rate on the basis of future value of interest rate value and interest accrual period.
      \f[\textrm{Interest Rate} = (\sqrt[\textrm{frequency}]{\textrm{Future Value}}-1) \times frequency\f]

  */
  double FractionRate::getRate(double fv, double t) const {
    return frequency_ * (pow(fv, 1/(t * frequency_))-1.0);
  }

  /** \brief Virtual copy constructor
      
      Method is an implementation of virtual copy constructor.
  */
  FractionRate* FractionRate::clone() const {
    return new FractionRate(*this);
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, FractionRate&) {
    s << "Compounding: Fraction Rate";
    return s;
  }

  /** \brief Info about class
      
      Method returns string that containing information about class. 
  */
  std::string FractionRate::info() const {
    return "FractionRate";
  }
}
