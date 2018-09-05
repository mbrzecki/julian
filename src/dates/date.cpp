#include <dates/_all_dates.hpp>
#include <string>
#include <regex>
#include <boost/assert.hpp>


namespace julian {

  /*! \name Constructors
   */

  //@{

  /** \brief Constructor
   *
   * Constructor creating date object on the basis of three integers representing year, month and day number. 
   */
  Date::Date(int year, int month, int day):
    year_(year), month_(month), day_(day) {
  }

  Date::Date(int date) {
    day_  = date % 100;
    date = (date - day_) / 100;
    month_ = date % 100;
    date = (date - month_) / 100;
    year_ = date;
  }

  /** \brief Default constructor
   *
   * Constructor creating invalid date: year, month and day number are set to zero. This allows to check if date was initialized or not. 
   */
  Date::Date(): year_(0), month_(0), day_(0) {
  }

  /** \brief Constructor - from string YYYY-MM-DD
   *
   *  Constructor creating date object on the basis of string. (example date represent 31st of December, 2015):
   * * 2015-12-31
   * * 15-12-31
   * * 2015DEC31
   * * 2015/12/31
   * * 31/12/2015
   * * 31DEC2015
   */
  Date::Date(std::string date, Date::Format fmt) {
    std::string month_str;
    switch (fmt) {
    case Date::Format::date1:
      year_ = atoi((date.substr(0, 4)).c_str());
      month_ = atoi((date.substr(5, 2)).c_str());
      day_ = atoi((date.substr(8, 2)).c_str());
      break;
    case Date::Format::date2:
      year_ = 2000 + atoi((date.substr(0, 2)).c_str() );
      month_ = atoi((date.substr(3, 2)).c_str());
      day_ = atoi((date.substr(6, 2)).c_str());
      break;
    case Date::Format::date3:
      year_ = atoi((date.substr(0, 4)).c_str());
      month_str = (date.substr(5, 3)).c_str();
      day_ = atoi((date.substr(7, 2)).c_str());

      if (month_str == "JAN") month_ = 1;
      else if (month_str == "FEB") month_ = 2;
      else if (month_str == "MAR") month_ = 3;
      else if (month_str == "APR") month_ = 4;
      else if (month_str == "MAY") month_ = 5;
      else if (month_str == "JUN") month_ = 6;
      else if (month_str == "JUL") month_ = 7;
      else if (month_str == "AUG") month_ = 8;
      else if (month_str == "SEP") month_ = 9;
      else if (month_str == "OCT") month_ = 10;
      else if (month_str == "NOV") month_ = 11;
      else if (month_str == "DEC") month_ = 12;
      break;
    case Date::Format::date4:
      year_ = atoi((date.substr(0, 4)).c_str());
      month_ = atoi((date.substr(5, 2)).c_str());
      day_ = atoi((date.substr(8, 2)).c_str());
      break;
    case Date::Format::date5:
      day_   = atoi((date.substr(0, 2)).c_str() );
      month_ = atoi((date.substr(3, 2)).c_str() );
      year_  = atoi((date.substr(6, 4)).c_str() );
      break;
    case Date::Format::date6:
      day_ = atoi((date.substr(0, 2)).c_str());
      month_str = (date.substr(2, 3)).c_str();
      year_ = atoi((date.substr(5, 4)).c_str());

      if (month_str == "JAN") month_ = 1;
      else if (month_str == "FEB") month_ = 2;
      else if (month_str == "MAR") month_ = 3;
      else if (month_str == "APR") month_ = 4;
      else if (month_str == "MAY") month_ = 5;
      else if (month_str == "JUN") month_ = 6;
      else if (month_str == "JUL") month_ = 7;
      else if (month_str == "AUG") month_ = 8;
      else if (month_str == "SEP") month_ = 9;
      else if (month_str == "OCT") month_ = 10;
      else if (month_str == "NOV") month_ = 11;
      else if (month_str == "DEC") month_ = 12;
      break;
    }
  }
//@}

  /*! \name Output getters
   */
//@{

