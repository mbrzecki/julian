#ifndef JULIAN_GSLFUNCTIONFDFADAPTER_HPP
#define JULIAN_GSLFUNCTIONFDFADAPTER_HPP

#include <gsl/gsl_math.h>


namespace julian {
 
/**
 * @file   GslFunctionFdfAdapter.hpp
 * @brief  File contains adapter of GSL Function.
 */
 
  /** \ingroup gsladapters
   *  \brief Class implements adapter for gsl_function_fdf.
   *
   * Class implements adapter for gsl_function_fdf. Class wraps callable class F and dF so that it can be statically casted to gsl_function_fdf.
   * F must be a functor with overloaded **double operator()(double)** implementing value of the function.
   * dF must be a functor with overloaded **double operator()(double)** implementing derivative of the function.	 
   */

  template< typename F, typename dF >
  class GslFunctionFdfAdapter : public gsl_function_fdf {
  public:

    /** \brief Constructor
     *
	 * **F** must be a functor with overloaded **double operator()(double)** implementing value of the function.
	 * **dF** must be a functor with overloaded **double operator()(double)** implementing derivative of the function.	 
     */
    GslFunctionFdfAdapter(const F& kf, const dF& kdf) : f_(kf), df_(kdf) {
      f   = &GslFunctionFdfAdapter::call_f;
      df  = &GslFunctionFdfAdapter::call_df;
      fdf = &GslFunctionFdfAdapter::call_fdf;
      params=this;
    }
  private:
    /** \brief Method called by the GSL algorithm 
     * 
     * \return Returns value of called gsl_function_fdf for x. 
     */
    static double call_f(double x, void *params) {
      return static_cast<GslFunctionFdfAdapter*>(params)->f_(x);
    }
    
    /** \brief Method called by the GSL algorithm 
     * 
     * \return Returns derivative of gsl_function_fdf for x. 
     */
    static double call_df(double x, void *params) {
      return static_cast<GslFunctionFdfAdapter*>(params)->df_(x);
    }
    
    /** \brief Method called by the GSL algorithm 
     * 
     * \return Returns by reference value of gsl_function_fdf and derivative of gsl_function_fdf for x. 
     */
    static void call_fdf(double x, void * params, double* f, double* df) {
      (*f)  = static_cast<GslFunctionFdfAdapter*>(params)->f_(x);
      (*df) = static_cast<GslFunctionFdfAdapter*>(params)->df_(x);
    }

    const F& f_;   /*!< \brief F must be a functor. */
    const dF& df_; /*!< \brief dF must be a functor. dF is derivative of F. */
  }; 
}
#endif /* GSLFDFFUNCTIONADAPTER_HPP */
