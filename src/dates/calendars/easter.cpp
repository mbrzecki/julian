#include <dates/calendars/easter.hpp>

namespace julian {
	
  /** \ingroup calendar_holidays				       
   *
   *  \fn Date EasterForAGivenYear(int year) 
   *  \brief Function calculating Easter date for a given year.
   * 
   * Easter date is calculated according to algorithm presented by C.F. Gauss.
   *
   * a = year mod 19
   *
   * b = year mod  4 
   * 
   * c = year mod  7 
   *
   * d = 19a + 24 
   *
   * e = 2b + 4c + 6d + X mod 7
   *
   * n = e + d 
   *
   * Then Easter is n days from 22MAR. 
   * For years 1900 - 2099 X = 5. For years 2100-2199 X = 6
   * There are few exceptions from this algorithm (1954, 1981, 2049, 2076, 2106, 2133)
   * 
   * \param year An integer describing the year.
   * \return A date of Easter for a given year.
   */
  Date EasterForAGivenYear(int year) {
    int y = 5;

    if (year > 2099) {
      y = 6;
    }

    int a = year % 19;
    int b = year % 4;
    int c = year % 7;
    int d = (19 * a + 24) % 30;
    int e = (2 * b  + 4 * c + 6 * d + y) % 7;

    Date result;
    result.setYear(year);

    if (year == 1981 || year == 2076 || year == 2133) {
      result.setDay(19);
      result.setMonth(4);
      return result;
    }

    if (year == 1954 || year == 2049 || year == 2106) {
      result.setDay(18);
      result.setMonth(4);
      return result;
    }

    result.setMonth(3);
    result.setDay(22);
    result += (d + e) * DAY;
    return result;
  }
}  // namespace julian
