#include <marketData/interestRateCurves/estimators/costFunctions/FirstDerivativeCostFunction.hpp>

namespace julian {
namespace ir {

  /** \brief returns Q matrix, the quadratic term of optimization cost function
   *
   * Numerical derivative of a function f can be approximated using following formula
   * \f[\frac{df(x)}{dx}|_{x=x_i} \approx \frac{f(x_{i+1}) - f(x_{i})}{x_{i+1}-x_{i}}\f]
   * If \f$F = [f(x_1), f(x_2), ..., f(x_n)]\f$
   * then differencing of function can be presented in matrix form:
   * \f[\frac{dF}{dX} = X^{-1} \times D_{1} \times F\f]
   * where:
   *
   * \f[ D_{1} = 
   * \begin{bmatrix}
   *  0   & 0  & 0 & \dots & 0  & 0 \\
   *  -1  & 1  & 0 & \dots & 0  & 0 \\
   *  0   & -1 & 1 & \dots & 0  & 0 \\
   *  0   &  0 &-1 & \dots & 0  & 0 \\
   *  \hdotsfor{6} \\
   *  0   & 0  & 0 & \dots & -1 & 1
   *  \end{bmatrix}\f]
   *
   *   * \f[ X = 
   * \begin{bmatrix}
   *  x_{1} - x_{0}  & 0              & 0             & \dots & 0  & 0 \\
   *  0              & x_{2} - x_{1}  & 0             & \dots & 0  & 0 \\
   *  0              & 0              & x_{3} - x_{2} & \dots & 0  & 0 \\
   *  0              & 0              & 0             & \dots & 0  & 0 \\
   *  \hdotsfor{6} \\
   *  0              & 0              & 0             &\dots  & 0  & x_{n}-x_{n-1}
   *  \end{bmatrix}\f]
   *
   * To calculate Q matrix InterpolatedCurve is needed,because we need the gird dates and the size of the curve
   *
   * \param input InterpolatedCurve for which Q matrix is calculated
   */
  arma::mat FirstDerivativeCostFunction::giveQmatrix(const InterpolatedCurve& input) const {
    arma::mat q = CostFunctionDecorator::giveQmatrix(input);
    arma::mat d = matrixD( input.getSize(), 1);
    arma::mat x = matrixX( input, 1);
      
    arma::mat ret =  d.t() * x.t() * x * d;
      
    return q + weight_ * ret;;
  }

  /** \brief returns C vector
   *
   * Method does not modify the C vector obtained from decorated class.
   */
  arma::mat FirstDerivativeCostFunction::giveCvector(const InterpolatedCurve& input) const {
    return CostFunctionDecorator::giveCvector(input);
  }

  /** \brief returns curve as vector of doubles
   *
   * \f[ Cost = \int^{tN}_{t0} \Big(\frac{df(x)}{dx}\Big)^2 dx\f]
   *
   * InterpolatedCurve may be represented by different
   */
  double FirstDerivativeCostFunction::calculateCost(const InterpolatedCurve& input) const {
    double ret = CostFunctionDecorator::calculateCost(input);

    arma::mat d = matrixD( input.getSize(), 1);
    arma::mat x = matrixX( input, 1);

    arma::mat costMatrix = weight_ * d.t() * x.t() * x * d;
    std::vector<double> r = CostFunctionDecorator::giveSmoothedCurve(input);
    arma::mat r_(r);

    arma::mat a = r_.t() * costMatrix * r_;

    return ret + a(0, 0);
  }

  /** \brief virtual copy constructor
   */
  FirstDerivativeCostFunction* FirstDerivativeCostFunction::clone() const {
    return new FirstDerivativeCostFunction(*this);
  }

}  // namespace ir
}  // namespace julian
