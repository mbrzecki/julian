#ifndef JULIAN_CZKHOLIDAY_HPP
#define JULIAN_CZKHOLIDAY_HPP

#include <dates/calendars/holiday.hpp>
#include <dates/calendars/easter.hpp>

namespace julian {

  /**
   * @file   czkHoliday.hpp
   * @brief  File contains CZKHoliday class.
   */
  
  /** \ingroup calendar_holidays
   *  \brief Holidays set for CZK currency.
   *
   *  CZK holiday set contains:
   *  * New Year's Day (1st of January)
   *  * Easter Monday
   *  * Labour Day (1st of May)
   *  * Liberation Day (8th of May)
   *  * SS Cyril and Methodius (5th of July)
   *  * Jan Hus Day (6th of July)
   *  * Czech Statehood Day (28th of September)
   *  * Independence Day (28th of October)
   *  * Struggle for Freedom and Democracy Day (17th of November)
   *  * Christmas Eve (24th of December)
   *  * Christmas (25th of December)
   *  * St. Stephan Day (26th of December).
   * 
   * Source: <a href = "https://www.cnb.cz/en/public/media_service/schedules/media_svatky.html"> CZK Bank Holidays </a>
   */
  
  class CZKHoliday: public Holiday {
  public:
    virtual bool operator()(Date) const;
    virtual CZKHoliday* clone() const;
    virtual std::string info() const;
    virtual ~CZKHoliday(){};
    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int){
      boost::serialization::base_object<Holiday>(*this);
    }
  };
}  // namespace julian
#endif
