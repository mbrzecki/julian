#ifndef JULIAN_MARKETDATAUTILS_HPP
#define JULIAN_MARKETDATAUTILS_HPP

#include <marketData/ForwardCurve.hpp>
#include <marketData/interestRateCurves/InterpolatedCurve.hpp>
#include <marketData/interestRateCurves/curveSettings.hpp>

namespace julian {

  
  /**
   * @file   marketDataUtils.hpp
   * @brief  File contains simple functions helping to handle market data classes.
   */

  ir::InterpolatedCurve calculateYieldCurve(ir::InterpolatedCurve discounting_curve, ForwardCurve forward_curve, double asset_price);
  
}  // namespace julian
#endif




