#ifndef JULIAN_ALL_INTERESTRATE_HPP
#define JULIAN_ALL_INTERESTRATE_HPP

/**
 * @file   _all_interestRate.hpp
 * @brief  Contains headers of all files with definitions of classes gathered in interest rate module.
 */

/** \defgroup interestRate Interest Rate 
 * \brief Interest rate and building blocks of interest rate object (compounding conventions).
 *
 *
 * This module contains interest rate object and its building blocks. Interest rate are build from:
 *  * year fraction (YearFraction) which calculates the year fraction between to dates according to appropriate convention 
 *  * compounding (Compounding) that encapsulates the method of calculating future value of present notional on the basis of interest rate and interest period.     
 */

#include <interestRates/interestRate.hpp>
#include <interestRates/simpleRate.hpp>
#include <interestRates/fractionRate.hpp>
#include <interestRates/CompoundedRate.hpp>
#include <interestRates/ExponentialRate.hpp>

#endif
