#include <dates/calendars/goodFriday.hpp>

namespace julian {
  
  /** \brief Checks if date is Corpus Christi feast 
   *  
 * Method returns true if a date is a Good Friday and false otherwise.
 */
  
  bool GoodFriday::operator()(Date date) const {
    Date Easter = EasterForAGivenYear(date.getYear()); 
    Date corpusChristi = Easter - 2 * DAY;
   
    return (date == corpusChristi);
  }

  /** \brief Virtual copy constructor 
   *
   * Method is an implementation of virtual copy constructor.
   */

  GoodFriday* GoodFriday::clone() const {
    return new GoodFriday(*this);
  }

  /** \brief Informations about class 
   *
   * Method returns string that containing information about class. 
   */
  std::string GoodFriday::info() const {
    std::string s = "GoodFriday ";
    return s;
  }
}
