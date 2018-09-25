#ifndef JULIAN_GBPHOLIDAY_HPP
#define JULIAN_GBPHOLIDAY_HPP

#include <dates/calendars/holiday.hpp>
#include <dates/calendars/easter.hpp>

namespace julian {

  /**
   * @file   gbpHoliday.hpp
   * @brief  File contains GBPHoliday class.
   */

  /** \ingroup holidays
   *  \brief Holidays set for GBP currency.
   *
   * GBP holiday set contains:
   *  * New Year's Day (possibly moved to Monday)
   *  * Good Friday
   *  * Easter Monday
   *  * first Monday of May (Early May Bank holiday)
   *  * last Monday of May (Spring Bank holiday)
   *  * last Monday of August (Summer Bank holiday)
   *  * Christmas (possibly moved to Monday or Tuesday)
   *  * Boxing Day (possibly moved to Monday or Tuesday).
   *
   * \warning Class does not contain irregular holidays that occurred once (e.g. royal anniversaries).
   *
   */
  
  class GBPHoliday: public Holiday {
  public:
    virtual bool operator()(Date) const;
    virtual GBPHoliday* clone() const;
    virtual std::string info() const;
    virtual ~GBPHoliday(){};
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
