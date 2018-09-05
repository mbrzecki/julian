#include <mathematics/interpolation/cubicInterpolation.hpp>
#include <boost/assert.hpp>

namespace julian {
/** \brief Performs interpolation
    
    This operator returns value of interpolant at the point x_init. This value is obtained by cubic interpolation on the basis of given arguments (vector x)  and corresponding values (vector y). 
	If x_init is outside the interval defined by the first and the last element of vector of the arguments operator returns error. 
 
 */
  double CubicInterpolation::operator()(const std::vector<double>& x,const std::vector<double>& y,const double& x_int) const {  
    BOOST_ASSERT_MSG(x_int >= x.front(),"Cannot return value for argument lower then first nodal point ");
    BOOST_ASSERT_MSG(x_int <= x.back(),"Cannot return value for argument higher then last nodal point ");
    BOOST_ASSERT_MSG(x.size() == y.size(), "Size of x and is different then size of  y vector. ");
    if (x_int == x.front())
      return y.front();
    else {
      std::vector<double>::const_iterator low;
      low = std::lower_bound (x.begin(), x.end(), x_int); 

      unsigned int pos = low - x.begin(); 
      double x1 = x.at(pos-1);
      double x2 = x.at(pos);
    
      return y.at(pos-1) + (y.at(pos) - y.at(pos-1)) * (x_int * x_int * x_int - x1 * x1 * x1) / (x2 * x2 * x2 - x1 * x1 * x1);
    }
  }

  /** \brief Virtual copy constructor
      
      Method is an implementation of virtual copy constructor.
  */
  CubicInterpolation* CubicInterpolation::clone() const   {
    return new CubicInterpolation(*this);
  }


  int unsigned CubicInterpolation::getMinSize() const {
    return 2;
  }
  
  /** \brief Name of a class
      
      Method returns string that containing information about class. 
  */
  std::string CubicInterpolation::info() const {
    return "Cubic";
  }
}  // namespace julian
