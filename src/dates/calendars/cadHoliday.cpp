#include <dates/calendars/cadHoliday.hpp>
#include <string>
namespace julian {

  /** \brief Check if date is a holiday
   * 
   * Method return true if date is CAD holiday and false otherwise.
   */
  bool CADHoliday::operator()(Date date) const {
    int d  = date.getDay();
    int m  = date.getMonth();
    int y  = date.getYear();

    Date good_friday = EasterForAGivenYear(y) -  2 * DAY;
    int wd = date.getN() % 7;

    // New Year (1st of January, possible move to Monday)
    if ( (d == 1 || (d == 2 && wd == MON) ) && m == JAN) return true; 
    // Family Day, third Monday of February (since 2008)
    if ( (d >= 15 && d <= 21) && wd == MON && m == FEB && y >= 2008) return true;
    // Good Friday
    if ( date == good_friday ) return true; 
    // Victoria Day, the Monday on or preceding May 24th
    if ( d > 17 && d <= 24 && wd == MON && m == MAY) return true;
    // Canada Day, July 1st (possibly moved to Monday)
    if ((d == 1 || ((d == 2 || d == 3) && wd == MON)) && m == JUL) return true;
    // Provincial Holiday, first Monday of August
    if (d <= 7 && wd == MON && m == AUG) return true;
    // Labour Day, first Monday of September
    if (d <= 7 && wd == MON && m == SEP) return true;
    // Thanksgiving Day, second Monday of October
    if (d > 7 && d <= 14 && wd == MON && m == OCT) return true;
    // Remembrance Day, November 11th (possibly moved to Monday)
    if ((d == 11 || ((d == 12 || d == 13) && wd == MON)) && m == NOV) return true;
    // Christmas, December 25th (possibly moved to Monday or Tuesday)
    if ((d == 25 || (d == 27 && (wd == MON || wd == TUE))) && m == DEC) return true;
    // Boxing Day, December 26th (possibly moved to Monday or Tuesday)
    if ((d == 26 || (d == 27 && (wd == MON || wd == TUE))) && m == DEC) return true;
    return false;
  }

  /** \brief Virtual copy constructor
   *
   *  Method is an implementation of virtual copy constructor.
   */
  CADHoliday* CADHoliday::clone() const {
    return new CADHoliday(*this);
  }

  /** \brief informations about class
   *
   * Method returns string that containing information about class. 
   */
  std::string CADHoliday::info() const {
    std::string s = "CAD ";
    return s;
  }
}
