#ifndef JULIAN_ALL_INSTRUMENTS_HPP
#define JULIAN_ALL_INSTRUMENTS_HPP


/**
* @file   _all_instruments.hpp
* @brief  Financial instruments module.
*/
/** \defgroup instruments Financial instruments
 * 
 * \brief Financial instruments: debt securities, linear derivatives, options etc.
 *  
 */

#include <instruments/linear/_all_linear.hpp>
#include <instruments/bonds/_all_bonds.hpp>
#include <instruments/options/_all_options.hpp>

#include <instruments/CashFlow.hpp>
#include <instruments/CashFlowVector.hpp>
#include <instruments/FixedCashFlow.hpp>
#include <instruments/FloatingCashFlow.hpp>
#include <instruments/CashFlowBuilder.hpp>

#endif
