#ifndef JULIAN_ALL_INTERPOLATION_HPP
#define JULIAN_ALL_INTERPOLATION_HPP

  /**
   * @file   _all_interpolation.hpp
   * @brief  Interpolation module
   */

/** \defgroup interpolation Interpolation methods 
 *
 *  \ingroup mathematics
 *
 *  \brief Interpolation techniques
 *  
 * An interpolation is a mathematical method of estimating interpolation function (called interpolant) which agrees with values for a given discrete set of points. Usually interpolant has a form of piecewise function - 
 a function that is defined by sub functions,
 each applying to a certain interval of the function domain. Most common are piecewise linear function or spline functions. 

 * We can distinguish two types of interpolation techniques: local and global. The interpolation methods that are based on "nearest neighbours" points are called local interpolation techniques. 
	They are computational efficient because they do not require fitting to the whole set of points. Major disadvantage of these schemes is that they do not produce interpolant with continuous derivatives. 
	When a continuity of derivatives is a concern, one may use global methods like spline (e.g cubic spline) and sub-spline function (e.g. AKIMA interpolation). The disadvantage of these methods is non-locality, 
	which means that change of value at one node cause changes not only in its surrounding neighbourhood (see \cite hagan1), but also at distant intervals. 
 *
 * 
 * 
 See more: \cite intphys  \cite NumRec \cite OGinter
 *
 */

#include <mathematics/interpolation/interpolation.hpp>

#include <mathematics/interpolation/cubicInterpolation.hpp>
#include <mathematics/interpolation/naturalCubicSpline.hpp>
#include <mathematics/interpolation/flatBackward.hpp>
#include <mathematics/interpolation/flatForward.hpp>
#include <mathematics/interpolation/linearInterpolation.hpp>
#include <mathematics/interpolation/logarithmicInterpolation.hpp>
#include <mathematics/interpolation/quadraticInterpolation.hpp>
#include <mathematics/interpolation/polynomialInterpolation.hpp>
#include <mathematics/interpolation/AKIMA.hpp>
#include <mathematics/Interpolation/steffenInterpolation.hpp>

#endif
