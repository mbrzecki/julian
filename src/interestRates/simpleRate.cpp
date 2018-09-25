#include <interestRates/SimpleRate.hpp>
#include <iostream>

namespace julian {

  /** \brief Calculates future value
      
      Method calculates the future value of 1 currency unit on the basis of annualized interest rate and interest accrual period.
      \f[\textrm{Future Value} = 1 + \textrm{Interest Rate} \times \textrm{Accrual Time}\f] 
  */
  double SimpleRate::getCapitalization(double interest_rate, double accrual_time) const {
    return 1.0 + interest_rate * accrual_time;
  }

  /**
     \brief Calculates interest rate
     
     Method calculates the annualized interest rate on the basis of future value of interest rate value and interest accrual period.
     \f[\textrm{Interest Rate} = \frac{\textrm{Future Value}-1}{\textrm{Accrual Time}}\f] 
  */
  double SimpleRate::getRate(double future_value, double accrual_time) const {
    if (accrual_time == 0.0)
      return 0.0;
    return (future_value - 1) / accrual_time;
  }


  /** \brief Virtual copy constructor
      
      Method is an implementation of virtual copy constructor.
  */
  SimpleRate* SimpleRate::clone() const {
    return new SimpleRate(*this);
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, SimpleRate&) {
    s << "Compounding: Simple";
    return s;
  }

  /** \brief Info about class
      
      Method returns string that containing information about class. 
  */
  std::string SimpleRate::info() const {
    return "Simple";
  }
}  // namespace julian
