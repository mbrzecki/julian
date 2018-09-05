#include <mathematics/regressions/regressionWithoutIntercept.hpp>
#include <vector>

namespace julian {

  /** \brief evaluates the linear regression model for x 
   */
  double RegressionWithoutIntercept::operator()(double x) const {
    return c1_ * x;
  }


  /** \brief estimates the slope parameters (intercept = 0) basing on provided data 
   */
  void RegressionWithoutIntercept::estimate(const std::vector<double>& x,const std::vector<double>& y) {
    gsl_fit_mul (&x.front(), 1, &y.front(), 1, x.size(), 
		 &c1_, &cov11_, &chi_sq_);
  }

  /** \brief estimates the slope parameters (intercept = 0) basing on provided data and weights
   */
  void RegressionWithoutIntercept::estimate(const std::vector<double>& x,const std::vector<double>& y,const std::vector<double>& w) {
    gsl_fit_wmul (&x.front(), 1, &w.front(), 1, &y.front(), 1, x.size(), 
		  &c1_, &cov11_, &chi_sq_);
  }

  std::vector<double> RegressionWithoutIntercept::getCoefficient() const {
    std::vector<double> ret {c1_};
    return ret;
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, julian::RegressionWithoutIntercept& r) {
  s << "Y = " << r.c1_ << " X " << std::endl;
  return s;
}

} // namespace julian

