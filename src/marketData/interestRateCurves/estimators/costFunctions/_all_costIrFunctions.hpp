#ifndef JULIAN_ALL_IRCOSTFUNCTIONS_HPP
#define JULIAN_ALL_IRCOSTFUNCTIONS_HPP

/**
* @file   _all_costIrFunctions.hpp
* @brief  Classes implementing cost function for interest rate curve estimators.
*/
/** \defgroup irCurveCost Interest Rate Curve Cost Functions
 * \ingroup irCurveEstimator
 *
 * \brief Cost function for interest rate curve bootstrappers based on optimization technique
 *
 * For example implementation of Decorator Pattern see \ref cpp_dp_decorator .
 *
 **/

#include <marketData/interestRateCurves/estimators/costFunctions/SmootherCostFunction.hpp>
#include <marketData/interestRateCurves/estimators/costFunctions/SmoothZeroCouponRates.hpp>
#include <marketData/interestRateCurves/estimators/costFunctions/SmoothForwardRates.hpp>
#include <marketData/InterestRateCurves/estimators/costFunctions/CostFunctionDecorator.hpp>
#include <marketData/InterestRateCurves/estimators/costFunctions/FirstDerivativeCostFunction.hpp>
#include <marketData/InterestRateCurves/estimators/costFunctions/SecondDerivativeCostFunction.hpp>

#endif
