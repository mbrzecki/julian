#ifndef JULIAN_MATHUTILS_HPP
#define JULIAN_MATHUTILS_HPP

namespace julian {

  /**
   * @file   mathutils.hpp
   * @brief  File contains small mathematical classes and functions.
   */
  
  /** \ingroup mathematics
   *  \brief collection of enumerations, simple classes and small functions used in mathematical computations 
   * 
   * Enumeration list types defining the computation of numerical derivatives by finite differencing
   */  
  enum class NumDiffScheme {
    CNTR /*!< Central differencing: 
	  * * first order \f$\frac{df}{dx}(x) = \frac{f(x+h)-f(x-h)}{2h}\f$
	  * * second order \f$\frac{d^2f}{dx^2}(x) = \frac{f(x+h)-2f(x) + f(x-h)}{h^2}\f$
	  */,
    FWD  /*!< Forward differencing:
	  * * first order \f$\frac{df}{dx}(x) = \frac{f(x+h)-f(x)}{h}\f$
	  * * second order \f$\frac{d^2f}{dx^2}(x) = \frac{f(x+2h)-2f(x+h)+f(x)}{h^2}\f$
	  */,
    BWD  /*!< Backward differencing: 
	  * *  first order \f$\frac{df}{dx}(x) = \frac{f(x)-f(x-h)}{h}\f$
	  * *  second order \f$\frac{df}{dx}(x) = \frac{f(x)-2f(x-h) + f(x-2h)}{h^2}\f$
	  */
  };
}
#endif 
