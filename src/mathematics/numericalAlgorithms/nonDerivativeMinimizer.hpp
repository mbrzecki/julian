#ifndef JULIAN_NONDERIVATIVEMINIMIZER_HPP
#define JULIAN_NONDERIVATIVEMINIMIZER_HPP

#include <gsl/gsl_multimin.h>
#include <mathematics/numericalAlgorithms/GslMultiminFunctionAdapter.hpp>

namespace julian {

  /**
   * @file   nonDerivativeMinimizer.hpp
   * @brief  File contains implementation multi-dimension minimizers.
   */
  
  /**\ingroup minimizers
   * \brief  Types of multi-dimension minimizer that does not require derivative of function
   *
   *  The function may use one of two algorithm defined below:
   * * Nelder-Mead Simplex
   *
   *  The Nelder–Mead method or downhill simplex method or amoeba method is a commonly applied numerical method used to find the minimum or maximum of an objective function in a multidimensional space. 
   * It is applied to non-linear optimization problems for which derivatives may not be known. 
   * 
   *
   * * Random Nelder-Mead Simplex
   *
   *  This method is a variant of Nelder-Mead Simplex which initialises the simplex around the starting point x using a randomly-oriented set of basis vectors instead of the fixed coordinate axes
   *
   *
   * For more information see Chapter 10 of Numerical Recipes \cite NumRec, original paper \cite nelder
   * and GSL Docs ( <a href="https://www.gnu.org/software/gsl/doc/html/multimin.html">link</a>).
   */

  enum class NonDerivativeMinimizer {NELDER_MEAD_SIMPLEX,        ///< Nelder-Mead Simplex
				     RANDOM_NELDER_MEAD_SIMPLEX  ///< Random Nelder-Mead Simplex
  };

  /**\ingroup minimizers
   * \brief Multi-dimension minimizer that does not require derivative of function
   *
   * \param f Functor being minimized taking std::vector<double> as argument
   * \param x_init initial guess
   * \param t minimizer type, see julian::NonDerivativeMinimizer
   * \param abs Optimizer test the value of the function against the absolute tolerance (abs) to determine if algorithm should stop 
   * \param number_of_iterations A user-specified maximum number of iterations
   * \returns std::vector representing point where f has minimum value
   * \remarks Function uses algorithms implemented in GSL
   */
  
  template<typename F>
  std::vector<double> nonDerivativeMinimizer(F f,std::vector<double> x_init, NonDerivativeMinimizer t, double abs = 1e-3, int number_of_iterations = 100) {
    int n = x_init.size();

    GslMultiminFunctionAdapter<decltype(f)> Func(f, n);

    gsl_multimin_function *gsl_f = static_cast<gsl_multimin_function*>(&Func); 

    const gsl_multimin_fminimizer_type *T = gsl_multimin_fminimizer_nmsimplex2;
    
    switch(t) {
    case NonDerivativeMinimizer::NELDER_MEAD_SIMPLEX:
      T = gsl_multimin_fminimizer_nmsimplex2;
      break;
    case NonDerivativeMinimizer::RANDOM_NELDER_MEAD_SIMPLEX:
      T = gsl_multimin_fminimizer_nmsimplex2rand;
      break;
    }
    
    gsl_multimin_fminimizer* s = gsl_multimin_fminimizer_alloc (T, n);
    
    gsl_vector *ss, *x;
    x = gsl_vector_alloc (n);
    ss = gsl_vector_alloc (n);
    gsl_vector_set_all (ss, 1.0);
    
    for (int i = 0; i < n; i++) {
      gsl_vector_set (x, i, x_init.at(i));
    }
    
    gsl_multimin_fminimizer_set (s, gsl_f, x, ss);
    int status = 0;
    int iter = 0;
    do {
      iter++;
      status = gsl_multimin_fminimizer_iterate(s);

      if (status)
      	break;
      
      double size = gsl_multimin_fminimizer_size (s);
      status = gsl_multimin_test_size (size, abs);
      
    } while (status == GSL_CONTINUE && iter < number_of_iterations);

    std::vector<double> ret(n);
    
    for( int i = 0; i < n; i++) {
      ret.at(i) = gsl_vector_get(s -> x, i);
    }
    
    return ret;
  }
}  // namespace julian
#endif
