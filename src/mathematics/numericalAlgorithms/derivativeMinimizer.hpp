#ifndef JULIAN_DERIVATIVEMINIMIZER_HPP
#define JULIAN_DERIVATIVEMINIMIZER_HPP

#include <gsl/gsl_multimin.h>
#include <mathematics/numericalAlgorithms/GslMultiminFunctionFdfAdapter.hpp>

namespace julian {

  /**
   * @file   derivativeMinimizer.hpp
   * @brief  File contains implementation multi-dimension minimizers.
   */
  
  /**\ingroup minimizers
   * \brief  Types of multi-dimension minimizer that requires gradient of function
   *
   * The function may use one of algorithms defined below:
   * * Fletcher-Reeves conjugate gradient
   *
   *  An initial search direction p is chosen using the gradient, and line minimization is carried out in that direction. 
   * The accuracy of the line minimization is specified by the parameter tol. 
   * The minimum along this line occurs when the function gradient g and the search direction p are orthogonal.
   * The line minimization terminates when \f$p\cdot g < tol |p| |g|\f$. The search direction is updated using the Fletcher-Reeves formula \f$p' = g' - \beta \f$ g where \f$\beta=-|g'|^2/|g|^2\f$,
   *
   * * Polak Ribiere conjugate gradient
   *
   *  Method similar ot Fletcher-Reeves, differing only in the choice of the coefficient \f$\beta\f$. 
   * \f[\beta = \frac{g'(g-g')}{g^2} \f]
   * 
   *
   * * Broyden-Fletcher-Goldfarb-Shanno
   *  
   *  BFGS method belongs to quasi-Newton methods. In quasi-Newton methods, the Hessian matrix of second derivatives doesn't need to be evaluated directly.
   * Instead, the Hessian matrix is approximated using updates specified by gradient evaluations (or approximate gradient evaluations). 
   *
   *  This version of this minimizer is the most efficient version available, and is a faithful implementation of the line minimization scheme described in 
   * Fletcher’s Practical Methods of Optimization (\cite fletcher)
   * 
   * * Steepest Descent
   *
   *  Algorithm follows the downhill gradient of the function. After the step was made the algorithm calculates function value for new position.
   * If new value of cost function is smaller step-size is doubled. If the downhill step leads to a higher function value then the algorithm backtracks and the step size
   * is decreased using the parameter \b tol.
   *
   * For more information see \cite fletcher , 10.6-10.7 chapter of \cite NumRec 
   * and GSL Docs ( <a href="https://www.gnu.org/software/gsl/doc/html/multimin.html">link</a>).
   */

  enum class DerivativeMinimizer {FLETCHER_REEVES,         ///< Fletcher-Reeves conjugate gradient
				  POLAK_RIBIERE,           ///< Polak-Ribiere conjugate gradient 
				  BROYDEN_FLETCHER,        ///< Broyden-Fletcher-Goldfarb-Shanno
				  STEEPEST_DESCENT         ///< Steepest Descent
  };

  /**\ingroup minimizers
   * \brief Multidimension minimizer that requires derivative of function
   *
   * \param f   Functor with overloaded:  double operator(vector<dobule>), that calculates the value of the optimized function. 
   * \param df  Functor with overloaded:  vector<dobule> operator(vector<dobule>), that calculates the gradient of the optimized function. 
   * \param fdf Functor with overloaded:  pair<double,vector> operator(vector<dobule>), that calculates the value and the gradient of the optimized function. 
   * \param x_init initial point
   * \param type Type of algorithm (see DerivativeMinimizer)
   * \param step_size The size of the first trial step
   * \param tol line minimization parameter; interpretation of tol parameter depends on the algorithm used
   * \param abs The function tests the norm of the gradient against the absolute tolerance \b abs.
   * \param max_iter Maximal number of iterations
   * \return minimum of the function
   *
   * \remarks Class uses algorithms implemented in GSL
   */
  template<typename F, typename dF, typename FdF>
  std::vector<double> derivativeMinimizer(F f,
					  dF df,
					  FdF fdf,
					  std::vector<double> x_init,
					  DerivativeMinimizer type,
					  double step_size = 0.1,
					  double tol = 1e-4,
					  double abs = 1e-6,
					  unsigned int max_iter = 200) {

    int n = x_init.size();
    GslMultiminFunctionFdfAdapter<decltype(f), decltype(df), decltype(fdf)> Func(f, df, fdf, n);
    
    size_t iter = 0;
    int status;

    const gsl_multimin_fdfminimizer_type *T;

    switch(type) {
    case DerivativeMinimizer::FLETCHER_REEVES:
      T = gsl_multimin_fdfminimizer_conjugate_fr;
      break;
    case DerivativeMinimizer::POLAK_RIBIERE:
      T = gsl_multimin_fdfminimizer_conjugate_pr;
      break;
    case DerivativeMinimizer::BROYDEN_FLETCHER:
      T = gsl_multimin_fdfminimizer_vector_bfgs2;
      break;
    case DerivativeMinimizer::STEEPEST_DESCENT:
      T = gsl_multimin_fdfminimizer_steepest_descent;
      break;
    }
    
    gsl_multimin_fdfminimizer *s;
    gsl_vector *x;
    x = gsl_vector_alloc (n);
    for (int i = 0; i < n; ++i) {
      gsl_vector_set(x, i, x_init.at(i));
    }
    s = gsl_multimin_fdfminimizer_alloc (T, n);
    gsl_multimin_fdfminimizer_set (s, &Func, x, step_size, tol);

    do {
      iter++;
      status = gsl_multimin_fdfminimizer_iterate (s);
      if (status)
        break;
      status = gsl_multimin_test_gradient (s->gradient, abs);
    } while (status == GSL_CONTINUE && iter < max_iter);

    std::vector<double> ret;
    for (unsigned int i = 0; i < n; ++i) {
      ret.push_back(gsl_vector_get(s -> x, i));
    }

    gsl_multimin_fdfminimizer_free (s);
    gsl_vector_free (x);
    
    return ret;
  }