  int Date::getDay() const {
    return day_;
  }

  int Date::getMonth() const {
    return month_;
  }

  int Date::getYear() const {
    return year_;
  }

  std::string Date::getString() const {
    std::string a, b;

    if (month_ < 10) {
      a = "-0";
    } else {
      a = "-";
    }

    if (day_ < 10) {
      b = "-0";
    } else {
      b = "-";
    }

    std::string ret = std::to_string(year_) + a + std::to_string(month_) + b + std::to_string(day_);
    return ret;
  }

  /** \brief Calculate number of date 
   *
   * Operator returns number of days between the date and 1900JAN01. 
   */
  int Date::getN() const {
    return yearOffset() + monthOffset() + day_;
  }

  //@}

  /*! \name Setters
   */
  //@{

  void Date::setDay(int day) {
    day_ = day;
  }

  void Date::setMonth(int month) {
    month_ = month;
  }

  void Date::setYear(int year) {
    year_ = year;
  }

  //@}

  /** \brief Moves date to next date
   *
   * Method increments date by a one day. 
   */

  void Date::operator++() {
    Date date1;
    Date date2;
    Date date3;

    date1.setYear(year_);
    date1.setMonth(month_);
    date1.setDay(day_ + 1);

    date2.setYear(year_);
    date2.setMonth(month_+1);
    date2.setDay(1);

    date3.setYear(year_+1);
    date3.setMonth(1);
    date3.setDay(1);

    if (date1.isValid()) {
      day_++;
    } else if (date2.isValid()) {
      month_++; day_ = 1;
    } else if (date3.isValid()) {
      year_++;
      day_ = 1;
      month_ = 1;
    }
  }

  /** \brief Moves date back to last day 
   * 
   * Method decrements date by a one day.  
   */

  void Date::operator--() {
    Date date1(year_, month_, day_ - 1);
    Date date1a(year_, month_, day_ - 2);
    Date date1b(year_, month_, day_ - 3);
    Date date2(year_, month_ - 1, 31);
    Date date3(year_, month_ - 1, 30);
    Date date4(year_, month_ - 1, 29);
    Date date5(year_, month_ - 1, 28);
    Date date6(year_ - 1, 12, 31);

    if (date1.isValid()) {
      day_--;
    } else if (date1a.isValid()) {
      day_ -= 2;
    } else if (date1b.isValid()) {
      day_ -= 3;
    } else if (date2.isValid()) {
      month_--;
      day_ = 31;
    } else if (date3.isValid()) {
      month_--;
      day_ = 30;
    } else if (date4.isValid()) {
      month_--;
      day_ = 29;
    } else if (date5.isValid()) {
      month_--;
      day_ = 28;
    } else if (date6.isValid()) {
      year_--;
      month_ = 12;
      day_ = 31;
    }
  }

  /** \brief Moves to end of month 
   *
   * Method moves date to the end of the month. 
   */
  void Date::moveToEndOfMonth() {
    if (month_ == 1 || month_ == 3 || month_ == 5 || month_ == 7 || month_ == 8 || month_ == 10 || month_ == 12) {
      day_ = 31;
    } else if (month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11) {
      day_ = 30;
    } else {
      if (year_ % 4 == 0) {
	day_ = 29;
      } else {
	day_ = 28;
      }
    }
  }

  /** \brief Moves to end of year
   *
   * Method moves date to the end of the year.
   */
  void Date::moveToEndOfYear() {
    day_ = 31;
    month_ = 12;
  }

  /** \brief Checks is date valid
   *
   * Method return true if the date is a valid date (month number between 1 and 12 and proper number of days) and false otherwise. 
   */
  bool Date::isValid() const {
  if (year_ < 1900 || year_ > 2200)
    return false;

  if (month_ > 12 || month_ < 1 )
    return false;

  if (day_ > 31 || day_ < 1 )
    return false;

  if (day_ == 31 && ( month_ == 2 || month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11 ))
    return false;

  if ( day_ == 30 && month_ == 2)
    return false;

  if ((day_ == 29 && month_ == 2) && !( year_ % 4 == 0 ))
    return false;

  return true;
}


