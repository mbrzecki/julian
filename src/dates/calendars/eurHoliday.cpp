#include <dates/calendars/eurHoliday.hpp>

namespace julian {
  
  /** \brief Checks if date is a holiday
   * 
   * Method return true if date is TARGER2 holiday and false otherwise.
   */
  bool EURHoliday::operator()(Date date) const {
    int d  = date.getDay();
    int m  = date.getMonth();
    int y  = date.getYear();
    
    Date Easter = EasterForAGivenYear(y);
    Date goodFriday = Easter - 2 * DAY;
    
    Date easterMonday = Easter +  1 * DAY;
    
    // New Year
    if( d == 1 && m == 1) return true;
    
    // Worker's Day
    if( d == 1 && m == 5) return true;
    
    // Good Friday
    if( date == goodFriday) return true;
    
    // EasterMondey
    if( date == easterMonday) return true;
    
    // Christmas
    if(d == 25 && m == 12) return true;
  
    // 2nd Day of Christmas
    if(d == 26 && m == 12) return true;
    
    return false;
  }
  
  /** \brief Virtual copy constructor
   *
   * Method is an implementation of virtual copy constructor.
   */
  EURHoliday* EURHoliday::clone() const {
    return new EURHoliday(*this);
  }

  /** \brief informations about class
   *
   * Method returns string that containing information about class. 
   */
  std::string EURHoliday::info() const {
    std::string s = "EUR ";
    return s;
  }
}
