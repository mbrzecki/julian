#include <marketData/interestRateCurves/interpolators/interpolateLogOfDF.hpp>
#include <cmath>

namespace julian {
namespace ir {

  /**
     \brief Calculates inputs form DF
   
     Swap curve maintains interest rate term structure as vector of default factors. The discount factors and appropriate dates are past from swap curve to interpolator.
	 Before interpolation procedure is performed,this method calculates natural logarithm of DF.
   
     \param DF2 Discount factor 
  */
  double InterpolateLogarithmOfDF::operator()(double, double DF2, InterestRate, Date, Date, Date) const {
    return log(DF2);
  }

  /**
     \brief Calculate DF form result of interpolation
   
     Because class implements interpolating discount factor, this method calculates the exponential of interpolation results.
   
     \param x result of interpolation
  */
  double InterpolateLogarithmOfDF::getDF(double x, InterestRate, Date, Date) const {
    return exp(x);
  }

  /** \brief Virtual copy constructor
    
      Method is an implementation of virtual copy constructor.
  */
  InterpolateLogarithmOfDF* InterpolateLogarithmOfDF::clone() const {
    return new InterpolateLogarithmOfDF(*this);
  }

  /** \brief Info about class
    
      Method returns string that containing information about class. 
  */
  std::string InterpolateLogarithmOfDF::info() const {
    return "logarithm_of_DF";
  }
}  // namespace ir
}  // namespace julian

