#include <string>
#include <dates/calendars/usdHoliday.hpp>

namespace julian {

  /** \brief Check if date is a holiday
   * 
   * Method return true if date is USD holiday and false otherwise.
   */
  bool USDHoliday::operator()(Date date) const {
    int d  = date.getDay();
    int m  = date.getMonth();
    int y  = date.getYear();
    int wd = date.getN() % 7;

    Date goodFriday = EasterForAGivenYear(y) - 2 * DAY;


    // New Year's Day (possibly moved to Monday if on Sunday)
    if( (d == 1 || (d == 2 && wd == 2) ) && m == 1) return true; 

    // Martin Luther King's birthday (third Monday in January)
    if ( (d >= 15 && d <=21) && wd == 2 && m == 1) return true;

    // Washington's birthday (third Monday in February)
    if( (d >= 15 && d <= 21) && wd == 2 && m == 2) return true;

    // Good Friday
    if( date == goodFriday) return true;  

    // Memorial Day (last Monday in May)
    if( d >= 25 && wd == 2 && m == 5) return true;

    // Independence Day (Monday if Sunday or Friday if Saturday)
    if( (d == 4 || (d == 5 && wd == 2) || (d == 3 && wd == 6)) && m == 7) return true;

    // Columbus Day (second Monday in October)
    if ( (d >= 8 && d <= 14) && wd == 2 && m == 10) return true;

    // Veteran's Day  (Monday if Sunday or Friday if Saturday)
    if ( ( d == 11 || (d == 12 && wd == 2) || (d == 10 && wd ==6)) && m == 11) return true;

    // Labour Day (first Monday in September)
    if( d <= 7 && wd == MON && m == 9) return true;

    // Thanksgiving Day (fourth Thursday in November)
    if (( d >= 22 && d<= 28) && wd == 5 && m == 11) return true; 

    // Christmas (Monday if Sunday or Friday if Saturday)
    if (( d == 25 || (d == 26 && wd == 2) || (d == 24 && wd ==6)) && m == 12) return true;

    return false;
  }

  /** \brief Virtual copy constructor
   * Method is an implementation of virtual copy constructor.
   *
   */
  USDHoliday* USDHoliday::clone() const {
    return new USDHoliday(*this);
  }

  /** \brief informations about class
   * 
   * Method returns string that containing information about class. 
   */
  std::string USDHoliday::info() const {
    std::string s = "USD ";
    return s;
  }
}
