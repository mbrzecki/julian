#ifndef JULIAN_EURHOLIDAY_HPP
#define JULIAN_EURHOLIDAY_HPP

#include <dates/calendars/holiday.hpp>
#include <dates/calendars/easter.hpp>

namespace julian {
  /**
   * @file   eurHoliday.hpp
   * @brief  File contains EURHoliday class.
   */

  /** \ingroup calendar_holidays
   *  \brief TARGET2 holiday set.
   *
   *  TARGET2 holiday set contains:
   *  * New Year's Day (1st of January)
   *  * Worker's Day (1st of May)
   *  * Good Friday
   *  * Easter Monday
   *  * Christmas (25th of December)
   *  * 2nd Day of Christmas (26th of December).
   *
   */

  class EURHoliday: public Holiday {
  public:
    virtual bool operator()(Date) const;
    virtual EURHoliday* clone() const;
    virtual std::string info() const;
    virtual ~EURHoliday(){};
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
