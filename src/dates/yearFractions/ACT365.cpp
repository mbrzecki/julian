#include <string>
#include <dates/yearFractions/ACT365.hpp>

namespace julian {

  /**
     Method calculates the year fraction on the basis of two dates.
  */
  double ACT365::operator()(const Date& date1, const Date& date2) const {     
    return ( (date2.getN() - date1.getN() ) / 365.0);
  }

  /** Method is an implementation of virtual copy constructor.
   */
  ACT365* ACT365::clone() const {
    return new ACT365(*this);
  }

  /** Method returns string that containing information about class. 
   */
  std::string ACT365::info() const {
    std::string s = "ACT365";
    return s;
  }
}
