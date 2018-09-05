#ifndef JULIAN_ALL_NUMERICALALGORITHM_HPP
#define JULIAN_ALL_NUMERICALALGORITHM_HPP

  /**
   * @file   _all_numericalAlgorithm.hpp
   * @brief  Numerical Algorithms module
   */

/** \defgroup num_alg Numerical Algorithms 
 *  \ingroup mathematics
 * \brief Numerical algorithms: root-finders, minimizers, integral calculators etc.
 *
 * Most of numerical algorithms gathered in this module comes from GNU Scientific Library (<a href = "https://www.gnu.org/software/gsl/manual/gsl-ref.pdf">GSL Manual</a>). 
 *
 * The manual of GSL contains brief introduction description of each algorithm with a rich list of references and recommendations for further reading. 
 * Still  <i>Numerical Recipes</i>(\cite NumRec) should be considered as best introductory book about numerical analysis. 
 * The book covers wide range of topics from standard problems (interpolation, integration etc) to more advanced subjects. 
 * Virtually all methods discussed in the book are implemented with code printed in the book. 
 *
 * Another books covering subject of numerical techniques are: Computational Physics \cite Sherer and Introductory computational physics \cite intphys.
 *
 */

#include <mathematics/numericalAlgorithms/integrate.hpp>
#include <mathematics/numericalAlgorithms/QuadraticProgrammingSolver.hpp>
#include <mathematics/numericalAlgorithms/simulatedAnnealing.hpp>


/** \defgroup minimizers Optimization algorithms
 *  \ingroup num_alg
 *  \brief Routines for finding minima of arbitrary one- or multi- dimensional functions
 *
 * The minimum finding routines can be divided into two groups:
 * * derivative-free optimization: Algorithms that that does not use derivative information in the classical sense to find optimal solutions (see julian::NonDerivativeMinimizer)
 * * derivative-based optimization: Algorithms basing on the calculation of gradient of cost function (see DerivativeMinimizer)
 *
 *  Good introduction to minimization techniques see Chapter 10 of \cite NumRec and Chapter 6 of \cite Sherer. 
 */

#include <mathematics/numericalAlgorithms/Minimizer1d.hpp>
#include <mathematics/numericalAlgorithms/nonDerivativeMinimizer.hpp>
#include <mathematics/numericalAlgorithms/derivativeMinimizer.hpp>


/** \defgroup rootfinding Root-Finding algorithms 
 *  \ingroup num_alg
 *  \brief Routines used to find the argument \f$x\f$ that \f$f(x) = 0\f$ 
 *
 * The root-finding routines can be divided into two groups:
 * * derivative-free: Algorithms that that does not use derivative information in the classical sense to find solutions. Usually those are bracketing algorithms
 * * derivative-based: Algorithms basing on the calculation of gradient. 
 */


#include <mathematics/numericalAlgorithms/bracketingRootFinder.hpp>
#include <mathematics/numericalAlgorithms/derivativeRootFinder.hpp>

/** \defgroup gsladapters GSL function adapters 
 *  \ingroup num_alg
 *  \brief Wrappers for GSL functions
 *
 * The most important aspect of numerical routines is providing the function to the numerical algorithm. 
 * The GSL is a library written in \b C, so it does not take of the advantages of OOP. Instead of objects, 
 * GSL is using structures containing pointer to functions. The \b C functions are free functions and can't hold state. 
 * The fact that \b C functions can't hold state, makes parametrization of the function harder. In GSL this problem was solved
 * by adding the void pointer to interface of the functions that are passed to numerical routines. 
 *
 * Those void pointers reference the structure holding the function's parameters.
 * The numerical algorithm does not have any information about the structure pointed to void pointer, it just passed is to function, 
 * where pointer is casted to proper structure and dereferenced.   
 * 
 * As this mechanism is quite complicated and hard to use, we provided the wrapper objects that map \b C++ functors (structure/classes with overloaded operator() method) to GSL functions.
 * Wrapper decouples data and method of functor and passes them as void pointer and free function. 
 *
 *
 * Simple example below:
 *
 * \includelineno voidpointer.cpp
 * \b Output
 * @verbinclude voidpointer.dox
 */
#include <mathematics/numericalAlgorithms/GslFunctionAdapter.hpp>
#include <mathematics/numericalAlgorithms/GslFunctionFdfAdapter.hpp>
#include <mathematics/numericalAlgorithms/GslMultiminFunctionAdapter.hpp>
#include <mathematics/numericalAlgorithms/GslMultiminFunctionFdfAdapter.hpp>

#endif
