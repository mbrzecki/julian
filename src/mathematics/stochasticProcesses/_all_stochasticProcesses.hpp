#ifndef JULIAN_ALL_STOCHASTICPROCESSES_HPP
#define JULIAN_ALL_STOCHASTICPROCESSES_HPP
  /**
   * @file   _all_stochasticProcesses.hpp
   * @brief  Stochastic processes module.
   */
/** \defgroup stochasticProcesses Stochastic Processes 
 *  \ingroup mathematics
 *
 * \brief Classes implementing stochastic processes.
 * 
 * Module covers:
 * * definition of stochastic processes (like Arithmetic/Geometric Brownian motion etc.);
 * * utility classes (like path). 
 * 
 * Good introduction to the topic of stochastic processes is \cite stochcalculus and \cite mathofder.
 */


#include <mathematics/stochasticProcesses/path.hpp>
#include <mathematics/stochasticProcesses/stochasticProcess.hpp>
#include <mathematics/stochasticProcesses/arithmeticBrownianMotion.hpp>
#include <mathematics/stochasticProcesses/geometricBrownianMotion.hpp>
#include <mathematics/stochasticProcesses/cirProcess.hpp>
#include <mathematics/stochasticProcesses/hestonProcess.hpp>

#endif
