#ifndef JULIAN_ALL_YEARFRACTION_HPP
#define JULIAN_ALL_YEARFRACTION_HPP
  /**
   * @file   _all_yearfraction.hpp
   * @brief  Year fraction module
   */
/** \defgroup yearfraction Year Fractions 
 *  \ingroup dates
 *  \brief Year fraction calculators.  
 *  
 * A system used to determine the number of days between two coupon dates, which is important in calculating accrued interest and present value when the next coupon payment is less than a full coupon period away. 
 * Each bond/money market has its own day-count convention. 
 *
 * Read more in \cite OGguide
 *
 */

#include <dates/yearFractions/yearFraction.hpp>
#include <dates/yearFractions/OneYF.hpp>
#include <dates/yearFractions/ActActISDA.hpp>
#include <dates/yearFractions/ActActAFB.hpp>
#include <dates/yearFractions/ACT360.hpp>
#include <dates/yearFractions/ACT360addOne.hpp>
#include <dates/yearFractions/ACT365.hpp>
#include <dates/yearFractions/E30360.hpp>
#include <dates/yearFractions/US30360.hpp>

#endif
