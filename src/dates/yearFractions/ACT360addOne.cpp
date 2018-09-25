#include <string>
#include <dates/yearFractions/ACT360addOne.hpp>

namespace julian {

  /**\brief Calculates year fraction
     
     Method calculates the year fraction on the basis of two dates.
  */

  double ACT360addOne::operator()(const Date& d1, const Date& d2) const {
    return ( ( d2.getN() - d1.getN() + 1) / 360.0 );
  }

  /** \brief Virtual copy constructor
      
      Virtual copy constructor of the ACT360addOne class
  */
  ACT360addOne* ACT360addOne::clone() const {
    return new ACT360addOne(*this);
  }

  /** \brief Name of a class
      
      Method returns string that containing information about class. 
  */
  std::string ACT360addOne::info() const {
    return "ACT360+1";
  }
}  // namespace julian
