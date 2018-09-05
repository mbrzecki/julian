#include <dates/calendars/hufHoliday.hpp>

namespace julian {

  /** \brief Check if date is a holiday
   * 
   * Method return true if date is HUF holiday and false otherwise.
   */
  bool HUFHoliday::operator()(Date date) const {
    int d  = date.getDay();
    int m  = date.getMonth();
    int y  = date.getYear();
    
    Date Easter = EasterForAGivenYear(y);
    Date easterMonday = Easter + 1 * DAY;
    Date WhitMonday = Easter + 50 * DAY;


    // EasterMondey
    if( date == easterMonday)
      return true;
    
    // Whit Monday
    if( date == WhitMonday)
      return true;
    
    // New Year's Day
    if (d == 1  && m == 1)
      return true;
    
    // National Day
    if (d == 15  && m == 3)
      return true;
    
    // Labour Day
    if (d == 1  && m == 5)
      return true;
    
    // Constitution Day
    if (d == 20  && m == 8)
      return true;
    
    // Republic Day
    if (d == 23  && m == 10)
      return true;
    
    // All Saints Day
    if (d == 1  && m == 11)
      return true;
    
    // Christmas
    if (d == 25 && m == 12)
      return true;
    
    // 2nd Day of Christmas
    if (d == 26 && m == 12)
      return true;
    
    return false;
  }

  /**\brief Virtual copy constructor 
   * 
   * Method is an implementation of virtual copy constructor.
   */
  HUFHoliday* HUFHoliday::clone() const {
    return new HUFHoliday(*this);
  }

  /** \brief Informations about class 
   * 
   * Method returns string that containing information about class. 
   */
  std::string HUFHoliday::info() const {
    std::string s = "HUF ";
    return s;
  }
}
