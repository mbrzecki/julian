#include <marketData/interestRateCurves/estimators/costFunctions/SecondDerivativeCostFunction.hpp>
#include <vector>

namespace julian {
namespace ir {

    /** \brief returns Q matrix, the quadratic term of optimization cost function
     *
     * Numerical derivative of a function f can be approximated using following formula
     * \f[\frac{d^2f(x)}{dx^2}|_{x=x_i} \approx \frac{f(x_{i+1}) - 2f(x_{i}) + f(x_{i-1})}{x_{i+1}-x_{i-1}}\f]
     * If \f$F = [f(x_1), f(x_2), ..., f(x_n)]\f$
     * then differencing of function can be presented in matrix form:
     * \f[\frac{dF}{sX} = X^{-1} \times D_{2} \times F\f]
     * where:
     *
     * \f[ D_{2} = 
     * \begin{bmatrix}
     *  0   & 0  & 0 & 0 & \dots & 0  & 0 \\
     *  0   & 0  & 0 & 0 & \dots & 0  & 0 \\
     *  1   &-2  & 1 & 0 & \dots & 0  & 0 \\
     *  0   &  1 &-2 & 1 & \dots & 0  & 0 \\
     *  \hdotsfor{7} \\
     *  0   & 0  & 0 & \dots & 1 & -2 & 1
     *  \end{bmatrix}\f]
     *
     *   * \f[ X = 
     * \begin{bmatrix}
     *  x_{2} - x_{0}  & 0              & 0             & \dots & 0  & 0 \\
     *  0              & x_{3} - x_{1}  & 0             & \dots & 0  & 0 \\
     *  0              & 0              & x_{4} - x_{2} & \dots & 0  & 0 \\
     *  0              & 0              & 0             & \dots & 0  & 0 \\
     *  \hdotsfor{6} \\
     *  0              & 0              & 0             &\dots  & 0  & x_{n}-x_{n-2}
     *  \end{bmatrix}\f]
     *
     * To calculate Q matrix InterpolatedCurve is needed,because we need the gird dates and the size of the curve
     *
     * \param input InterpolatedCurve for which Q matrix is calculated
     */
  arma::mat SecondDerivativeCostFunction::giveQmatrix(const InterpolatedCurve& input) const {
    arma::mat q = CostFunctionDecorator::giveQmatrix(input);
    arma::mat d = matrixD(input.getSize(), 2);
    arma::mat x = matrixX(input, 2);

    arma::mat ret = weight_ * d.t() * x.t() * x * d;
    return q + ret;
  }

  /** \brief returns C vector
   *
   * Method does not modify the C vector obtained from decorated class.
   */
  arma::mat SecondDerivativeCostFunction::giveCvector(const InterpolatedCurve& input) const {
    return CostFunctionDecorator::giveCvector(input);
  }

  /** \brief returns curve as vector of doubles
   *
   * \f[ Cost = \int^{tN}_{t0} \Big(\frac{df^2(x)}{dx^2}\Big)^2 dx\f]
   *
   * InterpolatedCurve may be represented by different
   */
  double SecondDerivativeCostFunction::calculateCost(const InterpolatedCurve& input) const {
    double ret = CostFunctionDecorator::calculateCost(input);
    arma::mat d = matrixD( input.getSize(), 2);
    arma::mat x = matrixX( input, 2);

    arma::mat costMatrix = weight_ * d.t() * x.t() * x * d;
    std::vector<double> r = CostFunctionDecorator::giveSmoothedCurve(input);
    arma::mat r_(r);

    arma::mat a = r_.t() * costMatrix * r_;

    return ret + a(0,0);
  }

  /** \brief virtual copy constructor
   */
  SecondDerivativeCostFunction* SecondDerivativeCostFunction::clone() const {
    return new SecondDerivativeCostFunction(*this);
  }
}  // namespace ir
}  // namespace julian
