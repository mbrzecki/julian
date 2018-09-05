#include <dates/calendars/fixedHoliday.hpp>
#include <string>
#include <iomanip>
#include <locale>
#include <sstream>

namespace julian {
  
  /** \brief Checks if a date is fixed holiday.
      
      Method returns true if a date is fixed date holiday and false otherwise.
  */
  bool FixedHoliday::operator()(Date date) const {
    int d  = date.getDay();
    int m  = date.getMonth();
    
    if( d == day_ && m == month_) return true;
    return false;
  }
  
  /** \brief Virtual copy constructor 
      
      Method is an implementation of virtual copy constructor.
  */
  FixedHoliday* FixedHoliday::clone() const {
    return new FixedHoliday(*this);
  }
  
  /** \brief Informations about class
      
      Method returns string that containing information about class. 
  */
  std::string FixedHoliday::info() const {        
    std::ostringstream s1;  
    s1 << day_;
    std::string s2;
    
    switch(day_) {
    case 1: s2 = "st";break;
    case 2: s2 = "nd";break;
    case 3: s2 = "rd";break;
    default: s2 = "th";
    }
    
    std::string s3;
    
    switch(month_) {
    case 1: s3 = "January "; break;
    case 2: s3 = "February "; break;
    case 3: s3 = "March "; break;
    case 4: s3 = "April "; break;
    case 5: s3 = "May "; break;
    case 6: s3 = "June "; break;
    case 7: s3 = "July "; break;
    case 8: s3 = "August "; break;
    case 9: s3 = "September "; break;
    case 10:s3 = "October "; break;
    case 11:s3 = "November "; break;
    case 12:s3 = "December "; break;
    }
    
    return  s1.str() + s2 + s3;
  }
}
