#ifndef JULIAN_TIMEUNIT_HPP
#define JULIAN_TIMEUNIT_HPP

#include <string>
#include <iostream>

/**
 * @file   timeUnit.hpp
 * @brief  File contain time units and other useful enumerations.
 */

namespace julian {
  
  /** \ingroup dates
     
      TimeUnit represent the units of time, such as Day, Week, Month, Quarter and Year. The enumeration contains also pseudo-tenors such as OverNight, TommorowNext, Today, SpotNext and SpotDate. 
      Those names are degenerated tenors and cannot be used in all situations. This is because the properly usage of this tenors requires defining holidays and weekends. 
      They were defined to obtain unified method of constructing financial instruments. 
  */

  enum TimeUnit {
    DAY,
    WEEK,
    MONTH,
    QUARTER,
    YEAR,
    OVERNIGHT,
    TOMORROWNEXT,
    SPOTDATE,
    TODAY,
    SPOTNEXT
  };

  /** \ingroup dates
   *
   * \brief interface used by Boost serialization library
   */
  template<class Archive>
  void serialize(Archive & ar, TimeUnit & g, const unsigned int version) {
  }
  /** \ingroup dates
      
      Weekday enumeration contains the names of days of the week. The number value of each day is: Saturday = 0, Sunday = 1, Monday = 2, ... , Friday = 6. 
	  The numbers are set in such way because they are the result of calculating date.number mod 7 (1900-JAN-01 was Sunday). If one wants to check if for example 2015-10-28 is Friday he/she can write:
      \code{.cpp}
      Date d(2015, OCT, 28); 
      if(d.dateNumber() % 7 == FRI) { 
        std::cout<<"Friday!";
      } else { 
        std::cout<<"Sorry, but ... no!";
      }
      \endcode
  */
  enum Weekday {
    MON = 2,
    TUE = 3,
    WED = 4,
    THU = 5,
    FRI = 6,
    SAT = 0,
    SUN = 1
  };

  /** \ingroup dates
   * 
   * Frequency enumeration encapsulates the concept of frequency. It is helpful in constructing financial instruments such as bonds or swaps. The numbers represent number of months in every Frequency.
   */
  enum Frequency {
    NOFREQ = 0,
    MONTHLY = 1,
    QUARTERLY = 3,
    SEMIANNUALLY = 6,
    ANNUALLY = 12
  };
  /** \ingroup dates
   *\brief Overloading << operator for Frequency enumeration
   */
  inline std::ostream& operator<<(std::ostream & os, Frequency & f) {
    switch(f) {
    case NOFREQ: os << "NoFreq"; break;
    case MONTHLY: os << "monthly"; break;
    case QUARTERLY: os << "quarterly"; break;
    case SEMIANNUALLY: os << "semiannually"; break;
    case ANNUALLY: os << "annually"; break;
    }
    return os;
  }
  
  /** \ingroup dates
   * 
   * Enumeration contains the name of months. Months have number values that enables those types to be use in date creation:
   \code{.cpp}
   Date d1(2015,OCT,28); 
   Date d2(2011,JAN,13);
   Date d3(2020,MAR,1);
   \endcode
  */
  enum NameOfMonth {
    JAN = 1,
    FEB = 2,
    MAR = 3,
    APR = 4,
    MAY = 5,
    JUN = 6,
    JUL = 7,
    AUG = 8,
    SEP = 9,
    OCT = 10,
    NOV = 11,
    DEC = 12
  };

  /** \ingroup calendar_holidays
   * 
   * Enumeration contains names of day rolling convention that are used to adjust the payment date if payment is occurring at non-business day.
   */
  enum DayRollingConvention {
    FOLLOWING /*!< Move to the next working day*/,
    PRECEDING /*!< Move to the previous working day*/,
    MODIFIEDFOLLOWING /*!< Move to the next working day, unless this day extends to a next month, in that case the previous working day is used.*/,
    MODIFIEDPRECEDING /*!< Move to the previous working day, unless this day extends to a previous month, in that case the next working day is used.*/,
    UNADJUSTED /*!< Leave date unchanged*/,
    NEAREST /*!< Move to the nearest working day (prefer the next working day).*/
  };
  
  /** \ingroup calendar_holidays
   *
   * \brief  interface used by Boost serialization library 
   */
  template<class Archive>
  void serialize(Archive & ar, DayRollingConvention & g, const unsigned int version) {
  }
}  // namespace julian
#endif
