#include <mathematics/interpolation/linearInterpolation.hpp>
#include <boost/assert.hpp>
#include <vector>
#include <iostream>

namespace julian {

/** \brief Performs interpolation
    
    This operator returns value of interpolant at the point x_init. This value is obtained by linear interpolation on the basis of given arguments (vector x)  and corresponding values (vector y). 
    If x_init is outside the interval defined by the first and the last element of vector of the arguments operator returns error. 
  */

  double LinearInterpolation::operator()(const std::vector<double>& x,const std::vector<double>& y,const double& x_int) const {
    BOOST_ASSERT_MSG(x_int >= x.front(), "Cannot return value for argument lower then first nodal point ");
    BOOST_ASSERT_MSG(x_int <= x.back(), "Cannot return value for argument higher then last nodal point ");
    BOOST_ASSERT_MSG(x.size() == y.size(), "Size of x and is different then size of  y vector. ");
    if (x_int == x.front()) {
      return y.front();
    } else if ( x_int == x.back() ) {
      return y.back();
    } else {
      
      std::vector<double>::const_iterator low;
      low = std::lower_bound(x.begin(), x.end(), x_int);
      unsigned int position = low - x.begin();

      return (y.at(position-1) * ( x.at(position) - x_int) + y.at(position) * (x_int - x.at(position-1)) ) / (x.at(position) - x.at(position-1));
    }
  }

  
  unsigned int LinearInterpolation::getMinSize() const {
    return 2;
  }
  
  /** \brief Virtual copy constructor
    
      Method is an implementation of virtual copy constructor.
  */
  LinearInterpolation* LinearInterpolation::clone() const {
    return new LinearInterpolation(*this);
  }

  /** \brief Name of a class
      
      Method returns string that containing information about class. 
  */
  std::string LinearInterpolation::info() const {
    return "Linear";
  }
}  // namespace julian
