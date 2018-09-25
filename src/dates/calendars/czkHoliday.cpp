#include <dates/calendars/czkHoliday.hpp>
#include <string>

namespace julian {

  /** \brief Check if date is a holiday
   * 
   * Method return true if date is CZK holiday and false otherwise.
   */
  bool CZKHoliday::operator()(Date date) const {
    int d  = date.getDay();
    int m  = date.getMonth();
    int y  = date.getYear();

    Date easter_monday;
    easter_monday  = EasterForAGivenYear(y);
    easter_monday += 1 * DAY;
    // New Year's Day
    if (d == 1  && m == 1) return true;

    // EasterMondey
    if (date == easter_monday) return true;

    // Labour Day
    if (d == 1  && m == 5) return true;

    // Liberation Day
    if (d == 8 && m == 5) return true;

    // SS. Cyril and Methodius
    if (d == 5 && m == 7) return true;

    // Jan Hus Day
    if (d == 6 && m == 7) return true;

    // Czech Statehood Day
    if (d == 28 && m == 9) return true;

    // Independence Day
    if (d == 28 && m == 10) return true;

    // Struggle for Freedom and Democracy Day
    if (d == 17 && m == 11) return true;

    // Christmas Eve
    if (d == 24 && m == 12) return true;

    // Christmas
    if (d == 25 && m == 12) return true;

    // St. Stephen
    if (d == 26 && m == 12) return true;

    return false;
  }

  /** \brief Virtual copy constructor
   * 
   * Method is an implementation of virtual copy constructor.
   */

  CZKHoliday* CZKHoliday::clone() const {
    return new CZKHoliday(*this);
  }

  /** \brief Informations about class
   *
   * Method returns string that containing information about class. 
   */
  std::string CZKHoliday::info() const {
    return "CZK ";
  }
}  // namespace julian
