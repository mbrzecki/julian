#include <dates/calendars/jpyHoliday.hpp>

namespace julian {
  
  /** \brief Check if date is a holiday
   *
   * Method return true if date is JPY holiday and false otherwise.
   */
  bool JPYHoliday::operator()(Date date) const {
    int d  = date.getDay();
    int m  = date.getMonth();
    int y  = date.getYear();
    int wd = date.getN() % 7;
    
    const double exact_vernal_equinox_time = 20.69115; 
    const double exact_autumnal_equinox_time = 23.09;
    const double diff_per_year = 0.242194;
    const double moving_amount = (y-2000)*diff_per_year;
    
    int number_of_leap_years = (y-2000)/4+(y-2000)/100-(y-2000)/400;
    
    int ve = exact_vernal_equinox_time   + moving_amount - number_of_leap_years;
    int ae = exact_autumnal_equinox_time + moving_amount - number_of_leap_years;
    
    // New Year's Day, January 1st
    if( d == 1  && m == 1) return true;
    
    // Bank Holiday, January 2nd
    if( d == 2  && m == 1) return true; 
    
    // Bank Holiday, January 3rd
    if( d == 3  && m == 1) return true;
    
    //Coming of Age Day, 2nd Monday in January
    if( (d >= 8 && d <= 14) && wd == MON && m == 1 && y >= 2000) return true;
    if(  y < 2000 && m == 1 && ( (wd == MON && d ==16) || d == 15) ) return true;
    
    // National Foundation Day, February 11th
    if( (d == 11 || (d == 12 && wd == MON)  )&& m == 2) return true;
    
    // Vernal Equinox
    if( (d == ve || (d == ve+1 && wd == MON)) && m == 3) return true; 
    
    // Greenery Day, April 29th
    if( (d == 29 || (d==30 && wd == MON ) )  && m == 4) return true;
    
    // Constitution Memorial Day, May 3rd
    if( d == 3  && m == 5) return true;
    
    //Holiday for a Nation, May 4th
    if( d == 4  && m == 5) return true;
    
    //Children's Day, May 5th
    if( d == 5 && m ==5 ) return true;
    
    // any of the three above observed later if on Saturday or Sunday
    if (d == 6 && m == 5 && (wd == MON || wd == TUE || wd == WED) ) return true;
    
    // Marine Day (3rd Monday in July),
    // was July 20th until 2003, not a holiday before 1996 
    
    if (wd == MON && (d >= 15 && d <= 21)  && m == 7 && y >= 2003) return true;
    if ((d == 20 || (d == 21 && wd == MON)) && m == 7 && y >= 1996 && y < 2003) return true;
    
    // Respect for the Aged Day,
    if( (d == 15 || ( d == 16 && wd == MON)) && m == 9 && y <2003) return true;  
    if( wd == MON && ( d >= 15 && d <=22) && m == 9 && y >= 2003) return true;
    
    // If a single day falls between Respect for the Aged Day
    // and the Autumnal Equinox, it is holiday
    
    if (wd == TUE && d+1 == ae && d >= 16 && d <= 22 && m == SEP && y >= 2003) return true;
    
    // Autumnal Equinox
    if( (d == ae || (d == ae+1 && wd == MON)) && m == 9) return true;
    
    // Health and Sports Day, 2nd Monday in October
    if( (d == 10 || (d == 11 && wd == MON)) && m == 10 && y <2000) return true;
    if((wd == MON && ( d >= 8 && d <=14)) && m == OCT && y >= 2000) return true;
    
    // National Culture Day
    if( (d == 3 || (d == 4 && wd == MON)) && m == 11) return true;
    
    // Labor Thanksgiving Day
    if ((d == 23 || (d == 24 && wd == MON)) && m == 11) return true;
    
    // Emperor's Birthday
    if ((d == 23 || (d == 24 && wd == MON)) && m == 12 && y >= 1989) return true;
    
    // Bank Holiday
    if( d == 31 && m == 12) return true;
    
    // Marriage of Prince Akihito
    if(d == 10 && m == 4 && y == 1959) return true;
    //Rites of Imperial Funeral
    if (d == 24 && m == 2 && y == 1989) return true;
    // Enthronement Ceremony
    if (d == 12 && m == 11 && y == 1990) return true;
    // Marriage of Prince Naruhito
    if (d == 9 && m == 6 && y == 1993) return true;
    
    return false;
  }
  
  /** \brief Virtual copy constructor
   * 
   * Method is an implementation of virtual copy constructor.
   */
  JPYHoliday* JPYHoliday::clone() const {
    return new JPYHoliday(*this);
  }
  
  /** \brief informations about class
   *
   * Method returns string that containing information about class. 
   */
  std::string JPYHoliday::info() const {
    std::string s = "JPY ";
    return s;
  }
}
