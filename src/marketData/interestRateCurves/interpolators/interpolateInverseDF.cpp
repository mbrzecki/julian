#include <marketData/interestRateCurves/interpolators/interpolateInverseDF.hpp>
#include <string>

namespace julian {
namespace ir {

  /**
     \brief Calulate inputs form DF
       
     Swap curve maintains interest rate term structure as vector of default factors. The discount factors and appropriate dates are past from swap curve to interpolator. 
     Before interpolation procedure is performed,this method inverses DF.

     \param DF2 Discount factor for date2
  */
  double InterpolateInverseDF::operator()(double,double DF2,InterestRate, Date, Date, Date) const {
    return 1 / DF2;
  }

  /**
     \brief Calculate DF form result of interpolation
       
     Because class implements interpolating discount factor, this method inverses received result of interpolation.
       
     \param x result of interpolation
  */

  double InterpolateInverseDF::getDF(double x, InterestRate ,Date ,Date ) const {
    return 1 / x;
  }

  /** \brief Virtual copy constructor
    
      Method is an implementation of virtual copy constructor.
  */
  InterpolateInverseDF* InterpolateInverseDF::clone() const {
    return new InterpolateInverseDF(*this);
  }

  /** \brief Info about class
    
      Method returns string that containing information about class. 
  */
  std::string InterpolateInverseDF::info() const {
    return "inverse_DF";
  }

}  // namespace ir
}  // namespace julian
