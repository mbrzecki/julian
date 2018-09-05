#ifndef _ALL_MATHEMATICS_HPP
#define _ALL_MATHEMATICS_HPP

  /**
   * @file   _all_mathematics.hpp
   * @brief  Mathematics module
   */

/** \defgroup mathematics Mathematics
 * \brief Mathematical and numerical tools
 *
 * Module contains the numerical and mathematical tools such as:
 * * interpolations
 * * numerical algorithm (adapters to <a href="https://www.gnu.org/software/gsl/">GNU Scientific Library</a> functions)
 * * statistic calculators
 * * probability distribution
 * * regressions
 * * stochastic processes
 * * random number generators
 *
 */
#include <mathematics/mathUtils.hpp>
#include <mathematics/interpolation/_all_interpolation.hpp>
#include <mathematics/numericalAlgorithms/_all_numericalAlgorithm.hpp>
#include <mathematics/statistics/_all_statistics.hpp>
#include <mathematics/distributions/_all_probabilityDistribution.hpp>
#include <mathematics/regressions/_all_regressions.hpp>
#include <mathematics/stochasticProcesses/_all_stochasticProcesses.hpp>
#include <mathematics/RNGs/_all_RNGs.hpp>
#endif
