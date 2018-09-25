#include <marketData/interestRateCurves/interpolators/interpolateZCRate.hpp>
#include <string>

namespace julian {
namespace ir {

  /**
     \brief Calculates inputs form DF
       
     Swap curve maintains interest rate term structure as vector of default factors. The discount factors and appropriate dates are past from swap curve to interpolator. 
     Because class implements interpolating discount factor, all what it does is forwarding received DF2.
       
     \param DF2 Discount factor for date2
     \param r Interest rates needed to calculate zero coupon rate.
     \param today Today date needed to calculate YF
     \param d2 maturity date needed to calculate YF
  */
  double InterpolateZCRate::operator()(double ,double DF2,InterestRate r,Date today,Date ,Date d2) const {
    return r.zcRate(today,d2,DF2);
  }

  /**
     \brief Calculate DF form result of interpolation
       
     Because class implements interpolating discount factor, this method forwards received result of interpolation unchanged.
       
     \param x result of interpolation
     \param r Interest rates needed to calculate zero coupon rate.
     \param d1 Today date needed to calculate YF
     \param d2 maturity date needed to calculate YF
  */
  double InterpolateZCRate::getDF(double x, InterestRate r, Date d1, Date d2) const {
    return r.DF(d1,d2,x);
  }

  /** \brief Virtual copy constructor
	
      Method is an implementation of virtual copy constructor.
  */
  InterpolateZCRate* InterpolateZCRate::clone() const {
    return new InterpolateZCRate(*this);
  }

  /** \brief Info about class

      Method returns name of class 
  */
  std::string InterpolateZCRate::info() const {
    return "Zero_Coupon_Rates";
  }

}  // namespace ir
}  // namespace julian
