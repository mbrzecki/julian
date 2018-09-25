#include <mathematics/interpolation/flatForward.hpp>
#include <cmath>
#include <boost/assert.hpp>

namespace julian {
  /** \brief Performs interpolation
    
      This operator returns value of interpolant at the point x_init. This value is obtained by flat forward interpolation on the basis of given arguments (vector x)  and corresponding values (vector y).  
	  If x_init is outside the interval defined by the first and the last element of vector of the arguments operator returns error. 
 
  */
  double FlatForward::operator()(const std::vector<double>& x,const std::vector<double>& y,const double& x_int) const {
    BOOST_ASSERT_MSG(x_int >= x.at(0),"Cannot return value for argument lower then first nodal point ");
    BOOST_ASSERT_MSG(x_int <= x.at(x.size()-1),"Cannot return value for argument higher then last nodal point ");
    BOOST_ASSERT_MSG(x.size() == y.size(), "Size of x and is different then size of  y vector. ");  
    if(x_int == x.at(0)) {
      return y.at(0);
    } else {
      std::vector<double>::const_iterator low;
      low = std::lower_bound (x.begin(), x.end(), x_int); 
      return y.at(low - x.begin());
    }
  }

  /** \brief Virtual copy constructor
    
      Method is an implementation of virtual copy constructor.
  */
  FlatForward* FlatForward::clone() const {
    return new FlatForward(*this);
  }

  int unsigned FlatForward::getMinSize() const {
    return 2;
  }
  
  /** \brief Name of a class
    
      Method returns string that containing information about class. 
  */
  std::string FlatForward::info() const {
    return "FlatForward";
  }
}  // namespace julian
