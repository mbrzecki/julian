#include <marketData/interestRateCurves/estimators/costFunctions/SmoothForwardRates.hpp>
#include <vector>

namespace julian {
namespace ir {
  /** \brief returns matrix filled with zeros
   */
  arma::mat SmoothForwardRates::giveQmatrix(const InterpolatedCurve& curve) const {
    return arma::mat(curve.getSize(), curve.getSize(), arma::fill::zeros);
  }
  
  /** \brief returns vector filled with zeros
   */
  arma::mat SmoothForwardRates::giveCvector(const InterpolatedCurve& curve) const {
    return arma::mat(curve.getSize(), 1, arma::fill::zeros);
  }

  /** \brief returns 0.0, as the true cost is calculated by decorators
   */
  double SmoothForwardRates::calculateCost(const InterpolatedCurve&) const {
    return 0.0;
  }

  /** \brief returns vector of forward rates
   */
  std::vector<double> SmoothForwardRates::giveSmoothedCurve(const InterpolatedCurve& curve) const {
    return curve.getFwdRates();
  }

  /** \brief updates the curve with vector of forward rates
   */
  void SmoothForwardRates::updateSmoothedCurve(InterpolatedCurve& c, const std::vector<double>& r) const {
    c.setFwdRates(r);
  }
  /** \brief virtual copy constructor
   */
  SmoothForwardRates* SmoothForwardRates::clone() const {
    return new SmoothForwardRates(*this);
  }

}  // namespace ir
}  // namespace julian
