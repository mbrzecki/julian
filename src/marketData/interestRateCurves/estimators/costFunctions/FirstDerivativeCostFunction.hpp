#ifndef JULIAN_FIRSTDERIVATIVECOSTFUNCTION_HPP
#define JULIAN_FIRSTDERIVATIVECOSTFUNCTION_HPP

#include <marketData/interestRateCurves/estimators/costFunctions/CostFunctionDecorator.hpp>
#include <marketData/interestRateCurves/interpolatedCurve.hpp>
#include <armadillo>

namespace julian {
namespace ir {
      /**
   * @file   FirstDerivativeCostFunction.hpp
   * @brief  File contains implementation of FirstDerivativeCostFunction.
   */
  /** \ingroup irCurveCost
   * \brief Implements the first order derivative term of cost function
   *  
   * 
   * \f[Cost_{f} = \underline{a \int^{tN}_{t0} \Big(\frac{df(x)}{dx}\Big)^2 dx} + b \int^{tN}_{t0} \Big(\frac{df^2(x)}{dx^2}\Big)^2 dx \f]
   *
   *  The integral is evaluated numerically:
   * \f[ \int^{tN}_{t0} \Big(\frac{df(x)}{dx}\Big)^2 dx \approx \sum^{i=N-1}_{i=0}\Big(\frac{x(t_{i+1}) - x(t_{i})}{t_{i+1}-t_i}\Big)^2 = x^T D^T_1D_1 x = x^T Q x\f]
   * where \f$D_1\f$ is a matrix representing first order differentiation and \f$t_i\f$ are grid dates of the curve.
   *
   * If this factor is used as the only one in the estimation process of the curve, 
   * it is equivalent to the estimating  the curve with the smallest length.
   */
  
	 
  class FirstDerivativeCostFunction: public CostFunctionDecorator  {
  public:
  /** \brief Constructor
  */
    explicit FirstDerivativeCostFunction(SmartPointer<SmootherCostFunction> c, double weight = 1.0):
      CostFunctionDecorator(c), weight_(weight) {};
      
    virtual arma::mat giveQmatrix(const InterpolatedCurve&) const;
    virtual arma::mat giveCvector(const InterpolatedCurve&) const;
    virtual double calculateCost(const InterpolatedCurve&) const;
      
    virtual FirstDerivativeCostFunction* clone() const;
    virtual ~FirstDerivativeCostFunction(){};
  private:
    double weight_;  /*!< \brief Weight assigned to first order term (see parameter \b a in equation above) */
  };
}  // namespace ir
}  // namespace julian
#endif
