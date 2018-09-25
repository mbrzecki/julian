#ifndef JULIAN_SIMPLELINEARREGRESSION_HPP
#define JULIAN_SIMPLELINEARREGRESSION_HPP

#include <mathematics/regressions/regression.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <gsl/gsl_fit.h>

namespace julian {

  /**
   * @file   simpleLinearRegression.hpp
   * @brief  File contains class implementing simple linear regression.
   */

  /** \ingroup regression
   *  \brief Class implements simple linear regression
   *
   * Simple linear regression is a linear regression model with a single explanatory variable. The parameters of the regression are calculated by minimizing the OLS.
   * In other words class computes the best-fit linear regression coefficients \f$(c_0, c_1)\f$ of the model \f$Y = c_0 + c_1 X\f$ for the dataset (x, y) by minimizing
   * the sum: \f$\sum^{n}_{i=1} (Y_i - (c_1 X + c_0))^2 \f$
   *
   * For more information see <a href = "https://en.wikipedia.org/wiki/Simple_linear_regression"> Wikipedia</a> 
   *
   *  \remarks Class uses algorithm implemented in GSL
   */

  class SimpleLinearRegression : public DeeplyCopyableRegression<SimpleLinearRegression> {
  public:
    SimpleLinearRegression(): chi_sq_(0.0), cov00_(0.0), cov01_(0.0), cov11_(0.0), c0_(0.0), c1_(0.0) {};

    void estimate(const std::vector<double>& x,const std::vector<double>& y);
    void estimate(const std::vector<double>& x,const std::vector<double>& y,const std::vector<double>& w);
    
    double getSlope();
    double getIntercept();
    std::vector<double> getCoefficient() const;
    double operator()(double) const;

  private:
    double chi_sq_; /*!< \brief The sum of squares of the residuals from the best-fit line*/
    double cov00_;  /*!< \brief Variance of the slope estimate.*/
    double cov01_;  /*!< \brief Covariance of the slope/intercept estimates.*/
    double cov11_;  /*!< \brief Variance of the intercept estimate.*/
    double c0_;     /*!< \brief Intercept of linear regression.*/
    double c1_;     /*!< \brief Slope of linear regression.*/
  };
}  //  namespace julian

/** \brief Overloads stream operator
 *
 * This overloaded operator enables to print the curve on the console.
 */
std::ostream& operator<<(std::ostream& s, julian::SimpleLinearRegression& r);

#endif
