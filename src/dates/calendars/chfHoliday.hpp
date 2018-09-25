#ifndef JULIAN_CHFHOLIDAY_HPP
#define JULIAN_CHFHOLIDAY_HPP

#include <dates/calendars/holiday.hpp>
#include <dates/calendars/easter.hpp>

namespace julian {

/**
 * @file   chfHoliday.hpp
 * @brief  File contains CHFHoliday class.
 */

/** \ingroup calendar_holidays
 *  \brief Holidays set for CHF currency.
 *
 * CHF holiday set contains:
 *  * New Year (1st of January)
 *  * Berchtoldstag (2nd of January)
 *  * Good Friday
 *  * Easter Monday
 *  * Ascension Day
 *  * Whit Monday
 *  * Labour Day (1st of May)
 *  * National Day (1st of August)
 *  * Christmas (25th of December)
 *  * 2nd Day of Christmas (26th of December).
 *
 */
  
  class CHFHoliday: public Holiday {
  public:
    virtual bool operator()(Date) const;
    virtual CHFHoliday* clone() const;
    virtual std::string info() const;
    virtual ~CHFHoliday(){};
    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int){
      boost::serialization::base_object<Holiday>(*this);
    }
  };
} // namespace julian
#endif