  /** \brief Checks if date is in leap year
   *
   * Method returns true if date is in a leap year and false otherwise.
   */
  bool Date::isLeapYear() const {
    return (year_ % 4 == 0);
  }

  /** \brief Checks if date is end of month
   *
   * Method returns true if date is a last day of its month and false otherwise. 
   */
  bool Date::isEndOfMonth() const {
    Date test(*this);
    test.moveToEndOfMonth();
    return (*this == test);
  }

  /** \brief Checks if date is end of year 
   * 
   * Method returns true if date is a last day of its year and false otherwise.
   */
  bool Date::isEndOfYear() const {
    if (month_ == 12 && day_ == 31)
      return true;
    return false;
  }

  /** \brief Adds tenor
   * 
   * Operator moves date forward by a certain tenor. This operate will not do anything if OverNight, TommmorowNext, SpotDate, Today, SpotNext tenor given.
   */
  void Date::operator+=(Tenor t) {
    if (t.getTimeUnit() == DAY) {
      if (t.getNumberOfUnits() > 0) {
        for (int i = 0; i < t.getNumberOfUnits(); i++)
          this->operator++();
      } else if (t.getNumberOfUnits() < 0) {
        for (int i = t.getNumberOfUnits(); i < 0; i++)
          this->operator--();
      }
    } else if ( t.getTimeUnit() == WEEK ) {
      Tenor tx = 7 * t.getNumberOfUnits() * DAY;
      *this += tx;
    } else if ( t.getTimeUnit() == MONTH ) {
      if (t.getNumberOfUnits() > 0) {
        month_ +=  t.getNumberOfUnits();
        while (month_ > 12) {
          year_++;
          month_ -= 12;
        }
      } else {
        month_ += t.getNumberOfUnits();
        while (month_ < 0) {
          year_--;
          month_ += 12;
        }
      }
    } else if (t.getTimeUnit() == QUARTER) {
      Tenor tx = 3 * t.getNumberOfUnits() * MONTH;
      *this += tx;
    } else if (t.getTimeUnit() == YEAR) {
      year_ += t.getNumberOfUnits();
    }

    while ( !isValid() )
      this->operator--();
  }

  /** \brief Subtracts tenor
   *
   * Operator moves date backward by a certain tenor. This operate will not do anything if OverNight TommmorowNext, SpotDate, Today tenor given. 
   */
  void Date::operator-=(Tenor t) {
    Tenor tx(-t.getNumberOfUnits(), t.getTimeUnit());
    Date d(*this);
    d += tx;
    year_ = d.getYear();
    month_ = d.getMonth();
    day_  = d.getDay();
  }

  /** \brief Prints date 
   *
   * Operator enables using std library operator << to print the date. 
   */
  std::ostream& operator << (std::ostream& os, Date& d) {
    std::string a, b;

    if (d.getMonth() < 10) {
      a = "-0";
    } else {
      a = "-";
    }

    if ( d.getDay() < 10 ) {
      b = "-0";
    } else {
     b = "-";
    }

    os << d.getYear() << a << d.getMonth() << b << d.getDay();
    return os;
  }

  /** \brief Auxiliary method
   * 
   * Auxiliary method used by method dateNumber to calculated number of days . 
   */
  int Date::monthOffset() const {
    static const int MonthOffset[] = {
      0,  31,  59,  90, 120, 151,   // Jan - Jun
      181, 212, 243, 273, 304, 334,   // Jun - Dec
      365     // used in dayOfMonth to bracket day_
    };

    static const int MonthLeapOffset[] = {
      0,  31,  60,  91, 121, 152,   // Jan - Jun
      182, 213, 244, 274, 305, 335,   // Jun - Dec
      366     // used in dayOfMonth to bracket day_
    };

    return (isLeapYear() ? MonthLeapOffset[month_-1] : MonthOffset[month_-1]);
  }

