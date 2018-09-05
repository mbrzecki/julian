#ifndef JULIAN_SECONDDERIVATIVECOSTFUNCTION_HPP
#define JULIAN_SECONDDERIVATIVECOSTFUNCTION_HPP

#include <marketData/interestRateCurves/estimators/costFunctions/CostFunctionDecorator.hpp>
#include <marketData/interestRateCurves/interpolatedCurve.hpp>
#include <armadillo>

namespace julian {
namespace ir {
      /**
   * @file   SecondDerivativeCostFunction.hpp
   * @brief  File contains implementation of SecondDerivativeCostFunction
   */
  /** \ingroup irCurveCost
   * \brief Implements the second order derivative term of cost function
   *  
   *  \f[Cost_{f} =a \int^{tN}_{t0} \Big(\frac{df(x)}{dx}\Big)^2 dx +  \underline{b \int^{T}_t \Big(\frac{df^2(x)}{dx^2}\Big)^2 dx} \f]
   *
   *  The integral is evaluated numerically:
   * \f[ \int^{tN}_{t0} \Big(\frac{df^2(x)}{dx^2}\Big)^2 dx \approx \sum^{i=N-2}_{i=0}\Big(\frac{x(t_{i+2})- 2x(t_{i+1}) + x(t_{i})}{(t_{i+2}-t_i)^2}\Big)^2 = x^T D^T_2D_2 x = x^T Q x\f]
   * where \f$D_2\f$ is a matrix representing second order differentiation and \f$t_i\f$ are grid dates of the curve.
   *
   */
  
  class SecondDerivativeCostFunction: public CostFunctionDecorator {
  public:
  /** \brief Constructor
  */
    explicit SecondDerivativeCostFunction(SmartPointer<SmootherCostFunction> c, double weight = 1.0): CostFunctionDecorator(c), weight_(weight) {};
      
    virtual arma::mat giveQmatrix(const InterpolatedCurve&) const;
    virtual arma::mat giveCvector(const InterpolatedCurve&) const;
    virtual double calculateCost(const InterpolatedCurve&) const;
    virtual SecondDerivativeCostFunction* clone() const;  
    virtual ~SecondDerivativeCostFunction(){};
  private:
    double weight_;   /*!< \brief Weight assigned to second order term (see parameter \b b in equation above) */
  };
}  // namespace ir
}  // namespace julian
#endif
