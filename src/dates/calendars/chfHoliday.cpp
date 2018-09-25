#include <dates/calendars/chfHoliday.hpp>

namespace julian {
  
  /** \brief Check if date is a holiday
   * 
   * Method return true if date is CHF holiday and false otherwise.
   */
  bool CHFHoliday::operator()(Date date) const {
    int d  = date.getDay();
    int m  = date.getMonth();
    int y  = date.getYear();

    Date Easter = EasterForAGivenYear(y);
    Date goodFriday = Easter - 2 * DAY;
    Date easterMonday = Easter + 1 * DAY;
    Date ascensionDay = Easter + 40 * DAY;
    Date aWhitMonday = Easter + 50 * DAY;
  
    // New Year
    if( d == 1 && m == 1) return true;
    
    // Berchtoldstag
    if( d == 2 && m == 1) return true; 
    
    // Good Friday
    if( date == goodFriday) return true;
    
    // EasterMondey
    if( date == easterMonday) return true;
    
    // Ascension Day
    if( date == ascensionDay) return true;
    
    // Whit Monday
    if( date == aWhitMonday) return true;
  
    // Worker's Day
    if( d == 1 && m == 5) return true;

    // National Day
    if( d == 1 && m == 8) return true;
   
    // Christmas
    if(d == 25 && m == 12) return true;
      
    // St. Stephen's Day
    if(d == 26 && m == 12) return true;

    return false;
  }

  /** \brief Virtual copy constructor
   *
   *  Method is an implementation of virtual copy constructor.
   */
  CHFHoliday* CHFHoliday::clone() const {
    return new CHFHoliday(*this);
  }

  /** \brief informations about class
   *
   * Method returns string that containing information about class. 
 */
  std::string CHFHoliday::info() const {
    return "CHF ";
  }
}  // namespace julian
