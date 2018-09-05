#ifndef JULIAN_INTEGRATION_HPP
#define JULIAN_INTEGRATION_HPP

#include <mathematics/numericalAlgorithms/GslFunctionAdapter.hpp>
#include <gsl/gsl_integration.h>

namespace julian {

  /**
   * @file   integrate.hpp
   * @brief  File contains implementation of integrating algorithm.
   */
  
  /**\ingroup num_alg
   * \brief Types of integrating algorithms.
   *
   * The function uses Gauss-Kronrod algorithm in six variants:
   * * non adaptive Gauss-Kronrod
   * 
   * The QNG algorithm is a non-adaptive procedure which uses fixed Gauss-Kronrod-Patterson abscissae to sample the integrand at a maximum of 87 points.
   * 
   * * adaptive Gauss-Kronrod
   *
   * The QAG algorithm is a simple adaptive integration procedure. The integration region is divided into subintervals, and on each iteration the subinterval with the largest estimated error is bisected.
   * This reduces the overall error rapidly, as the subintervals become concentrated around local difficulties in the integrand.
   *
   * * adaptive Gauss-Kronrod with Singularities
   *
   * The QAGS algorithm combines adaptive bisection with the Wynn epsilon-algorithm to speed up the integration of many types of integrable singularities.
   *
   * * adaptive Gauss-Kronrod on infinite range
   *
   * Algorithm computes the integral of the function f over the infinite interval \f$(-\infty,+\infty)\f$. The integral is mapped onto the semi-open interval (0,1] using the transformation x = (1-t)/t.
   * It is then integrated using the QAGS algorithm.
   *
   * * adaptive Gauss-Kronrod solving improper integral with infinity as a upper limit of integration
   *
   * Algorithm computes the integral of the function f over the semi-infinite interval \f$(a,+\infty)\f$. 
   * The integral is mapped onto the semi-open interval (0,1] using the transformation x = a + (1-t)/t,
   *
   * * adaptive Gauss-Kronrod solving improper integral with infinity as a lower limit of integration
   * 
   * Algorithm computes the integral of the function f over the semi-infinite interval \f$(a,+\infty)\f$. 
   * The integral is mapped onto the semi-open interval (0,1] using the transformation x = b - (1-t)/t.
   *
   * For more information see Chapter 4 of Numerical Recipes \cite NumRec and manual of GNU Scientific Library (<a href="https://www.gnu.org/software/gsl/doc/html/integration.html"> link</a>).
   */

  enum class Integration {NON_ADAPTIVE_GAUSS_KRONROD,  ///< non adaptive Gauss-Kronrod 
			  ADAPTIVE_GAUSS_KRONROD,  ///< adaptive Gauss-Kronrod
			  ADAPTIVE_GAUSS_KRONROD_WITH_SINGULARITIES,  ///< adaptive Gauss-Kronrod with Singularities 
			  ADAPTIVE_GAUSS_KRONROD_INFINITE_RANGE,  ///< adaptive Gauss-Kronrod on infinite range
			  ADAPTIVE_GAUSS_KRONROD_UPPER_INFINITE,  ///< adaptive Gauss-Kronrod solving improper integral with infinity as a upper limit of integration
			  ADAPTIVE_GAUSS_KRONROD_LOWER_INFINITE  ///< adaptive Gauss-Kronrod solving improper integral with infinity as a lower limit of integration
  }; 

    /** \ingroup num_alg
   * \brief Function calculates integral.
   *
   * Function calculates the integral of provided function for a given interval.
   *
   * \param f Functor representing integrated function.
   * \param x_lo Lower bound of interval. Not needed for Integration::ADAPTIVE_GAUSS_KRONROD_INFINITE_RANGE and Integration::ADAPTIVE_GAUSS_KRONROD_LOWER_INFINITE
   * \param x_hi Upper bound of interval. Not needed for Integration::ADAPTIVE_GAUSS_KRONROD_INFINITE_RANGE and Integration::ADAPTIVE_GAUSS_KRONROD_UPPER_INFINITE
   * \param precision_abs absolute error limits
   * \param precision_rel relative error limits.
   * \param n order of Gaussian Quadrature
   * \param t Type of algorithm. See julian::Integration  
   * \return Integrates f function on given interval \f$(x_{lo},x_{hi} )\f$
   *
   *  \remarks Class uses algorithms implemented in GSL
   */
  template<typename F>
  double integrate(F f, double x_lo, double x_hi, double precision_abs,double precision_rel, int n, Integration t) {
    GslFunctionAdapter<F> pF(f);
    gsl_function *gsl_f = static_cast<gsl_function*>(&pF); 
    
    double ret;
    double error;
    size_t number_of_eval;
    
    gsl_integration_workspace * workspace = gsl_integration_workspace_alloc (n);
    
    switch (t) {
    case Integration::NON_ADAPTIVE_GAUSS_KRONROD:
      gsl_integration_qng(gsl_f, x_lo, x_hi, precision_abs, precision_rel, &ret, &error, &number_of_eval);break;
    case Integration::ADAPTIVE_GAUSS_KRONROD:
      gsl_integration_qag(gsl_f, x_lo, x_hi, precision_abs, precision_rel, n, 4, workspace, &ret, &error);break; // 4 means it is a 41 point rule
    case Integration::ADAPTIVE_GAUSS_KRONROD_WITH_SINGULARITIES:
      gsl_integration_qags (gsl_f, x_lo, x_hi, precision_abs, precision_rel, n, workspace, &ret, &error);break;
    case Integration::ADAPTIVE_GAUSS_KRONROD_INFINITE_RANGE:
      gsl_integration_qagi (gsl_f, precision_abs, precision_rel, n, workspace, &ret, &error);break;
    case Integration::ADAPTIVE_GAUSS_KRONROD_LOWER_INFINITE:
      gsl_integration_qagil(gsl_f, x_lo, precision_abs, precision_rel, n, workspace, &ret, &error );break;
    case Integration::ADAPTIVE_GAUSS_KRONROD_UPPER_INFINITE:
      gsl_integration_qagiu(gsl_f, x_hi, precision_abs, precision_rel, n, workspace, &ret, &error );break;    
    }
    
    gsl_integration_workspace_free (workspace);
    return ret;
  }
}  // namespace julian
  
#endif /* INTEGRATION_HPP */
