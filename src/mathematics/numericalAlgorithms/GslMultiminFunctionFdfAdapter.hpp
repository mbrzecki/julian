#ifndef JULIAN_GSLMULTIMINFUNCTIONFDFADAPTER_HPP
#define JULIAN_GSLMULTIMINFUNCTIONFDFADAPTER_HPP

#include <gsl/gsl_multimin.h>
#include <vector>
#include <utility>

namespace julian {
	
/**
 * @file   GslMultiminFunctionFdfAdapter.hpp
 * @brief  File contains adapter of GSL Function.
 */

  /** \ingroup gsladapters
   *  \brief Class implements adapter for gsl_multimin_function.
   *
   * Class implements adapter for gsl_multimin_function. Class wraps callable class F so that it can be statically casted to gsl_functiongsl_function.
   *
   * Functor **F** must have overloaded operator: **double operator()(std::vector<double>)** that calculates function value
   * Functor **dF** must have overloaded operator: **std::vector<double> operator()(std::vector<double>)** that calculates gradient
   * Functor **FdF** must have overloaded operator: **std::pair<double,std::vector<double>> operator()(std::vector<double>)** that calculates value and gradient of the function
   */

  
  template< typename F, typename dF, typename FdF >
  class GslMultiminFunctionFdfAdapter : public gsl_multimin_function_fdf {
  public:
  
    /** \brief Constructor
     *
     *  \param func1 must be a functor calculating the value of the function.
     *  \param func2 must be a functor calculating derivative of the function. 
     *  \param func3 must be a functor calculating value and derivative of the function.
     *  \param n_ Dimension of the function 
     */
    GslMultiminFunctionFdfAdapter(const F&   func1,
				  const dF&  func2,
				  const FdF& func3,
				  unsigned int n_) : func1_(func1), func2_(func2), func3_(func3) {
      f   = &GslMultiminFunctionFdfAdapter::call_f;
      df  = &GslMultiminFunctionFdfAdapter::call_df;
      fdf = &GslMultiminFunctionFdfAdapter::call_fdf;
      n   = n_;
      params = this;

    }
  private:
    const F&   func1_; /*!< \brief F must be a functor calculating the value of the function. */
    const dF&  func2_; /*!< \brief dF must be a functor calculating derivative of the function. */
    const FdF& func3_; /*!< \brief FdF must be a functor calculating value and derivative of the function. */

    /** \brief Method called by the GSL algorithm 
     */	
    static double call_f(const gsl_vector* x, void *params) {
      std::vector<double> x_std;

      for(unsigned int i = 0; i < static_cast<GslMultiminFunctionFdfAdapter*>(params)->n; ++i) {
	x_std.push_back( gsl_vector_get(x,i));
      }
      return static_cast<GslMultiminFunctionFdfAdapter*>(params)->func1_(x_std);
    }

	 /** \brief Method called by the GSL algorithm 
     */
    static void call_df(const gsl_vector* x, void *params ,gsl_vector* grad) {
      std::vector<double> x_std;

      for(unsigned int i = 0; i < static_cast<GslMultiminFunctionFdfAdapter*>(params)->n; ++i) {
	x_std.push_back( gsl_vector_get(x,i));
      }

      auto grad_  = static_cast<GslMultiminFunctionFdfAdapter*>(params)->func2_(x_std);

      for (unsigned int i = 0 ; i < static_cast<GslMultiminFunctionFdfAdapter*>(params)->n; ++i) {
	gsl_vector_set(grad, i, grad_.at(i));
      }
    }

	 /** \brief Method called by the GSL algorithm 
     */
    static void call_fdf(const gsl_vector* x, void *params, double *f, gsl_vector *grad) {
      std::vector<double> x_std;

      for(unsigned int i = 0; i < static_cast<GslMultiminFunctionFdfAdapter*>(params)->n; ++i) {
	x_std.push_back( gsl_vector_get(x,i));
      }
      std::pair<double, std::vector<double> > res = static_cast<GslMultiminFunctionFdfAdapter*>(params)->func3_(x_std);
      *f = res.first;
    
      for (unsigned int i = 0 ; i < static_cast<GslMultiminFunctionFdfAdapter*>(params)->n; ++i) {
	gsl_vector_set(grad, i, res.second.at(i));
      }
    }
  };

}  // namespace julian

#endif
