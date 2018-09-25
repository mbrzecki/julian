#include <string>
#include <dates/yearFractions/ACT360.hpp>

namespace julian {

  /**
     \brief Calculates year fraction
     
     Method calculates the year fraction on the basis of two dates.
  */
  double ACT360::operator()(const Date& date1, const Date& date2) const {
    return ( ( date2.getN() - date1.getN() ) / 360.0 );
  }

  /** \brief Virtual copy constructor
   * 
   * Virtual copy constructor of the ACT360 class
   */
  ACT360* ACT360::clone() const {
    return new ACT360(*this);
  }

  /** \brief Name of a class
      
      Method returns string that containing information about class. 
  */
  std::string ACT360::info() const {
    return "ACT360";
  }

}
