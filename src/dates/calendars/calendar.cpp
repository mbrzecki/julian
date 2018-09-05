#include <dates/calendars/calendar.hpp>
#include <boost/assert.hpp>
#include <vector>
#include <string>

namespace julian {

  /** \brief Constructor
   *
   * Constructor creating calendar object on the basis of given date, day rolling convention and spot lag. 
   * Also three vectors that are used in process of establishing whether a day is business day are provided. 
   */
  Calendar::Calendar(DayRollingConvention day_rolling_convention,
                     int spot_lag,
                     const std::vector<Date>& business_days,
                     const std::vector<Date>& holidays_dates,
                     const std::vector<SmartPointer<Holiday> >& holidays,
                     bool end_of_month,
                     const SmartPointer<SettlementDateConvention>& settlement) {
    day_rolling_convention_ = day_rolling_convention;
    spot_lag_ = spot_lag;
    end_of_month_ = end_of_month;
    business_days_ = business_days;
    holidays_dates_ = holidays_dates;
    holidays_ = holidays;
    settlement_ = settlement;
  }

  /** \brief Constructor
   *
   * Constructor creating calendar object on the basis of given date, day rolling convention and spot lag. 
   * Also three vectors that are used in process of establishing whether a day is business day are provided. 
   */
  Calendar::Calendar() {
    day_rolling_convention_ = UNADJUSTED;
    spot_lag_  = 0;
    end_of_month_ = false;
    SettlementFromSpot x;
    settlement_ = x;
  }

  /** \brief Method returns true if a given date is business day and false otherwise. 
   */
  bool Calendar::isBusinessDay(const Date& input) const {
    return !(isWeekend(input) || isHoliday(input));
  }

  /** \brief Method returns true if a given date is holiday and false otherwise. 
   *
   * Firstly method checks if date is listed in set of holidays vector. 
   * Secondly method check if date is listed in set of business day vector. 
   *
   * Lastly it checks if date is holiday according to given Holiday objects. 
   */
  bool Calendar::isHoliday(const Date& input) const {
    if (holidays_dates_.size() > 0) {
      for (auto x : holidays_dates_)
	if (input == x) {
	  return true;
	}
    }

    if (business_days_.size() > 0) {
      for (auto x : business_days_)
        if (input == x) {
          return false;
        }
    }

    if (holidays_.size() > 0) {
      for (auto x : holidays_) {
	if (x->operator()(input)) {
	  return true;
	}
      }
    }
    return false;
  }

  /** \brief Method returns true if a given date is a Saturday or Sunday and false otherwise. 
   */
  bool Calendar::isWeekend(const Date& date) const {
    int test = date.getN() % 7;
    if (test == SAT || test == SUN)
      return true;
    return false;
  }

  /** \brief Method returns number of business days between date1 and date2. 
   */
  int Calendar::businessDaysBetween(const Date& date1, const Date& date2) const {
    int sum = 0;
    Date d_test = date1;
    while (d_test <= date2) {
      if (isBusinessDay(d_test))
	sum++;
      d_test += 1 * DAY;
    }
    return sum;
  }

  /** \brief Method returns number of holidays between date1 and date2. 
   */
  int Calendar::numberOfHolidaysBetween(const Date& date1, const Date& date2) const {
    int sum = 0;
    Date d_test = date1;
      while (d_test <= date2) {
	if (isHoliday(d_test)) {
	  sum++;
	}
	d_test += 1 * DAY;
      }
    return sum;
  }

  /** \brief Method adjusts a date according to a given day rolling convention.
   */
  Date Calendar::adjust(const Date& date) const {
    Date d_new(date);

    if (!isBusinessDay(d_new)) {

      if (day_rolling_convention_ == FOLLOWING)
	return workingDays(d_new, 1);

      if (day_rolling_convention_ == PRECEDING)
	return workingDays(d_new, -1);

      if (day_rolling_convention_ == MODIFIEDFOLLOWING) {
	Date d_test;
	d_test =  workingDays(d_new, 1);
	if (d_test.getMonth() == d_new.getMonth())
	  return d_test;
	else
	  return workingDays(d_new, -1);
      }

      if (day_rolling_convention_ == MODIFIEDPRECEDING) {
	Date d_test;
	d_test =  workingDays(d_new, -1);
	if (d_test.getMonth() == d_new.getMonth())
	  return d_test;
	else
	  return workingDays(d_new, 1);
      }
      
      if (day_rolling_convention_ == NEAREST) {
      Date d_test1(date);
      Date d_test2(date);

      while (isHoliday(d_test1) && isHoliday(d_test2)) {
	d_test1 -= 1*DAY;
	d_test2 += 1*DAY;
      }
      
      if (isHoliday(d_test2))
	return d_test1;
      else
	return d_test2;  
      }
    }
    
    return d_new; //unadjusted
  }

  /** \brief  Method returns spot date for a given date.
   */
  Date Calendar::getSpot(const Date& aDate) const {
    return workingDays(aDate, spot_lag_);
  }

