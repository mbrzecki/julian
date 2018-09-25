#ifndef JULIAN_BRACKETINGROOTFIDNER_HPP
#define JULIAN_BRACKETINGROOTFIDNER_HPP

#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>
#include <mathematics/numericalAlgorithms/GslFunctionAdapter.hpp>

namespace julian {

  /**
   * @file   bracketingRootFinder.hpp
   * @brief  File contains implementation of bracketing root finder algorithm.
   */
  
  /** \ingroup rootfinding
   * 
   * \brief Types of bracketing algorithms.
   * 
   * The function may use one of three algorithm defined below:
   * * The bisection method 
   *   
   *  The bisection method in mathematics is a root-finding method that repeatedly bisects an interval and then selects a subinterval in which a root must lie for further processing.
   *
   * * Method of False Position
   * An algorithm for finding roots which retains that prior estimate for which the function value has opposite sign from the function value at the current best estimate of the root. 
   * Using the two-point form of the line
   * 
   * \f[ y-y_1=(f(x_{n-1})-f(x_1))/(x_{n-1}-x_1)(x_n-x_1) \f]
   * with \f$y=0\f$, using \f$y_1=f(x_1)\f$, and solving for \f$x_n\f$ therefore gives the iteration
   * \f[x_n=x_1-(x_{n-1}-x_1)/(f(x_{n-1})-f(x_1))f(x_1)\f].
   * For more information <a href="https://en.wikipedia.org/wiki/False_position_method">Wikipedia article</a>.
   * 
   * * Brent-Dekker Method
   * Brent's method is a root-finding algorithm which combines root bracketing, bisection, and inverse quadratic interpolation. 
   * For more information <a href="https://en.wikipedia.org/wiki/Brent%27s_method"> Wikipedia article</a>.
   *
   * For more information see Chapter 9 of Numerical Recipes \cite NumRec.
   */
  enum class BracketingRootFinder {BISECTION,  ///< The bisection method 
				   FALSEPOS,  ///< Method of False Position
				   BRENT_DEKKER  ///< Brent-Dekker Method
  };

  /** \ingroup rootfinding
   * \brief Function finds roots using bracketing algorithms.
   *
   * We will say that a root is bracketed in the interval (a, b) if f(a) and f(b) have opposite signs. 
   * If the function is continuous, then at least one root must lie in that interval (<a href="https://en.wikipedia.org/wiki/Intermediate_value_theorem">the intermediate value theorem</a>).
   * Algorithms which proceed by bracketing a root are guaranteed to converge, but usually are slow. 
   * For more information see Chapter 9 of Numerical Recipes \cite NumRec.
   *
   * \param f Functor for which root is searched.
   * \param x_lo Lower bound of interval
   * \param x_hi Upper bound of interval
   * \param type Type of algorithm. See julian::BracketingRootFinder  
   * \param precision User-specified precision (relative). When this number is reached, algorithm is stopped. Default value 1e-12.
   * \param max_iter A user-specified maximum number of iterations. When this number is reached, algorithm is stopped. Default value 100.
   * \return Root of f function found in interval \f$(x_{lo},x_{hi} )\f$
   *
   *  \remarks Function uses algorithms implemented in GSL
   */
  template<typename T>
  double  bracketingRootFinder(T f, double x_lo, double x_hi, BracketingRootFinder type, double precision = 1e-12, int max_iter = 100) {
    GslFunctionAdapter<T> pF(f);
    gsl_function *gsl_f = static_cast<gsl_function*>(&pF); 
    double root {0.0};
    
    int status;
    int iter = 0;

    const gsl_root_fsolver_type *type_of_solver;
    gsl_root_fsolver *s;
    
    switch (type){
    case BracketingRootFinder::BISECTION: type_of_solver = gsl_root_fsolver_bisection; break;
    case BracketingRootFinder::FALSEPOS: type_of_solver = gsl_root_fsolver_falsepos; break;
    case BracketingRootFinder::BRENT_DEKKER: type_of_solver = gsl_root_fsolver_brent; break;
    }
    
    s = gsl_root_fsolver_alloc (type_of_solver);
    gsl_root_fsolver_set (s, gsl_f, x_lo, x_hi);
    
    do {
      iter++;
      status = gsl_root_fsolver_iterate (s);
      root = gsl_root_fsolver_root (s);
      x_lo = gsl_root_fsolver_x_lower (s);
      x_hi = gsl_root_fsolver_x_upper (s);
      status = gsl_root_test_interval (x_lo, x_hi, 0, precision);
    } while (status == GSL_CONTINUE && iter < max_iter);
    
    gsl_root_fsolver_free (s);
    return root;
  }
}  // namespace julian
#endif
  
