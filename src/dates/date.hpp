#ifndef JULIAN_DATE_HPP
#define JULIAN_DATE_HPP

#include <stdlib.h>

#include <iostream>
#include <string>

#include <dates/timeUnit.hpp>
#include <dates/tenor.hpp>
#include <boost/serialization/export.hpp>

namespace julian {
  /**
   * @file   date.hpp
   * @brief  File contains definition of date class.
   */

  /** \ingroup dates
   *  \brief Class implements a date object.
   *
   *  This class provides methods to inspect dates as well as methods and operators which implement a limited date algebra (moving by year, month, day, or moving to end of month or year).
   *
   *  \warning Date object can represent only the dates between 1900JAN01 and 2200DEC31
   */

  class Date {
  public:
    /** \brief Date formats
     */
    enum class Format {
      date1 /*!< Format 2015-12-31*/,
      date2 /*!< Format 15-12-31*/,
      date3 /*!< Format 2015DEC31*/,
      date4 /*!< Format 2015/12/31*/ ,
      date5 /*!< Format 31/12/2015*/,
      date6 /*!< Format 31DEC2015*/
    };
    
    Date();
    Date(int year, int month, int day);
    Date(int yyyymmdd);
    Date(std::string, Date::Format);


    
    std::string getString() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    int getN() const;

    void setDay(int);
    void setMonth(int);
    void setYear(int);

    void moveToEndOfMonth();
    void moveToEndOfYear();

    bool isValid() const;
    bool isLeapYear() const;
    bool isEndOfMonth() const;
    bool isEndOfYear() const;

    void operator++();
    void operator--();

    void operator+=(Tenor t);
    void operator-=(Tenor t);

    
    friend class boost::serialization::access;
    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & ar,  const unsigned int) {
      ar & BOOST_SERIALIZATION_NVP(year_);
      ar & BOOST_SERIALIZATION_NVP(month_);
      ar & BOOST_SERIALIZATION_NVP(day_);
    }
 private:
    int year_;   /*!< \brief This is the integer value representing number of years.*/
    int month_;  /*!< \brief This is the integer value representing number of months.*/
    int day_;    /*!< \brief This is the integer value representing number of days.*/

    int yearOffset() const;
    int monthOffset() const;
  };

  
  std::ostream& operator<<(std::ostream& s, Date& d);

  /** \brief moves date forward by a tenor
   */ 
  inline  Date operator+(Date d, Tenor t) {
    d += t;
    return d;
  }
  /** \brief moves date backward by a tenor
   */ 
  inline  Date operator-(Date d, Tenor t) {
    d -= t;
    return d;
  }
  /** \brief checks if dates are equal
   */ 
  inline bool operator==(const Date& d1, const Date& d2) {
    return d1.getN() == d2.getN();
  }
  /** \brief checks if dates are not equal
   */ 
  inline bool operator!=(const Date& d1, const Date& d2) {
    return d1.getN() != d2.getN();
  }
  /** \brief checks if date d1 is earlier than d2
   */ 
  inline bool operator<(const Date& d1, const Date& d2) {
    return d1.getN() < d2.getN();
  }
  /** \brief checks if date d1 is later than d2
   */ 
  inline bool operator>(const Date& d1, const Date& d2) {
    return d1.getN() > d2.getN();
  }
  /** \brief checks if date d1 is not earlier than d2
   */ 
  inline bool operator<=(const Date& d1, const Date& d2) {
    return d1.getN() <= d2.getN();
  }
  /** \brief checks if date d1 is not later than d2
   */ 
  inline bool operator>=(const Date& d1, const Date& d2) {
    return (d1.getN() >= d2.getN() );
  }
  /** \brief creates tenor 
   */ 
  inline Tenor operator*(int a, TimeUnit unit_) {
    return Tenor(a, unit_);
  }
  /** \brief creates tenor 
   */ 
  inline Tenor operator*(TimeUnit unit_, int a) {
    return Tenor(a, unit_);
  }

}  // namespace julian
#endif 
