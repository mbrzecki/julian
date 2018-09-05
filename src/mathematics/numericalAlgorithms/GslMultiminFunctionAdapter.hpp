#ifndef JULIAN_GSLMULTIMINFUNCTIONADAPTER_HPP
#define JULIAN_GSLMULTIMINFUNCTIONADAPTER_HPP

#include <gsl/gsl_multimin.h>

namespace julian {

/**
 * @file   GslMultiminFunctionAdapter.hpp
 * @brief  File contains adapter of GSL Function.
 */

  /** \ingroup gsladapters
   *  \brief Class implements adapter for gsl_multimin_function.
   *
   * Class implements adapter for gsl_multimin_function. Class wraps callable class F so that it can be statically casted to gsl_functiongsl_function.
   *
   * Functor **F** must have overloaded operator: **double operator()(std::vector<double>)**
   * 
   */

  template< typename F >
  class GslMultiminFunctionAdapter : public gsl_multimin_function {
  public:
    /** \brief Constructor
     *
     *  \param func must be a functor.
     *  \param n_ Dimension of the function 
     */
    GslMultiminFunctionAdapter(const F& func,unsigned int n_) : func_(func) {
      f = &GslMultiminFunctionAdapter::call;
      n = n_;
      params=this;

    }
    private:
    /** \brief Method called by the GSL algorithm 
     */
    static double call(const gsl_vector* x, void *params) {
      std::vector<double> x_std;

      for(unsigned int i = 0; i < static_cast<GslMultiminFunctionAdapter*>(params)->n; ++i) {
	x_std.push_back( gsl_vector_get(x,i));
      }
      return static_cast<GslMultiminFunctionAdapter*>(params)->func_(x_std);
    }

    const F& func_; /*!< \brief F must be a functor. */
  };
}
#endif /* GSLMULTIMINFUNCTIONADAPTER_HPP */
