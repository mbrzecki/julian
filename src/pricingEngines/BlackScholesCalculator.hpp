#ifndef JULIAN_BLACKSHOLESCALCULATOR_HPP
#define JULIAN_BLACKSHOLESCALCULATOR_HPP

#include <instruments/instrumentAuxiliaryTypes.hpp>

namespace julian {
  /**
   * @file   BlackScholesCalculator.hpp
   * @brief  File contains small functions used to calculate PV and Greeks using Black-Scholes model.
   */
  double prizeBlackScholes(double S,
			   double K,
			   double DFr,
			   double DFq,
			   double vol,
			   double t,
			   CallPut icp);
  double calculateImpliedVolatility(double S,double K, double DFr,double DFq, double prize, double t, CallPut icp);
  double calculateBlackScholesDelta(double S,double K, double DFr,double DFq, double vol, double t, CallPut icp);
  double calculateStrikeFromCallDelta(double spot,double DFr,double DFq,double vol,double t,double delta);
  double calculateStrikeFromPutDelta (double spot,double DFr,double DFq,double vol,double t,double delta); 
}

#endif
