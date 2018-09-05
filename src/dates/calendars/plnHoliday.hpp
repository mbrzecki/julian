#ifndef JULIAN_PLNHOLIDAY_HPP
#define JULIAN_PLNHOLIDAY_HPP

#include <dates/calendars/holiday.hpp>
#include <dates/calendars/easter.hpp>

namespace julian {

  /**
   * @file   plnHoliday.hpp
   * @brief  File contains PLNHoliday class.
   */
  
  /** \ingroup calendar_holidays
   *  \brief Holidays set for PLN currency.
   *
   * PLN holiday set contains:
   *  * New Year (1st of January)
   *  * Epiphany (6th of January after 2010)
   *  * Labour Day (1st of May)
   *  * Constitution Day (3rd of May)
   *  * Easter Monday
   *  * Corpus Christi 
   *  * Assumption of the Blessed Virgin Mary (15th of August)
   *  * All Saints Day (1st of November)
   *  * Independence Day (11th of November)
   *  * Christmas (25th of December)
   *  * 2nd Day of Christmas (26th of December).
   *
   */
  
  
  class PLNHoliday: public Holiday {
  public:
    virtual bool operator()(Date) const;
    virtual PLNHoliday* clone() const;
    virtual std::string info() const;
    virtual ~PLNHoliday(){};
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
