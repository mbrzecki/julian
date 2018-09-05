#ifndef JULIAN_CADHOLIDAY_HPP
#define JULIAN_CADHOLIDAY_HPP

#include <dates/calendars/holiday.hpp>
#include <dates/calendars/easter.hpp>

namespace julian {

  /**
   * @file   cadHoliday.hpp
   * @brief  File contains CADHoliday class.
   */
  
  /** \ingroup calendar_holidays
   *  \brief Holidays set for CAD currency.
   *
   * CAD holiday set contains:
   *  * New Year (1st of January, possible move to Monday)
   *  * Family Day, third Monday of February (since 2008) 
   *  * Good Friday
   *  * Victoria Day, the Monday on or preceding May 24th
   *  * Canada Day, July 1st (possibly moved to Monday)
   *  * Provincial Holiday, first Monday of August
   *  * Labour Day, first Monday of September
   *  * Thanksgiving Day, second Monday of October
   *  * Remembrance Day, November 11th (possibly moved to Monday)
   *  * Christmas, December 25th (possibly moved to Monday or Tuesday)
   *  * Boxing Day, December 26th (possibly moved to Monday or Tuesday)
   *
   */
 
  class CADHoliday: public Holiday {
  public:
    virtual bool operator()(Date) const;
    virtual CADHoliday* clone() const;
    virtual std::string info() const;
    virtual ~CADHoliday(){};
    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int){
      boost::serialization::base_object<Holiday>(*this);
    }
  };
}

#endif
