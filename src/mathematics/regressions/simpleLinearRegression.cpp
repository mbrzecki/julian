#include <mathematics/regressions/simpleLinearRegression.hpp>
#include <vector>

namespace julian {

  /** \brief evaluates the linear regression model for x 
   */
  double SimpleLinearRegression::operator()(double x) const {
    return c0_ + c1_ * x;
  }

  /** \brief returns slope
   */
  double SimpleLinearRegression::getSlope() {
    return c1_;
  }

  /** \brief returns intercept
   */
  double SimpleLinearRegression::getIntercept() {
    return c0_;
  }

  /** \brief estimates the parameters basing on provided data
   */
  void SimpleLinearRegression::estimate(const std::vector<double>& x,const std::vector<double>& y) {
    gsl_fit_linear (&x.front(), 1, &y.front(), 1, x.size(), 
		    &c0_, &c1_,
		    &cov00_, &cov01_, &cov11_, 
		    &chi_sq_);
  }

  /** \brief estimates the parameters basing on provided data and weights
   */
  void SimpleLinearRegression::estimate(const std::vector<double>& x,const std::vector<double>& y,const std::vector<double>& w) {
    gsl_fit_wlinear (&x.front(), 1, &w.front(), 1, &y.front(), 1, x.size(), 
		     &c0_, &c1_, &cov00_, &cov01_, &cov11_, &chi_sq_);
  }

  std::vector<double> SimpleLinearRegression::getCoefficient() const {
    std::vector<double> ret {c0_, c1_};
    return ret;
  }
} // namespace julian

std::ostream& operator<<(std::ostream& s, julian::SimpleLinearRegression& r) {
  std::string sign;
  std::string coef;

  if (r.getIntercept() > 0) {
    sign = "+";
    coef = std::to_string(r.getIntercept());
  } else if (r.getIntercept() == 0) {
    sign = "";
    coef = "";
  } else {
    sign = "-";
    coef = std::to_string(-r.getIntercept());
  }
  s << "Y = " << r.getSlope() << " X " << sign << " " << coef << std::endl;
  return s;
}