  /** \brief Auxiliary method
   *
   * Auxiliary method used by method dateNumber to calculated number of days  
   */
  int Date::yearOffset() const {
    static const int YearOffset[] = {
      // 1900-1909
      0,  366,  731, 1096, 1461, 1827, 2192, 2557, 2922, 3288,
      // 1910-1919
      3653, 4018, 4383, 4749, 5114, 5479, 5844, 6210, 6575, 6940,
      // 1920-1929
      7305, 7671, 8036, 8401, 8766, 9132, 9497, 9862, 10227, 10593,
      // 1930-1939
      10958, 11323, 11688, 12054, 12419, 12784, 13149, 13515, 13880, 14245,
      // 1940-1949
      14610, 14976, 15341, 15706, 16071, 16437, 16802, 17167, 17532, 17898,
      // 1950-1959
      18263, 18628, 18993, 19359, 19724, 20089, 20454, 20820, 21185, 21550,
      // 1960-1969
      21915, 22281, 22646, 23011, 23376, 23742, 24107, 24472, 24837, 25203,
      // 1970-1979
      25568, 25933, 26298, 26664, 27029, 27394, 27759, 28125, 28490, 28855,
      // 1980-1989
      29220, 29586, 29951, 30316, 30681, 31047, 31412, 31777, 32142, 32508,
      // 1990-1999
      32873, 33238, 33603, 33969, 34334, 34699, 35064, 35430, 35795, 36160,
      // 2000-2009
      36525, 36891, 37256, 37621, 37986, 38352, 38717, 39082, 39447, 39813,
      // 2010-2019
      40178, 40543, 40908, 41274, 41639, 42004, 42369, 42735, 43100, 43465,
      // 2020-2029
      43830, 44196, 44561, 44926, 45291, 45657, 46022, 46387, 46752, 47118,
      // 2030-2039
      47483, 47848, 48213, 48579, 48944, 49309, 49674, 50040, 50405, 50770,
      // 2040-2049
      51135, 51501, 51866, 52231, 52596, 52962, 53327, 53692, 54057, 54423,
      // 2050-2059
      54788, 55153, 55518, 55884, 56249, 56614, 56979, 57345, 57710, 58075,
      // 2060-2069
      58440, 58806, 59171, 59536, 59901, 60267, 60632, 60997, 61362, 61728,
      // 2070-2079
      62093, 62458, 62823, 63189, 63554, 63919, 64284, 64650, 65015, 65380,
      // 2080-2089
      65745, 66111, 66476, 66841, 67206, 67572, 67937, 68302, 68667, 69033,
      // 2090-2099
      69398, 69763, 70128, 70494, 70859, 71224, 71589, 71955, 72320, 72685,
      // 2100-2109
      73050, 73415, 73780, 74145, 74510, 74876, 75241, 75606, 75971, 76337,
      // 2110-2119
      76702, 77067, 77432, 77798, 78163, 78528, 78893, 79259, 79624, 79989,
      // 2120-2129
      80354, 80720, 81085, 81450, 81815, 82181, 82546, 82911, 83276, 83642,
      // 2130-2139
      84007, 84372, 84737, 85103, 85468, 85833, 86198, 86564, 86929, 87294,
      // 2140-2149
      87659, 88025, 88390, 88755, 89120, 89486, 89851, 90216, 90581, 90947,
      // 2150-2159
      91312, 91677, 92042, 92408, 92773, 93138, 93503, 93869, 94234, 94599,
      // 2160-2169
      94964, 95330, 95695, 96060, 96425, 96791, 97156, 97521, 97886, 98252,
      // 2170-2179
      98617, 98982, 99347, 99713, 100078, 100443, 100808, 101174, 101539,
      101904,
      // 2180-2189
      102269, 102635, 103000, 103365, 103730, 104096, 104461, 104826, 105191,
      105557,
      // 2190-2199
      105922, 106287, 106652, 107018, 107383, 107748, 108113, 108479,
      108844, 109209,
      // 2200
      109574
    };
    return YearOffset[year_-1900];
  }
}  // namespace julian
