#ifndef JULIAN_GOODFRIDAY_HPP
#define JULIAN_GOODFRIDAY_HPP

#include <dates/calendars/holiday.hpp>
#include <dates/calendars/easter.hpp>

namespace julian {

  /**
   * @file   goodFriday.hpp
   * @brief  File contains GoodFriday class.
   */
  
  /** \ingroup calendar_holidays
   *  \brief Good Friday
   *
   * Good Friday is a moveable feast, celebrated on the Friday before Easter.
   * 
   */

  class GoodFriday: public Holiday {
  public:
    virtual bool operator()(Date) const;
    virtual GoodFriday* clone() const;
    virtual std::string info() const;
    virtual ~GoodFriday(){};
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
