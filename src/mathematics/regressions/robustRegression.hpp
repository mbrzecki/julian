#ifndef JULIAN_ROBUSTREGRESSION_HPP
#define JULIAN_ROBUSTREGRESSION_HPP

#include <vector>
#include <iostream>
#include <mathematics/regressions/regression.hpp>

namespace julian {

  /**
   * @file   robustRegression.hpp
   * @brief  File contains class implementing robust regression.
   */

  /** \ingroup regression
   *  \brief Class implements robust linear regression
   *
   * Robust regression is introduced because OLS models are often heavily influenced by the presence of outliers. 
   * Generally robust regression is estimated by minimizing the objective function
   * \f[\sum_i \rho(e_i) = \sum_i \rho (y_i - Y(c, x_i))\f]
   * where \f$e_i = y_i - Y(c, x_i)\f$ is the residual of the ith data point, and \f$\rho(e_i)\f$ is a function that:
   *
   * 1) \f$\rho(e) \ge 0 \f$
   *
   * 2) \f$\rho(0) = 0\f$
   *
   * 3) \f$\rho(-e) = \rho(e)\f$
   *
   * 4) \f$\rho(e_1) > \rho(e_2) for |e_1| > |e_2|\f$
   *
   * When \f$\rho(e) = e^2\f$ we obtain OLS estimator. To find the coefficients minimizing the objective function Iteratively Reweighed Least Squares (IRLS) algorithm is used. 
   * In this algorithm the problem of minimizing above sum is reduced to standard OLS with weighting, where weights \f$w(e)\f$ depends on error term. 
   *
   * Apart from OLS following functions can be used:
   * 
   * * Tukey's bi-square function
   *
   *  \f[ w(e) = \left\{  \begin{array}{cc} (1 - e^2)^2, & |e| \le 1 \\ 0, & |e| > 1 \end{array}\right.\f]
   *
   * * Cauchy’s function (aka Lorentzian function)
   *
   * \f[ w(e) = \frac{1}{1 + e^2}\f]
   *
   *
   * * fair regression
   * 
   * \f[w(e) = frac{1}{ 1 + |e|}\f]
   * 
   * * OLS
   *
   * \f[w(e) = 1 \f]
   *
   * *  Welsch function
   *
   * \f[w(e) = \exp{(-e^2)}\f]
   *
   * \warning Cauchy's function does not guarantee a unique solution.
   *
   * For more information see Chapter 15.7 of \cite NumRec,  <a href = "https://en.wikipedia.org/wiki/Robust_regression"> Robust Regression</a> 
   * and <a href = "https://en.wikipedia.org/wiki/Iteratively_reweighted_least_squares"> Iteratively reweighted least squares</a>  
   *
   * \remarks Class uses algorithm implemented in GSL
   */
  
  class RobustRegression : public DeeplyCopyableRegression<RobustRegression> {
  public:

    /** \brief Robust regression types 
     */
    enum type {BISQUARE, ///<  Tukey's bi-square function
	       CAUCHY,   ///<  Cauchy’s function
	       FAIR,     ///<  Fair regression
	       HUBER,    ///<  Huber loss function
	       OLS,      ///<  OLS
	       WELSCH    ///<  Welsch function
    };

    /** \brief constructor
     *
     * \note If no arguments are provided, order of polynomial is set to 2 and type is set to OLS.
     */
    RobustRegression(): order_(2), type_(RobustRegression::OLS){};

    /** \brief constructor
     */
    RobustRegression(int order, RobustRegression::type t): order_(order), type_(t) {};
    
    void estimate(const std::vector<double>& x,const std::vector<double>& y);
       
    std::vector<double> getCoefficient() const;
    double operator()(double) const;

    virtual ~RobustRegression(){}

  private:
    int order_; /*!< \brief Order of polynomial*/
    RobustRegression::type type_; /*!< \brief Type of robust regression */
    std::vector<double> coefs_;/*!< \brief Vector of coefficients */
  };
  
}
/** \brief Overloads stream operator
 *
 * This overloaded operator enables to print the curve on the console.
 */
std::ostream& operator<<(std::ostream& s, julian::RobustRegression& r);

#endif
