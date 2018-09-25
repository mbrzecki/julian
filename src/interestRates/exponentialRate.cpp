#include <interestRates/ExponentialRate.hpp>
#include <cmath>
#include <iostream>

namespace julian {

  /**
     \brief Calculates interest rate
     
     Method calculates the annualized interest rate on the basis of future value of interest rate value and interest accrual period.
     \f[\textrm{Interest Rate} = \frac{ln(\textrm{Future Value})}{\textrm{Accrual Time}}\f]

  */
  double ExponentialRate::getRate(double future_value, double accrual_time) const {
    if ( accrual_time == 0 )
      return 0;
    return (log(future_value) / accrual_time);
  }

  /** \brief Calculates future value
      
      Method calculates the future value of 1 currency unit on the basis of annualized interest rate and interest accrual period.
      \f[\textrm{Future Value} = e^{\textrm{Interest Rate} \times \textrm{Accrual Period}}\f] 
  */
  double ExponentialRate::getCapitalization(double interest_rate, double accrual_time) const {
    return exp(interest_rate*accrual_time);
  }

  /** \brief Virtual copy constructor
      
      Method is an implementation of virtual copy constructor.
  */
  ExponentialRate* ExponentialRate::clone() const {
    return new ExponentialRate(*this);
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, ExponentialRate&) {
    s << "Compounding: Exponential";
    return s;
  }

  /** \brief Info about class
      
      Method returns string that containing information about class. 
  */
  std::string ExponentialRate::info() const {
    return "Exponential";
  }
}  // namespace julian
