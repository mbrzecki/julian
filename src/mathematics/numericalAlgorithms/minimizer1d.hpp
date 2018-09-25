#ifndef JULIAN_MINIMIZER1D_HPP
#define JULIAN_MINIMIZER1D_HPP

#include <mathematics/numericalAlgorithms/GslFunctionAdapter.hpp>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_min.h>

namespace julian {

  
  /**
   * @file   minimizer1d.hpp
   * @brief  File contains implementation of one dimensional minimizer.
   */
  
  /**\ingroup minimizers
   * \brief Types of 1d minimizers algorithms.
   *
   * The function may use one of three algorithms defined below:
   * * Golden Section minimizer
   *
   *  The golden section algorithm is the simplest method of bracketing the minimum of a function. It is the slowest algorithm provided by the library, with linear convergence.
   * 
   *  On each iteration, the algorithm first compares the subintervals from the endpoints to the current minimum. 
   * The larger subinterval is divided in a golden section (using the famous ratio \f$ (3-\sqrt 5)/2 \approx 0.3819660 \f$ and the value of the function at this new point is calculated. 
   * The new value is used with the constraint \f$f(a') > f(x') < f(b')\f$ to a select new interval containing the minimum, by discarding the least useful point. 
   * This procedure can be continued indefinitely until the interval is sufficiently small. 
   * Choosing the golden section as the bisection ratio can be shown to provide the fastest convergence for this type of algorithm.
   *
   * * Brent's minimizer
   *
   *  The Brent minimization algorithm combines a parabolic interpolation with the golden section algorithm. This produces a fast algorithm which is still robust.
   * 
   * *  Brent-Gill-Murray algorithm 
   *
   *  This is a variant of Brent’s algorithm which uses the safeguarded step-length algorithm of Gill and Murray.
   *
   * For more information see Chapter 10 of Numerical Recipes \cite NumRec and GSL Docs ( <a href="https://www.gnu.org/software/gsl/doc/html/min.html">link</a>).
   */
  
  enum class Minimizer1d {GOLDEN_SECTION_MINIMIZER, ///< Golden Section minimizer 
			  BRENT_MINIMIZER, ///< Brent's minimizer
			  QUAD_GOLDEN ///<  Brent-Gill-Murray algorithm 
  };

  /** \ingroup minimizers
   * \brief Function finds minimum of provided one-argument function.
   *
   * Function finds minimum of provided one-argument function. 
   * The minimum is found in interval (x_lo, x_hi)
   *
   * \param f Functor for which root is searched.
   * \param x_lo Lower bound of interval
   * \param x_hi Upper bound of interval
   * \param guess initial guess for the minimum.  
   * \param precision Algorithm finds minimum satisfying condition \f$|x_m - x_m^*| < \hbox{\it precision\/}\, x_m^* \f$
   * \param number_of_iterations A user-specified maximum number of iterations
   * \param t type of minimizer see julian::Minimizer1d 
   * \return Abscissa of minimum of function f. 
   *
   * \remarks Function uses algorithms implemented in GSL
   */
  
  template<typename F>
  double minimizer1d(F f, double x_lo, double x_hi, double guess, double precision, int number_of_iterations, Minimizer1d t) {
    GslFunctionAdapter<F> pF(f);
    gsl_function *gsl_f = static_cast<gsl_function*>(&pF); 
    
    const gsl_min_fminimizer_type *T;
    gsl_min_fminimizer *s;
    switch (t) {
    case Minimizer1d::GOLDEN_SECTION_MINIMIZER:
      T = gsl_min_fminimizer_goldensection;
      break;
    case Minimizer1d::BRENT_MINIMIZER:
      T = gsl_min_fminimizer_brent;
      break;
    case Minimizer1d::QUAD_GOLDEN:
      T = gsl_min_fminimizer_quad_golden;
      break;
    }
    
    s = gsl_min_fminimizer_alloc (T);
    gsl_min_fminimizer_set (s, gsl_f, guess, x_lo, x_hi);
    
    int status;
    int iter = 0;
    do {
      iter++;
      status = gsl_min_fminimizer_iterate (s);
      status = gsl_min_test_interval (x_lo, x_hi, 0.0, precision);
    } while (status == GSL_CONTINUE && iter < number_of_iterations);
    
    double ret = gsl_min_fminimizer_x_minimum (s);
    gsl_min_fminimizer_free (s);
    
    return ret;
  }
}  // namespace julian

#endif 
