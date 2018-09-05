#include <mathematics/interpolation/steffenInterpolation.hpp>
#include <boost/assert.hpp>
#include <gsl/gsl_spline.h>

namespace julian {

    /** \brief Performs interpolation
     */  
  
  double SteffenInterpolation::operator()(const std::vector<double>& x,const std::vector<double>& y,const double& x_int) const {

    BOOST_ASSERT_MSG(x_int >= x.at(0),"Cannot return value for argument lower then first nodal point ");
    BOOST_ASSERT_MSG(x_int <= x.at(x.size()-1),"Cannot return value for argument higher then last nodal point ");
    BOOST_ASSERT_MSG(x.size() == y.size(), "Size of x and is different then size of  y vector. "); 
    gsl_interp_accel *acc = gsl_interp_accel_alloc ();
    gsl_spline *interpolation = gsl_spline_alloc (gsl_interp_steffen, x.size());
  
    gsl_spline_init (interpolation, &x[0], &y[0], x.size());
    double result = gsl_spline_eval (interpolation, x_int, acc);
    
    gsl_spline_free (interpolation);
    gsl_interp_accel_free (acc);

    return result;
  }

  /** \brief Virtual copy constructor
    
      Method is an implementation of virtual copy constructor.
  */
  
  SteffenInterpolation* SteffenInterpolation::clone() const {
    return new SteffenInterpolation(*this);
  }

  
  unsigned int SteffenInterpolation::getMinSize() const {
    return gsl_interp_type_min_size(gsl_interp_steffen);
  }
  
  /** \brief Name of a class
      
      Method returns string that containing information about class. 
  */
  
  std::string SteffenInterpolation::info() const {
    return "Steffen";
  }
}  // namespace julian
