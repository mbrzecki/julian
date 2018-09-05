#ifndef JULIAN_JPYHOLIDAY_HPP
#define JULIAN_JPYHOLIDAY_HPP

#include <dates/calendars/holiday.hpp>
#include <dates/calendars/easter.hpp>

namespace julian {
  
  /**
   * @file   jpyHoliday.hpp
   * @brief  File contains JPYHoliday class.
   */
  
  /** \ingroup holidays
   *  \brief Holidays set for JPY currency.
   *
   * JPY holiday set contains:
   * * New Year's Day, January 1st
   * * Bank Holiday, January 2nd
   * * Bank Holiday, January 3rd
   * * Coming of Age Day, 2nd Monday in January (celebrated on 15th until 2000)
   * * National Foundation Day, February 11th
   * * Vernal Equinox
   * * Greenery Day, April 29th
   * * Constitution Memorial Day, May 3rd
   * * Holiday for a Nation, May 4th 
   * * Children's Day, May 5th
   * * Marine Day, 3rd Monday in July (was July 20th until 2003, not a holiday before 1996 )
   * * Respect for the Aged Day, 3rd Monday in September (was September 15th until 2003)
   * * Autumnal Equinox
   * * Health and Sports Day, 2nd Monday in October (was October 10th until 2000)
   * * National Culture Day, November 3rd
   * * Labour Thanksgiving Day, November 23rd
   * * Emperor's Birthday, December 23rd
   * * Bank Holiday, December 31st
   *
   *  Holidays falling on a Sunday are observed on the Monday following except for the bank holidays associated with the new year.
   * 
   * Additionally following dates are also non-working days.
   * * Marriage of Prince Akihito: 1959-Apr-10 
   * * Rites of Imperial Funeral: 1989-Feb-24
   * * Enthronement Ceremony: 1990-Nov-12
   * * Marriage of Prince Naruhito: 1993-Jun-09
   *
   */

  class JPYHoliday: public Holiday {
  public:
    virtual bool operator()(Date) const;
    virtual JPYHoliday* clone() const;
    virtual std::string info() const;
    virtual ~JPYHoliday(){};
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
