#ifndef JULIAN_ALL_OPTIONGREEKS_HPP
#define JULIAN_ALL_OPTIONGREEKS_HPP

  /**
   * @file   _all_optionGreeks.hpp
   * @brief  Includes objects related to Greeks.
   */

/** \defgroup optiongreeks PV and Greeks 
 *  \ingroup pricing_engines
 *  \brief Definition of classes that are used to construct risk reports about options PV and Greeks 
 * 
 * Module contains definition of classes that are used to construct risk reports about options PV and Greeks.
 * The OptionGreeks are implemented as Decorator (\ref cpp_dp_decorator). The basic report, calculating and maintaining only the PV of the option, 
 * is decorated with modules calculating different Greeks. 
 *
 */


#include <pricingEngines/optionGreeks/optionGreeks.hpp>
#include <pricingEngines/optionGreeks/optionGreeksBuilder.hpp>
#include <pricingEngines/optionGreeks/optionPV.hpp>
#include <pricingEngines/optionGreeks/optionGreeksDecorator.hpp>
#include <pricingEngines/optionGreeks/optionDelta.hpp>
#include <pricingEngines/optionGreeks/optionGamma.hpp>
#include <pricingEngines/optionGreeks/optionVega.hpp>
#include <pricingEngines/optionGreeks/optionVanna.hpp>
#include <pricingEngines/optionGreeks/optionVolga.hpp>
#include <pricingEngines/optionGreeks/optionTheta.hpp>
#endif
