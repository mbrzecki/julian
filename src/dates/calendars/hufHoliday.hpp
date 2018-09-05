#ifndef JULIAN_HUFHOLIDAY_HPP
#define JULIAN_HUFHOLIDAY_HPP

#include <dates/calendars/holiday.hpp>
#include <dates/calendars/easter.hpp>

namespace julian {
  
  /**
   * @file   hufHoliday.hpp
   * @brief  File contains HUFHoliday class.
   */
  
  /** \ingroup calendar_holidays
   *  \brief Holidays set for HUF currency.
   *
   * HUF holiday set contains:
   *  * New Year's Day (1st of January)
   *  * National Day (15th of March)
   *  * Easter Monday
   *  * Whit Monday
   *  * Labour Day (1st of May)
   *  * Constitution Day (20th of August)
   *  * Republic Day (23th of October)
   *  * All Saints Day (1st of November)
   *  * Christmas (25th of December)
   *  * 2nd Day of Christmas (26th of December).
   *
   */

  class HUFHoliday: public Holiday {
  public:
    virtual bool operator()(Date) const;
    virtual HUFHoliday* clone() const;
    virtual std::string info() const;
    virtual ~HUFHoliday(){};
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
