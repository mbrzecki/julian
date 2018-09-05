#include <marketData/interestRateCurves/interpolators/interpolateDF.hpp>

namespace julian {
namespace ir {

  /**
     \brief Calculates inputs form DF
       
     Swap curve maintains interest rate term structure as vector of default factors. The discount factors and appropriate dates are past from swap curve to interpolator. 
     Because class implements interpolating discount factor, all what it does is forwarding received DF2.
       
     \param DF2 Discount factor for date2
  */
  double InterpolateDF::operator()(double, double DF2, InterestRate, Date, Date, Date) const {
    return DF2;
  }

    /**
       \brief Calculate DF form result of interpolation
       
       Because class implements interpolating discount factor, this method forwards received result of interpolation unchanged.
       
       \param x result of interpolation

     */
  double InterpolateDF::getDF(double x, InterestRate, Date, Date) const {
    return x;
  }

    /** \brief Virtual copy constructor
	
	Method is an implementation of virtual copy constructor.
    */
  InterpolateDF* InterpolateDF::clone() const {
    return new InterpolateDF(*this);
  }

    /** \brief Info about class

	Method returns string that containing information about class. 
    */
  std::string InterpolateDF::info() const {
    return "Discount_Factors";
  }

  }  // namespace ir
}  // namespace julian
