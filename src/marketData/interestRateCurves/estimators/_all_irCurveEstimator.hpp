#ifndef JULIAN_ALL_IRCURVEESTIMATOR_HPP
#define JULIAN_ALL_IRCURVEESTIMATOR_HPP

/**
* @file   _all_irCurveEstimator.hpp
* @brief  Interest rate curve estimators module.
*/
/** \defgroup irCurveEstimator Interest Rate Curve Estimators
 * \ingroup irCurve
 * 
 * \brief Algorithms of interest rate curve estimation
 */
#include <marketData/interestRateCurves/estimators/irCurveEstimator.hpp>

#include <marketData/interestRateCurves/estimators/algebraicBootstrapper.hpp>
#include <marketData/interestRateCurves/estimators/rootFindingBootstrapper.hpp>
#include <marketData/interestRateCurves/estimators/constrainedSmoother.hpp>
#include <marketData/interestRateCurves/estimators/unconstrainedSmoother.hpp>

#include <marketData/interestRateCurves/estimators/costFunctions/_all_costIrFunctions.hpp>

#endif
