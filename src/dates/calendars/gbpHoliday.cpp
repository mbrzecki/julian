#include <dates/calendars/gbpHoliday.hpp>

namespace julian {

  /** \brief Check if date is a holiday
   *
   * Method return true if date is GBP holiday and false otherwise.
   */
  bool GBPHoliday::operator()(Date date) const {
    int d  = date.getDay();
    int m  = date.getMonth();
    int y  = date.getYear();
    int wd = date.getN() % 7;
    
    Date Easter = EasterForAGivenYear(y);
    Date goodFriday = Easter - 2 * DAY;
    Date easterMonday = Easter + 1 * DAY;
    
    
    // NEW Year's Day (possibly moved to Monday)
    if( (d == 1 || ((d == 2 || d == 3) && wd == 2)) && m == 1) return true;
    
    // Good Friday
    if( date == goodFriday)
      return true; 
    
    // EasterMondey
    if( date == easterMonday)
      return true;
    
    // first Monday of May (Early May Bank Holiday)
    if ( d <= 7 && wd == 2 && m == 5)
      return true;
    
    // last Monday of May (Spring Bank Holiday)
    if ( d >= 25 && wd == 2 && m ==5)
      return true;
    
    // last Monday of August (Summer Bank Holiday)
    if ( d >= 25 && wd == 2 && m == 8)
      return true;
    
    // Christmas (possibly moved to Monday or Tuesday)
    if( (d == 25 || (d == 27 && (wd == 2 || wd == 3))) && m == 12)
      return true;
    
    // Boxing Day (possibly moved to Monday or Tuesday)
    if( (d == 26 || (d == 28 && (wd == 2 || wd == 3))) && m == 12)
      return true;
    
    return false;
  }
  
  /** \brief Virtual copy constructor
   * 
   * Method is an implementation of virtual copy constructor.
   */
  GBPHoliday* GBPHoliday::clone() const {
    return new GBPHoliday(*this);
  }
  
  /** \brief informations about class
   *
   * Method returns string that containing information about class. 
   */
  std::string GBPHoliday::info() const {
    std::string s = "GBP ";
    return s;
  }
}
