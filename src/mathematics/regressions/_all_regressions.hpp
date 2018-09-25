#ifndef JULIAN_ALL_REGRESSIONS_HPP
#define JULIAN_ALL_REGRESSIONS_HPP

  /**
   * @file   _all_regressions.hpp
   * @brief  Regressions module
   */

/** \defgroup regression Regression
 * \ingroup mathematics
 *
 * \brief Regression methods.
 *
 * Module contains following regression types:
 * * Simple linear regression (\f$ Y \sim \alpha X + \beta\f$ minimizing OLS)
 * * Simple linear regression without intercept (\f$ Y \sim \alpha X \f$ minimizing OLS)
 * * Polynomial regression (\f$ Y \sim \sum^{n}_{i=0} \alpha_{i} X^{i} \f$ minimizing OLS)
 * * Robust Regression (\f$ Y \sim \sum^{n}_{i=0} \alpha_{i} X^{i} \f$ minimizing different loss functions: Huber, Cauchy, Welsch etc.) 
 * 
 * \remark Implemented function comes from GNU Scientific Library (<a href = "https://www.gnu.org/software/gsl/manual/gsl-ref.pdf">GSL Manual</a>). 
 */

#include <mathematics/regressions/regression.hpp>
#include <mathematics/regressions/simpleLinearRegression.hpp>
#include <mathematics/regressions/regressionWithoutIntercept.hpp>
#include <mathematics/regressions/polynomialRegression.hpp>
#include <mathematics/regressions/robustRegression.hpp>

#endif /* _ALL_REGRESSIONS_HPP */
