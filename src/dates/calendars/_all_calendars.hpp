#ifndef JULIAN_ALL_CALENDARS_HPP
#define JULIAN_ALL_CALENDARS_HPP

/**
 * @file   _all_calendars.hpp
 * @brief  Calendar and holidays module.
 */

/** \defgroup calendar_holidays Calendar and Holidays 
 *  \ingroup dates
 *  \brief Calendars and holidays for a given currency, stock exchange, etc. 
 *
 *  The financial contracts have to start and be settled on business day. Apart from Saturdays and Sundays, 
	every currency/stock exchange/market has additional non-working days- usually religious or public holidays. 
	Module contains definition of holidays and set of holidays that allow to correctly established the commence and maturity of a contract.  
 * 
 */

#include <dates/calendars/calendar.hpp>
#include <dates/calendars/calendarBuilder.hpp>

#include <dates/calendars/holiday.hpp>
#include <dates/calendars/plnHoliday.hpp>
#include <dates/calendars/chfHoliday.hpp>
#include <dates/calendars/czkHoliday.hpp>
#include <dates/calendars/eurHoliday.hpp>
#include <dates/calendars/usdHoliday.hpp>
#include <dates/calendars/gbpHoliday.hpp>
#include <dates/calendars/hufHoliday.hpp>
#include <dates/calendars/jpyHoliday.hpp>
#include <dates/calendars/cadHoliday.hpp>

#include <dates/calendars/easter.hpp>
#include <dates/calendars/easterMonday.hpp>
#include <dates/calendars/corpusChristi.hpp>
#include <dates/calendars/goodFriday.hpp>
#include <dates/calendars/whitMonday.hpp>
#include <dates/calendars/fixedHoliday.hpp>

#include <dates/calendars/settlementDateConvention.hpp>
#include <dates/calendars/settlementFromSpot.hpp>
#include <dates/calendars/settlementFromExpiry.hpp>

#endif
