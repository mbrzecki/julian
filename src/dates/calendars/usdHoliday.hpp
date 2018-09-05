#ifndef JULIAN_USDHOLIDAY_HPP
#define JULIAN_USDHOLIDAY_HPP

#include <dates/calendars/holiday.hpp>
#include <dates/calendars/easter.hpp>

namespace julian {

  /**
   * @file   usdHoliday.hpp
   * @brief  File contains USDHoliday class.
   */
  
  /** \ingroup calendar_holidays
   *  \brief Holidays set for USD currency.
   *
   * USD holiday set contains:
   *  * New Year's Day (1st of January, possibly moved to Monday if on Sunday)
   *  * Martin Luther King's birthday (third Monday in January)
   *  * Washington's birthday (third Monday in February)
   *  * Good Friday
   *  * Memorial Day (last Monday in May)
   *  * Independence Day (4th of July, Monday if Sunday or Friday if Saturday)
   *  * Labour Day (first Monday in September)
   *  * Columbus Day (second Monday in October)
   *  * Veteran's Day  (11th of November, Monday if Sunday or Friday if Saturday)
   *  * Thanksgiving Day (fourth Thursday in November)
   *  * Christmas (25th of December, Monday if Sunday or Friday if Saturday).
   *
   */
  
  class USDHoliday: public Holiday {
  public:
    virtual bool operator()(Date) const;
    virtual USDHoliday* clone() const;
    virtual std::string info() const;
    virtual ~USDHoliday(){};
    
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
