#ifndef JULIAN_CALENDARBUILDER_HPP
#define JULIAN_CALENDARBUILDER_HPP

#include <dates/date.hpp>
#include <iostream>
#include <dates/tenor.hpp>
#include <dates/timeUnit.hpp>
#include <vector>
#include <dates/calendars/calendar.hpp>
#include <dates/calendars/fixedHoliday.hpp>

namespace julian {

  /**
   * @file   calendarBuilder.hpp
   * @brief  File contains the definition of calendar builder class.
   */
  
  
  /** \ingroup calendar_holidays
   * \brief Class implements builder design pattern supporting construction of calendars.
   *
   * Class provides simple and clear interface for constructing the calendar. The class contains the methods through which the parameters of calendar are established. The user does not have to provide all required parameters. If some parameters are not given builder sets following default setting:
   * * day rolling convention: Unadjusted,
   * * spot lag: 0 days,
   * * no end of month adjustment,
   * * no holidays.
   *
   */

  
  class BuildCalendar {
  public: 
    BuildCalendar();

    BuildCalendar& withConvention(const DayRollingConvention& convention);
    BuildCalendar& withSpotLag(const int spot_lag);
    BuildCalendar& addHoliday(const Date& holiday);
    BuildCalendar& addHoliday(const NameOfMonth month,const int day);
    BuildCalendar& addHoliday(const SmartPointer<Holiday>& holidays);
    BuildCalendar& removeHoliday(const Date& business_day);
    BuildCalendar& endOfMonth();
    BuildCalendar& withSettlementDateConvention(SmartPointer<SettlementDateConvention>);
    
    operator Calendar();
    
  private:
    DayRollingConvention convention_; /*!< \brief day rolling 
       
				       Day rolling convention provided by method withConvention*/
    
    int spot_lag_; /*!< \brief spot lag 
		 
		 Size of spot lag provided by method withSpotLag*/
    
    bool end_of_month_; /*!< \brief end of month convention
			
			 Boolean value that if it is true the calendar will adjust date according to end of month convention*/
    
    std::vector<Date> business_days_vector_;  /*!< \brief working days 

					       Vector of dates which should be considered as business days - set created by removeHoliday method*/
    
    std::vector<Date> holidays_vector_; /*!< \brief holidays as dates
				      
				      Vector of dates which should be considered as holidays days - set created by addHoliday method*/
    
    std::vector<SmartPointer<Holiday> > holidays_; /*!< \brief predefined holidays
						    
						    Vector of predefined holidays - set created by addHoliday method*/
    
    SmartPointer<SettlementDateConvention> settlement_; /*!< \brief settlement date convention
						    
						    Object implementing settlement date convention.*/
  };
}
#endif
