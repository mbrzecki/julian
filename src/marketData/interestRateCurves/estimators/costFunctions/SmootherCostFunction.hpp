#ifndef JULIAN_SMOOTHERCOSTFUNCTION_HPP
#define JULIAN_SMOOTHERCOSTFUNCTION_HPP

#include <marketData/interestRateCurves/interpolatedCurve.hpp>
#include <armadillo>

namespace julian {
namespace ir {
  /**
   * @file   SmootherCostFunction.hpp
   * @brief  File contains interface of cost function used by interest rate curve smoothers.
   */
   
  /** \ingroup irCurveCost
   * \brief Interface for Smoother Cost Function decorator.
   *  
   * The SmootherCostFunction is used by ir::InterpolatedCurve estimators that base on optimization techniques.
   * SmootherCostFunction implements the cost function that is minimized in optimization algorithm. Generally the cost function $f(x)$ is given by formula
   * \f[Cost_{f} = a \int^{tN}_{t0} \Big(\frac{df(x)}{dx}\Big)^2 dx + b \int^{tN}_{t0} \Big(\frac{df^2(x)}{dx^2}\Big)^2 dx \f]
   * where:
   * * \f$x\f$ is a curve representation, it can be zero-coupon rate or forward rates. 
   * It is selected by using appropriate concrete component in decorator structure. Concrete Component is a class that contains basic behaviour that can be altered by decorators.
   *
   * * \f$a, b\f$ are weights, can be set to 0. These components and weights are set by selecting appropriate concrete decorator. 
   * Concrete Decorator is a class that altered alters the behaviour of Concrete Component.
   *
   * * \f$t0,tN\f$ are respectively  the earliest and the latest grid date of the curve
   *
   * If we want to estimate discounting curve by finding the shortest curve of zero-coupon rates, we simply choose the SmoothZeroCouponRates as concrete component 
   * and FirstDerivativeCostFunction as concrete decorator, as minimizing the integral \f$\int^{t0}_{tN} \Big(\frac{df(x)}{dx}\Big)^2 dx\f$ is equivalent to minimizing the integral
   * \f$\int^{tN}_{t0} \Big(\sqrt{1-\frac{df(x)}{dx}\Big)^2} dx\f$ which express the length of the curve. If we want to minimize the function variance we should choose the SecondDerivativeCostFunction 
   * as decorator class. Thanks to using the Decorator Pattern defining the cost function is flexible and simple.
   *
   * It is worth noting that algorithm does not evaluate integrals exactly. Numerical approximation is used. We calculate the first and second derivative numerically
   * \f[ \int^{tN}_{t0} \Big(\frac{df(x)}{dx}\Big)^2 dx \approx \sum^{i=N-1}_{i=0}\Big(\frac{x(t_{i+1}) - x(t_{i})}{t_{i+1}-t_i}\Big)^2 = x^T D^T_1D_1 x = x^T Q x\f]
   * where \f$D_1\f$ is a matrix representing first order differentiation and \f$t_i\f$ are grid dates of the curve.
   */
  
  class SmootherCostFunction {
  public:
    /** \brief constructor
     */
    SmootherCostFunction(){};

    /** \brief returns Q matrix, the quadratic term of optimization cost function
     */
    virtual arma::mat giveQmatrix(const InterpolatedCurve&) const = 0;

    /** \brief returns C vector, the linear term of optimization cost function
     */
    virtual arma::mat giveCvector(const InterpolatedCurve&) const = 0;

    /** \brief calculates value of cost function
     */
    virtual double calculateCost(const InterpolatedCurve&) const = 0;

    /** \brief returns curve as vector of doubles
     *
     */
    virtual std::vector<double> giveSmoothedCurve(const InterpolatedCurve&) const = 0;

    /** \brief updates the curve as with the vector of doubles
     */
    virtual void updateSmoothedCurve(InterpolatedCurve&,const std::vector<double>&) const = 0;

    /** \brief virtual copy constructor
     */
    virtual SmootherCostFunction* clone() const = 0;

    /** \brief destructor
     */
    virtual ~SmootherCostFunction(){};
      
  private:
  };
}  // namespace ir
}  // namespace julian
#endif
