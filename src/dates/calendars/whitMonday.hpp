#ifndef JULIAN_WHITMONDAY_HPP
#define JULIAN_WHITMONDAY_HPP

#include <dates/calendars/holiday.hpp>
#include <dates/calendars/easter.hpp>

namespace julian {
  
  /**
   * @file   whitMonday.hpp
   * @brief  File contains WhitMonday class.
   */
  
  /** \ingroup calendar_holidays
   *  \brief Whit Monday
   *
   * Whit Monday is a moveable feast, celebrated on the Monday, 50 days after Easter.
   *
   */

  class WhitMonday: public Holiday {
  public:
    virtual bool operator()(Date) const;
    virtual WhitMonday* clone() const;
    virtual std::string info() const;
    virtual ~WhitMonday(){};
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
