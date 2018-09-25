#include <mathematics/interpolation/quadraticInterpolation.hpp>
#include <boost/assert.hpp>

namespace julian {
/** \brief Performs interpolation
    
    This operator returns value of interpolant at the point x_init. This value is obtained by quadratic interpolation on the basis of given arguments (vector x)  and corresponding values (vector y).  
	If x_init is outside the interval defined by the first and the last element of vector of the arguments operator returns error. 
 
 */
  double QuadraticInterpolation::operator()(const std::vector<double>& x,const std::vector<double>& y,const double& x_int) const {
    double result;

    BOOST_ASSERT_MSG(x_int >= x.at(0),"Cannot return value for argument lower then first nodal point ");
    BOOST_ASSERT_MSG(x_int <= x.at(x.size()-1),"Cannot return value for argument higher then last nodal point ");
    BOOST_ASSERT_MSG(x.size() == y.size(), "Size of x and is different then size of  y vector. ");
    if(x_int == x.at(0)) {
      result = y.at(0);
    } else {
      std::vector<double>::const_iterator low;
      low = std::lower_bound (x.begin(), x.end(), x_int); 
      
      unsigned int pos = low - x.begin();
      
      double x1 = x.at(pos-1);
      double y1 = y.at(pos-1);
      double x2 = x.at(pos);
      double y2 = y.at(pos);
    
      result = y1 + (y2 - y1) * (x_int * x_int - x1 * x1) / (x2 * x2 - x1 * x1);
    }
    return result;
  }

  /** \brief Virtual copy constructor
    
      Method is an implementation of virtual copy constructor.
  */
  QuadraticInterpolation* QuadraticInterpolation::clone() const {
    return new QuadraticInterpolation(*this);
  }

  
  int unsigned QuadraticInterpolation::getMinSize() const {
    return 2;
  }
  
  /** \brief Name of a class
      
      Method returns string that containing information about class. 
  */
  std::string QuadraticInterpolation::info() const {
    return "Quadratic";
  }

}  // namespace julian
