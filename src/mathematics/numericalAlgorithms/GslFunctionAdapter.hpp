#ifndef JULIAN_GSLFUNCTIONADAPTER_HPP
#define JULIAN_GSLFUNCTIONADAPTER_HPP

#include <gsl/gsl_math.h>


namespace julian {
  /**
   * @file   GslFunctionAdapter.hpp
   * @brief  File contains adapter of GSL Function.
   */


  /** \ingroup gsladapters
   *  \brief Class implements adapter for gsl_function.
   *
   * Class implements adapter for gsl_function. Class wraps callable class *F* so that it can be statically casted to gsl_function.
   *
   * The GSL algorithm requires the functions with two arguments: the double representing the argument of mathematical function and void pointer to data structure containing 
   * parameters of the function. When we want to pass lambda expression to GSL algorithm, we need to adopt interface of lambda expression to interface of gsl_function.
   */
  
  
  template< typename F >
  class GslFunctionAdapter : public gsl_function {
  public:

    /** \brief Constructor
     *
    *  \param functor must be a functor with overloaded **double operator()(double)**
    */
    GslFunctionAdapter(const F& functor) : functor_(functor) {
      function = &GslFunctionAdapter::call;
      params=this;
    }
  private:
    /** \brief Method called by the GSL algorithm 
     */
    static double call(double x, void *params) {
      return static_cast<GslFunctionAdapter*>(params)->functor_(x);
    }

    const F& functor_; /*!< \brief F must be a functor. **double operator()(double)** will be used by GSL algorithm */
  };
}
#endif