  /**\ingroup minimizers
   * \brief Multidimension minimizer that requires derivative of function
   *
   * Function calculates the gradient numerically using forward differentiation scheme with increment of argument provided.
   *
   * \param f Functor with overloaded:  double operator(vector<dobule>), that calculates the value of the optimized function. 
   * \param x_init initial point
   * \param type Type of algorithm (see DerivativeMinimizer)
   * \param step_size The size of the first trial step
   * \param tol line minimization parameter; interpretation of tol parameter depends on the algorithm used
   * \param increment increment of argument used in numerical differentiating
   * \param abs The function tests the norm of the gradient against the absolute tolerance \b abs.
   * \param max_iter Maximal number of iterations
   * \return minimum of the function
   *
   * \remarks Class uses algorithms implemented in GSL
   */
  template<typename F>
  std::vector<double> derivativeMinimizer(F f,
					  std::vector<double> x_init,
					  DerivativeMinimizer type,
					  double step_size = 0.1,
					  double tol = 1e-4,
					  double increment = 1e-5,
					  double abs = 1e-6,
					  unsigned int max_iter = 200) {
    int n = x_init.size();
    
    auto inverse_increment = 1.0 / increment;
    auto df = [f,n,increment,inverse_increment](std::vector<double>  x)->std::vector<double> {
      std::vector<double> ret;
      double val = f(x);
      for (int i = 0; i < n; ++i) {
	x[i] += increment;
	ret.push_back( (f(x) -val) * inverse_increment);
	x[i] -= increment;
      }      
      return ret;
    };

    auto fdf = [f,n,increment,inverse_increment](std::vector<double>  x)-> std::pair<double, std::vector<double> > {
      std::vector<double> ret;
      double val = f(x);
      auto inverse_increment = 1.0 / increment;
      for (int i = 0; i < n; ++i) {
	x[i] += increment;
	ret.push_back( (f(x) -val) * inverse_increment);
	x[i] -= increment;
      }      
      return std::make_pair(val,ret);
    };
	
    GslMultiminFunctionFdfAdapter<decltype(f), decltype(df), decltype(fdf)> Func(f, df, fdf, n);
    
    size_t iter = 0;
    int status ;

    const gsl_multimin_fdfminimizer_type *T;

    switch(type) {
    case DerivativeMinimizer::FLETCHER_REEVES:
      T = gsl_multimin_fdfminimizer_conjugate_fr;
      break;
    case DerivativeMinimizer::POLAK_RIBIERE:
      T = gsl_multimin_fdfminimizer_conjugate_pr;
      break;
    case DerivativeMinimizer::BROYDEN_FLETCHER:
      T = gsl_multimin_fdfminimizer_vector_bfgs2;
      break;
    case DerivativeMinimizer::STEEPEST_DESCENT:
      T = gsl_multimin_fdfminimizer_steepest_descent;
      break;
    }
    
    gsl_multimin_fdfminimizer *s;
    gsl_vector *x;
    
    x = gsl_vector_alloc (n);

    for (int i = 0; i < n; ++i) {
      gsl_vector_set(x, i, x_init.at(i));
    }

    s = gsl_multimin_fdfminimizer_alloc (T, n);
    gsl_multimin_fdfminimizer_set (s, &Func, x, step_size, tol);

    do {
      iter++;
      status = gsl_multimin_fdfminimizer_iterate (s);
      if (status) {
        break;
      }
      status = gsl_multimin_test_gradient (s->gradient, abs);
    } while (status == GSL_CONTINUE && iter < max_iter);

    std::vector<double> ret;
    for (int i = 0; i < n; ++i) {
      ret.push_back(gsl_vector_get(s -> x, i));
    }
    
    gsl_multimin_fdfminimizer_free (s);
    gsl_vector_free (x);
    
    return ret;
  }
}  // namespace julian
#endif
