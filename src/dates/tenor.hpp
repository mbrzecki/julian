#ifndef JULIAN_TENOR_HPP
#define JULIAN_TENOR_HPP

#include <dates/timeUnit.hpp>
#include <iostream>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
/**
 * @file   tenor.hpp
 * @brief  File contains definition of tenor class.
 */

namespace julian {

  /**\ingroup dates
   * \brief Class implements a tenor object.
   *
   * Tenor is a object that posses number of time units (see TimeUnit enumeration). 
   * Quotings in the market are given for certain tenors. This class helps to represent the concept on tenor.
   */
    
  class Tenor {
  public:
    Tenor();
    Tenor(TimeUnit);
    Tenor(int,TimeUnit);
    
    Tenor(std::string); 
    Tenor operator=(TimeUnit);
    
    int getNumberOfUnits() const;
    TimeUnit getTimeUnit() const;

    operator std::string() const;
    
    friend std::ostream& operator<<(std::ostream&, Tenor&);
    
  private:
    TimeUnit unit_;       /*!< \brief This variable holds type of time unit. */
    int number_of_units_; /*!< \brief This integer represents number of time units. */
  };
}
#endif