  /** \brief  Method returns next working day of a calendar's date.
   */

  Date Calendar::getON(const Date& d) const {
    return workingDays(d, 1);
  }

  /** \brief  Method returns second working day from a calendar's date.
   */
  Date Calendar::getTN(const Date& d) const {
    return workingDays(d, 2);
  }

  /** \brief Method returns nth working day from a given date.
   */
  Date Calendar::workingDays(const Date& date, int n) const {
    Date d_new(date);
    int iterator = 0;

    if (n > 0) {
      while (iterator < n) {
	d_new += 1*DAY;
	if (isBusinessDay(d_new))
	  iterator ++;
      }
    }

    if (n < 0) {
      while (iterator > n) {
	d_new -= 1*DAY;
	if(isBusinessDay(d_new))
	  iterator --;
      }
    }
    return d_new;
  }

  /** \brief Calculates settlement date
   *
   * Method returns settlement date for a given start date and tenor. The calculation is performed according to settlement day convention provided is calendar construction process.
   */
  Date Calendar::settlementDate(const Date& d , const Tenor& t) const {
    if (!(t.getTimeUnit() == SPOTDATE || t.getTimeUnit() == OVERNIGHT || t.getTimeUnit() == TOMORROWNEXT || t.getTimeUnit() == TODAY || t.getTimeUnit() == SPOTNEXT)) {
      auto d_temp = (*settlement_).calculateSettlementDate(d, t, *this);
      if (isEndOfMonth(d) && end_of_month_ && t.getTimeUnit() != WEEK  && t.getTimeUnit() != DAY) {
	return getLastWorkingDateOfMonth(d_temp);
      } else {
	return d_temp;
      }
    } else {
      if (t.getTimeUnit() == SPOTDATE)
	return workingDays(d, spot_lag_);

      if (t.getTimeUnit() == OVERNIGHT)
	return workingDays(d, 1);

      if (t.getTimeUnit() == TOMORROWNEXT)
	return  workingDays(d, 2);

      if (t.getTimeUnit() == SPOTNEXT)
	return  workingDays(d, spot_lag_ + 1);
    }
    return d;
  }

  /** Method returns expiry date for a given start date and tenor. The calculation is performed according to settlement day convention provided is calendar construction process.
      \warning Expiry date can not be calculated for tenor like Spot Overnight, Tomorrow Next and Today.
  */
  Date Calendar::expiryDate(const Date& date, const Tenor& t) const {
    if (!(t.getTimeUnit() == SPOTDATE || t.getTimeUnit() == OVERNIGHT || t.getTimeUnit() == TOMORROWNEXT || t.getTimeUnit() == TODAY))
      return (*settlement_).calculateExpiryDate(date, t, *this);

    BOOST_ASSERT_MSG(true, "Expiry date can not be calculated for Spot, ON, TN nor Today ");
    return date;
  }

  /** This is overloading of std::cout<< operator that allows to print object's informations on console.
   */
  std::ostream& operator<<(std::ostream& s, Calendar& c) {
    std::string conv;
    switch (c.day_rolling_convention_) {
    case FOLLOWING : conv = "Following"; break;
    case MODIFIEDFOLLOWING : conv = "Modified Following"; break;
    case PRECEDING : conv = "Preceding"; break;
    case MODIFIEDPRECEDING : conv = "Modified Preceding"; break;
    case UNADJUSTED: conv = "Unadjusted"; break;
    case NEAREST : conv = "Nearest"; break;
    }

  std::string curr = " ";
  if (c.holidays_.size() > 0) {
    for (auto x : c.holidays_)
      curr = curr + x->info();

  } else if (c.holidays_.size() == 0) {
    curr = " None";
  }

  std::string eom;
  if (c.end_of_month_)
    eom = " Yes";
  else
    eom = " No";

  s << "Object: Calendar" << "\n"
    << "Convention: " << conv << "\n"
    << "SpotLag: " << c.spot_lag_ << "\n"
    << "Holidays:" << curr << "\n"
    << "Settlemet: " << c.settlement_->info() << "\n"
    << "EndOfMonth:" << eom << "\n";

  return s;
  }

/** Method returns true if the given date is the last working day of month.
 */
  bool Calendar::isEndOfMonth(const Date& d) const {
    Date d_test(d);
    d_test += 1*DAY;

    if (!isBusinessDay(d_test))
      d_test = workingDays(d_test, 1);
    return (d.getMonth() != d_test.getMonth());
  }

  /** Method calculates the last working date of the month.
   */
  Date Calendar::getLastWorkingDateOfMonth(const Date& d) const {
    Date d_test(d);
    d_test.moveToEndOfMonth();

    if (!isBusinessDay(d_test))
      d_test = workingDays(d_test, -1);

    return d_test;
  }
  /** Returns spot lag
   */
  int Calendar::getSpotLag() const {
    return spot_lag_;
  }
}  // namespace julian
