#ifndef JULIAN_DERIVATIVEROOTFINDER_HPP
#define JULIAN_DERIVATIVEROOTFINDER_HPP

#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>
#include <mathematics/numericalAlgorithms/GslFunctionAdapter.hpp>
#include <mathematics/numericalAlgorithms/GslFunctionFdfAdapter.hpp>
#include <gsl/gsl_deriv.h>

namespace julian {

  /**
   * @file   derivativeRootFinder.hpp
   * @brief  File contains implementation of root finder algorithm using derivative.
   */
  
  /** \ingroup rootfinding
   * 
   * \brief Types of root finding algorithms using derivatives
   * 
   * The function may use one of three algorithm defined below:
   * * Newton Raphson method 
   *
   * The algorithm begins with an initial guess for the location of the root. On each iteration, a line tangent to the function f is drawn at that position. 
   * The point where this line crosses the x-axis becomes the new guess. The iteration is defined by the following sequence,
   * \f[x_{i+1} = x_i - \frac{f(x_i)}{f'(x_i)}\f]
   *
   * * Secant method
   * 
   * The secant method is a simplified version of Newton’s method which does not require the computation of the derivative on every step.
   * On its first iteration the algorithm begins with Newton’s method, using the derivative to compute a first step,
   * \f[x_1 = x_0 - \frac{f(x_0)}{f'(x_0)}\f]
   * Subsequent iterations avoid the evaluation of the derivative by replacing it with a numerical estimate, the slope of the line through the previous two points,
   *  \f[x_{i+1} = x_i - {f(x_i) \over f'_{est}} \mbox{where}  f'_{est} =  \frac{f(x_{i}) - f(x_{i-1})}{x_i - x_{i-1}} \f]
   *
   * * Steffensen method
   *
   * The Steffensen Method provides the fastest convergence of all the routines. It combines the basic Newton algorithm with an Aitken “delta-squared” acceleration.
   * If the Newton iterates are \f$x_i\f$ then the acceleration procedure generates a new sequence \f$R_i=\f$,
   * \f[R_i = x_i - {(x_{i+1} - x_i)^2 \over (x_{i+2} - 2 x_{i+1} + x_i)}\f]
   * which converges faster than the original sequence under reasonable conditions.
   *
   *
   * Description of methods taken from GSL documentation.
   * For more information see Chepter 9 of Numerical Recipes \cite NumRec and GSL Docs ( <a href="https://www.gnu.org/software/gsl/doc/html/roots.html">link</a>).
   */
  enum class DerivativeRootFinder {NEWTON_RAPHSON , ///< Newton Raphson method
				   SECANT,  ///<Secant method
				   STEFFENSEN ///< Steffensen method
  };

  /** \ingroup rootfinding
   * \brief Function finds roots basing on derivative.
   *
   * The derivative root algorithms require an initial guess for the location of the root. 
   * There is no absolute guarantee of convergence—the function must be suitable for this technique and the initial guess must be sufficiently close to the root for it to work.
   * When these conditions are satisfied then convergence is quadratic.
   *
   * \param f Functor for which root is searched.
   * \param df Functor calculating derivative of f.
   * \param x_0 Initial guess
   * \param type Type of algorithm. See julian::DerivativeRootFinder  
   * \param precision User-specified precision (relative). When this number is reached, algorithm is stopped. Default value 1e-12.
   * \param max_iter A user-specified maximum number of iterations. When this number is reached, algorithm is stopped. Default value 100.
   * \return Root of f function
   *
   *  \remarks Function uses algorithms implemented in GSL
   */
  template<typename T, typename U>
  double derivativeRootFinder(T f, U df, double x_0, DerivativeRootFinder type,double precision = 1e-12, int max_iter = 100) {
    GslFunctionFdfAdapter<decltype(f),decltype(df)> Fdf(f,df);
    int status;
    int iter = 0;
    double x = x_0;
    const gsl_root_fdfsolver_type *Type = gsl_root_fdfsolver_newton;
    gsl_root_fdfsolver *s;
    
    switch (type) {
    case DerivativeRootFinder::NEWTON_RAPHSON: Type = gsl_root_fdfsolver_newton; break;
    case DerivativeRootFinder::SECANT: Type = gsl_root_fdfsolver_secant; break;
    case DerivativeRootFinder::STEFFENSEN: Type = gsl_root_fdfsolver_steffenson; break;
    }
    
    s = gsl_root_fdfsolver_alloc (Type);
    gsl_root_fdfsolver_set (s, &Fdf, x_0);

    do {
      iter++;
      status = gsl_root_fdfsolver_iterate (s);
      x_0 = x;
      x = gsl_root_fdfsolver_root (s);
      status = gsl_root_test_delta (x, x_0, 0, precision);
    } while (status == GSL_CONTINUE && iter < max_iter);
    
    gsl_root_fdfsolver_free (s);
    return x;
  }

  /** \ingroup rootfinding
   * \brief Function finds roots basing on derivative.
   *
   * 
   * The derivative root algorithms require an initial guess for the location of the root. 
   * There is no absolute guarantee of convergence—the function must be suitable for this technique and the initial guess must be sufficiently close to the root for it to work.
   * When these conditions are satisfied then convergence is quadratic.
   *
   * The function does not need derivative of f function. It approximates derivative using finite difference:
   * \f[f'(x) \approx \frac{f(x+h) - f(x)}{h}\f]
   *
   * \param f Functor for which root is searched.
   * \param x_0 Initial guess
   * \param type Type of algorithm. See julian::DerivativeRootFinder  
   * \param precision User-specified precision (relative). When this number is reached, algorithm is stopped. Default value 1e-12.
   * \param max_iter A user-specified maximum number of iterations. When this number is reached, algorithm is stopped. Default value 100.
   * \param h increment used in numerical differentiation
   * \return Root of f function
   *
   * \remarks Function uses algorithms implemented in GSL
   */
  template<typename T>
  double derivativeRootFinder(T f, double x_0, DerivativeRootFinder type,double precision = 1e-12, int max_iter = 100, double h = 1e-6) {
    GslFunctionAdapter<decltype(f)> pF(f);
    gsl_function *gsl_f = static_cast<gsl_function*>(&pF); 
    
    auto df = [&](double x)->double{
      double result, abserr;
      gsl_deriv_forward (gsl_f, x, h, &result, &abserr);
      return result;
    };
    
    GslFunctionFdfAdapter<decltype(f),decltype(df)> Fdf(f,df);
    
    int status;
    int iter = 0;
    double x = x_0;
    const gsl_root_fdfsolver_type *Type;
    gsl_root_fdfsolver *s;
    
    switch (type) {
    case DerivativeRootFinder::NEWTON_RAPHSON: Type = gsl_root_fdfsolver_newton; break;
    case DerivativeRootFinder::SECANT : Type = gsl_root_fdfsolver_secant; break;
    case DerivativeRootFinder::STEFFENSEN : Type = gsl_root_fdfsolver_steffenson; break;
    }
    
    s = gsl_root_fdfsolver_alloc (Type);
    gsl_root_fdfsolver_set (s, &Fdf, x_0);
    
    do {
      iter++;
      status = gsl_root_fdfsolver_iterate (s);
      x_0 = x;
      x = gsl_root_fdfsolver_root (s);
      status = gsl_root_test_delta (x, x_0, 0, precision);
    } while (status == GSL_CONTINUE && iter < max_iter);

    gsl_root_fdfsolver_free (s);
    return x;
  }
}  // namespace julian
#endif
