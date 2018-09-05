#include <mathematics/interpolation/flatBackward.hpp>
#include <cmath>
#include <boost/assert.hpp>

namespace julian {
  
  /** \brief Performs interpolation
      
      This operator returns value of interpolant at the point x_init. This value is obtained by flat backward interpolation on the basis of given arguments (vector x)  and corresponding values (vector y).  
	  If x_init is outside the interval defined by the first and the last element of vector of the arguments operator returns error. 
      
  */
  double FlatBackward::operator()(const std::vector<double>& x,const std::vector<double>& y,const double& x_int) const {
    BOOST_ASSERT_MSG(x_int >= x.at(0),"Cannot return value for argument lower then first nodal point ");
    BOOST_ASSERT_MSG(x_int <= x.at(x.size()-1),"Cannot return value for argument higher then last nodal point ");
    BOOST_ASSERT_MSG(x.size() == y.size(), "Size of x and is different then size of  y vector. ");  
    if(x_int == x.front()) {
      return y.front();
    } else {
      std::vector<double>::const_iterator low;
      low = std::lower_bound (x.begin(), x.end(), x_int); 
      return y.at(low - x.begin()-1);
    }
  }
  
  /** \brief Virtual copy constructor
      
      Method is an implementation of virtual copy constructor.
  */
  FlatBackward* FlatBackward::clone() const {
    return new FlatBackward(*this);
  }


  int unsigned FlatBackward::getMinSize() const {
    return 2;
  }
  
  /** \brief Name of a class
      
      Method returns string that containing information about class. 
  */
  std::string FlatBackward::info() const {
    return "FlatBackward";
  }
}  // namespace julian
