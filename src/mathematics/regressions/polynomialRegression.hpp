#ifndef JULIAN_POLYNOMIALREGRESSION_HPP
#define JULIAN_POLYNOMIALREGRESSION_HPP

#include <vector>
#include <iostream>
#include <mathematics/regressions/regression.hpp>

namespace julian {

  /**
   * @file   polynomialRegression.hpp
   * @brief  File contains class implementing polynomial regression.
   */

  /** \ingroup regression
   *
   * Polynomial regression is regression model with a single explanatory variable. The parameters of the regression are calculated by minimizing the OLS.
   * In other words class computes the best-fit linear regression coefficients \f$(c_0, c_1, ..., c_n)\f$ of the model \f$Y = c_0 + \Sigma^{i=n}_{i=1}c_i x^i\f$ for the dataset (x, y) by minimizing
   * the sum: \f$ \sum_i w_i (y_i - \sum_j X_{ij} c_j)^2 = || y - Xc ||_W^2\f$.
   *
   * For more information see <a href = "https://en.wikipedia.org/wiki/Polynomial_regression"> Wikipedia</a> 
   *
   *  \remarks Class uses algorithm implemented in GSL
   */
  class PolynomialRegression : public DeeplyCopyableRegression<PolynomialRegression> {
  public:
    /** \brief constructor
     *
     * \note If order of polynomial is not given, order of polynomial is set to 2.
     */
    PolynomialRegression(): order_(2) {};

    /** \brief constructor
     *
     * \param order Order of polynomial fitted
     */
    PolynomialRegression(int order): order_(order) {};

    void estimate(const std::vector<double>& x,const std::vector<double>& y);
    void estimate(const std::vector<double>& x,const std::vector<double>& y,const std::vector<double>& w);

    std::vector<double> getCoefficient() const;
    
    double operator()(double) const;

  private:
    int order_; /*!< \brief Order of polynomial*/
    std::vector<double> coefs_; /*!< \brief Vector of coefficients */
  };
}

/** \brief Overloads stream operator
 *
 * This overloaded operator enables to print the curve on the console.
 */
std::ostream& operator<<(std::ostream& s, julian::PolynomialRegression& r);

#endif
