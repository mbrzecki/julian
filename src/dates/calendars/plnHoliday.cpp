#include <dates/calendars/plnHoliday.hpp>

namespace julian {

  /** \brief Check if date is a holiday
   * 
   * Method return true if aDate is PLN holiday and false otherwise.
   */
  bool PLNHoliday::operator()(Date date) const {
    int d  = date.getDay();
    int m  = date.getMonth();
    int y  = date.getYear();
    
    Date Easter = EasterForAGivenYear(y);
    
    Date easterMonday;
    easterMonday = Easter +  1 * DAY;
    
    Date CorpusChristi = Easter + 60 * DAY;
    
    // New Year
    if( d == 1 && m == 1) return true; 
    
    // Epiphany
    if( d == 6 && m == 1 && y > 2010) return true;
    
    // Worker's Day
    if( d == 1 && m == 5) return true;
    
    // Constitution Day
    if( d == 3 && m == 5) return true;
    
    // EasterMondey
    if( date == easterMonday) return true;
    
    // CorpusChristi
    if( date == CorpusChristi) return true;
    
    // Assumption of the Blessed Virgin Mary
    if(d == 15 && m == 8) return true;
    
    // All Saints Day
    if(d == 1  && m == 11) return true;
    
    // Independence Day
    if(d ==11  && m == 11) return true;
    
    // Christmas
    if(d == 25 && m == 12) return true;
    
    // 2nd Day of Christmas
    if(d == 26 && m == 12) return true;
    return false;
  }
  
  /** \brief Virtual copy constructor
   *
   *  Method is an implementation of virtual copy constructor.
   */
  PLNHoliday* PLNHoliday::clone() const {
    return new PLNHoliday(*this);
  }
  
  /** \brief informations about class
   *
   * Method returns string that containing information about class. 
   */
  std::string PLNHoliday::info() const {
    std::string s = "PLN ";
    return s;
  }
}
