#include <marketData/interestRateCurves/estimators/costFunctions/SmoothZeroCouponRates.hpp>

namespace julian {
namespace ir {

  /** \brief returns matrix filled with zeros
   */
  arma::mat SmoothZeroCouponRates::giveQmatrix(const InterpolatedCurve& curve) const {
    return arma::mat(curve.getSize(), curve.getSize(), arma::fill::zeros);
  }

  /** \brief returns vector filled with zeros
   */
  arma::mat SmoothZeroCouponRates::giveCvector(const InterpolatedCurve& curve) const {
    return arma::mat(curve.getSize(), 1, arma::fill::zeros);
  }

  /** \brief returns 0.0, as the true cost is calculated by decorators
   */
  double SmoothZeroCouponRates::calculateCost(const InterpolatedCurve&) const {
    return 0.0;
  }

  /** \brief returns vector of zero-coupon rates
   */
  std::vector<double> SmoothZeroCouponRates::giveSmoothedCurve(const InterpolatedCurve& curve) const {
    return curve.getRates();
  }

  /** \brief updates the curve with vector of zero-coupon rates
   */
  void SmoothZeroCouponRates::updateSmoothedCurve(InterpolatedCurve& c, const std::vector<double>& r) const {
    c.setRates(r);
  }


  /** \brief virtual copy constructor
   */
  SmoothZeroCouponRates* SmoothZeroCouponRates::clone() const{
    return new SmoothZeroCouponRates(*this);
  }  
}  // namespace ir
}  // namespace julian
