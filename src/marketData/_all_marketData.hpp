#ifndef JULIAN_ALL_MARKETDATA_HPP
#define JULIAN_ALL_MARKETDATA_HPP

  /**
   * @file   _all_marketData.hpp
   * @brief  Market Data module
   */

/** \defgroup marketdata Market Data 
 *  
 * This group contains classes helping to handle (load, transform, interpolate) market data. Particularly in this group we have:
 * * interest rate curve,
 * * volatility surfaces,
 * * forward curve.
 */
#include <marketData/volatility/_all_volatilitySurface.hpp>
#include <marketData/interestRateCurves/_all_Curves.hpp>
#include <marketData/ForwardCurve.hpp>
#include <marketData/marketDataUtils.hpp>

#endif 
