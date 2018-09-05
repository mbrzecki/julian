#ifndef JULIAN_CALENDAR_HPP
#define JULIAN_CALENDAR_HPP

#include <dates/date.hpp>
#include <iostream>
#include <dates/tenor.hpp>
#include <dates/timeUnit.hpp>
#include <vector>
#include <utils/smartPointer.hpp>
#include <dates/calendars/holiday.hpp>
#include <dates/calendars/settlementDateConvention.hpp>
#include <dates/calendars/settlementFromSpot.hpp>



namespace julian {
  /**
   * @file   calendar.hpp
   * @brief  File contains the definition of calendar class.
   */
  
  /** \ingroup calendar_holidays
   * \brief Class implements calendar object.
   * 
   * This class provides methods for determining whether a date is a business day or a holiday. It also allows to increment or decrement a date of a given number of business days or by a given tenor. 
   * The calendar also provides methods for calculating number of working days/holidays between two dates. 
   *
   */
 
  class Calendar {
  public:
    Calendar();
    Calendar(DayRollingConvention, int, const std::vector<Date>&, const std::vector<Date>& ,const std::vector<SmartPointer<Holiday> >&, bool end_of_month,const SmartPointer<SettlementDateConvention>&);
    
    bool isBusinessDay(const Date&) const;     
    bool isHoliday(const Date&) const;         
    bool isWeekend(const Date&) const;
    Date adjust(const Date&) const;
    
    int businessDaysBetween(const Date&, const Date&) const; 
    int numberOfHolidaysBetween(const Date&, const Date&) const;
    Date workingDays(const Date&, int) const; 
  
    Date getSpot(const Date&) const;
    Date getON(const Date&) const;
    Date getTN(const Date&)const;

    Date expiryDate(const Date& d, const Tenor& t) const;
    Date settlementDate(const Date& d, const Tenor& t) const;

    int getSpotLag() const;    
    bool isEndOfMonth(const Date&) const;
    Date getLastWorkingDateOfMonth(const Date&) const;
  
    ~Calendar(){};
    
    friend std::ostream& operator<<(std::ostream&, Calendar&);
    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & ar, const unsigned int){
      ar & BOOST_SERIALIZATION_NVP(spot_lag_);
      ar & BOOST_SERIALIZATION_NVP(day_rolling_convention_);
      ar & BOOST_SERIALIZATION_NVP(end_of_month_);
      ar & BOOST_SERIALIZATION_NVP(business_days_);
      ar & BOOST_SERIALIZATION_NVP(holidays_dates_);
      ar & BOOST_SERIALIZATION_NVP(holidays_);
      ar & BOOST_SERIALIZATION_NVP(settlement_);
    }

    int spot_lag_;                                      /*!< \brief This integer define how many working days is between today date and spot date.*/
    DayRollingConvention day_rolling_convention_;       /*!< \brief Variable defines the day rolling convention*/
    bool end_of_month_;                                 /*!< \brief Boolean variable defining if end of month convention is applied.*/
    std::vector<Date> business_days_;                   /*!< \brief Vector of dates that are recognized as working dates.*/
    std::vector<Date> holidays_dates_;                  /*!< \brief Vector of dates that are recognized as holidays.*/
    std::vector<SmartPointer<Holiday> > holidays_;      /*!< \brief Vector of holidays objects (see Holiday).*/
    SmartPointer<SettlementDateConvention> settlement_; /*!< \brief This variable holds object defining settlement date convention.*/
  };
}

#endif
