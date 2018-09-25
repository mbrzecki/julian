#ifndef JULIAN_ALL_DATES_HPP
#define JULIAN_ALL_DATES_HPP

/**
 * @file   _all_dates.hpp
 * @brief  Contains headers of all files with definitions of classes gathered in dates calendar and holidays module.
 */

/** \defgroup dates Dates, calendar and holidays 
 *  \brief Dates and everything else.
 * 
 *  Module contains date, time units and tenor classes. It also contains the calendar class that allows to calculate the tenor according to specific day rolling convention, spot lag value and set of holidays. 
 *	In this module the year fraction calculators are also gathered. 
 */


#include <dates/date.hpp>
#include <dates/tenor.hpp>
#include <dates/timeUnit.hpp>

#include <dates/calendars/_all_calendars.hpp>
#include <dates/yearFractions/_all_yearfraction.hpp>
#include <dates/timeGrids/_all_timeGrids.hpp>

#endif
