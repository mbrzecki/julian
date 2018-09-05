#include <juliant.hpp>

/**
   \example DatesAndCalendarExample.cpp 
   \brief This example show how to create and use dates, calendars and year fractions.
   
   @verbinclude DatesAndCalendarExample.dox 
 */

using namespace julian;

int main() {
	//
	// Creating dates in three different way
	//
  Date d(2015,AUG,26);
  Date d1(20150525);
  Date d2(2015,9,12);
  
  	//
	// Building calendar
	//  
  CorpusChristi corpus_christi;
  EasterMonday easter_monday;
  GoodFriday good_friday;


  Calendar calendar = BuildCalendar()
    .withConvention(FOLLOWING)
    .addHoliday(good_friday)
    .addHoliday(easter_monday)
    .addHoliday(corpus_christi)
    .addHoliday(MAY,1)
    .withSpotLag(1); 

  SHOW(calendar);

   	//
	// Testing year fraction conventions
	//   
  ACT360 yf1;
  ACT360addOne yf2;
  ActActISDA yf3;
  ACT365 yf4;
  OneYF yf5;
  

  
  std::cout << "\nThis is an example calculation of year fraction between dates: "
	    << d1 << " and " <<d2 << " according to ACT360 convention.         YF= "
	    << yf1(d1,d2) << std::endl;
  std::cout << "This is an example calculation of year fraction between dates: "
	    << d1 << " and " << d2 << " according to ACT360 add one convention. YF= "
	    << yf2(d1,d2) << std::endl;
  std::cout << "This is an example calculation of year fraction between dates: "
	    << d1 << " and " << d2 << " according to ACTACT ISDA convention.    YF= "
	    << yf3(d1,d2) << std::endl;
  std::cout << "This is an example calculation of year fraction between dates: "
	    << d1 << " and " << d2 << " according to ACT365 convention.         YF= "
	    << yf4(d1,d2) << std::endl;
  std::cout << "This is an example calculation of year fraction between dates: "
	    << d1 << " and " << d2 << " according to 1/1 convention.            YF= "
	    << yf5(d1,d2) << std::endl;
    
  return 0;
}
