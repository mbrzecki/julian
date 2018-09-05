#ifndef JULIAN_EASTERMONDAY_HPP
#define JULIAN_EASTERMONDAY_HPP

#include <dates/calendars/holiday.hpp>
#include <dates/calendars/easter.hpp>

namespace julian {

  /**
   * @file   easterMonday.hpp
   * @brief  File contains EasterMonday class.
   */
  
  /** \ingroup calendar_holidays
   *  \brief Easter Monday
   *
   * Easter Monday is a moveable feast, celebrated on the first Monday after Easter.
   *
   */

  class EasterMonday: public Holiday {
  public:
    virtual bool operator()(Date) const;
    virtual EasterMonday* clone() const;
    virtual std::string info() const;
    virtual ~EasterMonday(){};
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
