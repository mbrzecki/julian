#include <string>
#include <dates/calendars/whitMonday.hpp>

namespace julian {

  /** \brief Check if date is a holiday
   *
   * Method returns true if a date is a Whit Monday and false otherwise.
   */
  bool WhitMonday::operator()(Date date) const {
    Date Easter = EasterForAGivenYear(date.getYear());
    Date aWhitMonday = Easter + 50 * DAY;
    return (date == aWhitMonday);
  }

  /** \brief Virtual copy constructor
   *
   * Method is an implementation of virtual copy constructor.
   */
  WhitMonday* WhitMonday::clone() const {
    return new WhitMonday(*this);
  }

  /** \brief informations about class
   *
   * Method returns string that containing information about class. 
   */
  std::string WhitMonday::info() const {
    std::string s = "WhitMonday ";
    return s;
  }
}  // namespace julian
