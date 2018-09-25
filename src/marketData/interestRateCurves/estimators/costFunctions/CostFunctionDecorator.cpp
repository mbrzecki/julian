#include <marketData/interestRateCurves/estimators/costFunctions//CostFunctionDecorator.hpp>
#include <boost/assert.hpp>
#include <vector>

namespace julian {
namespace ir {

  /** \brief returns Q matrix, the quadratic term of optimization cost function
   */
  arma::mat CostFunctionDecorator::giveQmatrix(const InterpolatedCurve& input) const {
    return cost_function_->giveQmatrix(input);
  }

  /** \brief returns C vector, the linear term of optimization cost function
   */
  arma::mat CostFunctionDecorator::giveCvector(const InterpolatedCurve& input) const {
    return cost_function_->giveCvector(input);
  }

  /** \brief calculates value of cost function
   */
  double CostFunctionDecorator::calculateCost(const InterpolatedCurve& input) const {
    return cost_function_->calculateCost(input);
  }

  /** \brief virtual copy constructor
   */
  CostFunctionDecorator* CostFunctionDecorator::clone() const {
    return new CostFunctionDecorator(*this);
  }

  /** \brief returns curve as vector of doubles
   *
   * InterpolatedCurve may be represented by different
   */
  std::vector<double> CostFunctionDecorator::giveSmoothedCurve(const InterpolatedCurve& input) const {
    return cost_function_->giveSmoothedCurve(input);
  }

  /** \brief updates the curve as with the vector of doubles
   */
  void CostFunctionDecorator::updateSmoothedCurve(InterpolatedCurve& c, const std::vector<double>& r) const {
    cost_function_->updateSmoothedCurve(c,r);
  }

  /** \brief Creates matrix representation of differential operator
   *
   * Numerical derivative of a function f can be approximated using following formula
   * \f[\frac{df(x)}{dx}|_{x=x_i} \approx \frac{f(x_{i+1}) - f(x_{i})}{x_{i+1}-x_{i}}\f]
   * If \f$F = [f(x_1), f(x_2), ..., f(x_n)]\f$
   * then differencing of function can be presented in matrix form"
   * \f[\frac{dF}{sX} = X^{-1} \times D_{1} \times F\f]
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
   * The second derivative can be calculated by analogy.
   *
   * This method calculates the D matrix.
   *
   * \param size Size of D matrix
   * \param derivative Order of derivative
   */
  arma::mat CostFunctionDecorator::matrixD(int size, int derivative) const {
    arma::mat t = trimatl(arma::mat(size, size, arma::fill::ones));
    t = arma::inv(t);
    arma::mat result = arma::mat(size, size, arma::fill::eye);
    for (int i = 0; i < derivative; i++) {
      result = result * t;
    }
    for (int i = 0; i < derivative; i++) {
      result.row(i) = arma::mat(1, size, arma::fill::zeros);
    }
    return result;
  }

  /** \brief Creates matrix representation of differential operator
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
   * The second derivative can be calculated by analogy.
   *
   * This method calculates the X matrix.
   *
   * \param c Curve which derivative we calculates 
   * \param order Order of derivative
   */
  arma::mat CostFunctionDecorator::matrixX(const InterpolatedCurve& c, int order) const {
    std::vector<Date> dates = c.getDates();
    arma::mat result(c.getSize(), c.getSize(), arma::fill::eye);
      
    for (unsigned int i = order; i < dates.size(); i++) {
      result(i, i) = c.calculateYF(dates. at(i-order), dates.at(i));
    }
    return arma::inv(result);
  }

}  // namespace ir
}  // namespace julian
