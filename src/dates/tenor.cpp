#include <dates/tenor.hpp>
#include <string>

namespace julian {

  /** \brief Constructor
   *
   *  This constructor set unit to Day and the number of units to 1. 
   */
  Tenor::Tenor(): unit_(DAY), number_of_units_(1) {
  }

  /** \brief Constructor - set unit and number 
   *
   *  This constructors builds object on the basis of provided time unit and integer. 
   */
  Tenor::Tenor(int n, TimeUnit unit):  unit_(unit),  number_of_units_(n) {
  }

  /** \brief Constructor - set unit, number is 1
   *
   *   This constructors builds object on the basis of provided time unit. Default number of units is 1.
   */
  Tenor::Tenor(TimeUnit a):  unit_(a), number_of_units_(1) {
  }

  /** \brief Constructor - string
   *
   *  This constructors builds object on the basis of string provided. The string should have form NU, where N is the number of units and U is:
   * * 'D' for Day
   * * 'W' for Week
   * * 'M' for Month
   * * 'Q' for Quarter
   * * 'Y' for year.
   */
  Tenor::Tenor(std::string str) {
    int numberOfUnits = 0;
    if (str == "SW") {
      unit_ = WEEK;
      numberOfUnits = 1;
    } else if (str == "ON") {
      unit_ = OVERNIGHT;
      numberOfUnits = 1;
    } else if (str == "TN") {
      unit_ = TOMORROWNEXT;
      numberOfUnits = 1;
    } else if (str == "SN") {
      unit_ = SPOTNEXT;
      numberOfUnits = 1;
    } else {

      char TUnit = str.at(str.size()-1);
      if (TUnit =='D') {
	unit_ = DAY;
      } else if (TUnit =='W') {
	unit_ = WEEK;
      } else if (TUnit =='M') {
	unit_ = MONTH;
      } else if (TUnit =='Y') {
	unit_ = YEAR;
      } else if (TUnit =='Q') {
	unit_ = QUARTER;
      }

      for (unsigned int i = 0; i < str.size() - 1; i++) {
	char digit = str.at(i);
	numberOfUnits *= 10;
	numberOfUnits += digit - '0';
      }
    }
    number_of_units_ = numberOfUnits;
  }

  /** \brief returns number of time units
   *
   *  Method returns number of time units held by instance.
   */
  int Tenor::getNumberOfUnits() const {
    return number_of_units_;
  }

  /** \brief returns time unit
   *
   *  Methods return name of time unit held by instance.
   */
  TimeUnit Tenor::getTimeUnit() const {
    return  unit_;
  }

  /** \brief Prints tenor
   *
   *  This is definition of overloaded << operator that enables printing Tenor on console application. 
   */
  std::ostream& operator<<(std::ostream& s, Tenor& t) {
    std::string a;
    switch (t. unit_) {
      case DAY: a = "D"; break;
      case WEEK: a = "W"; break;
      case QUARTER: a = "Q"; break;
      case MONTH: a = "M"; break;
      case YEAR: a = "Y"; break;
      case SPOTDATE: a = "Spot"; break;
      case OVERNIGHT: a = "OverNight"; break;
      case TOMORROWNEXT: a = "TomorrowNext"; break;
      case TODAY: a = "Today"; break;
      case SPOTNEXT: a = "SpotNext"; break;
    }

    if (!(t.unit_ == SPOTDATE || t.unit_ == OVERNIGHT || t.unit_ == TOMORROWNEXT || t.unit_ == TODAY || t.unit_ == SPOTNEXT)) {
      s << t.number_of_units_ << a;
    } else {
      s << a;
    }
    return s;
}

  /** \brief Creates tenor by time unit as rvalue.
   *
   *  Methods overloads operator=. It enables to create tenors object by providing time unit as rvalue. 
   */
  Tenor Tenor::operator=(TimeUnit u) {
    return Tenor(1, u);
  }

  /** \brief Converts tenor to std::string.
   *
   * Conversion operator to std::string. 
   */

  Tenor::operator std::string() const {
    std::string a;
    switch (unit_) {
      case DAY: a = "D"; break;
      case WEEK: a = "W"; break;
      case QUARTER: a = "Q"; break;
      case MONTH: a = "M"; break;
      case YEAR: a = "Y"; break;
      case SPOTDATE: a = "Spot"; break;
      case OVERNIGHT: a = "OverNight"; break;
      case TOMORROWNEXT: a = "TomorrowNext"; break;
      case TODAY: a = "Today"; break;
      case SPOTNEXT: a = "SpotNext"; break;
    }
    if (!(unit_ == SPOTDATE || unit_ == OVERNIGHT || unit_ == TOMORROWNEXT || unit_ == TODAY || unit_ == SPOTNEXT)) {
      a = std::to_string(number_of_units_) + a;
    } 
    return a;
  }
}
