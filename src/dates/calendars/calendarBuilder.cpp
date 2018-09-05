#include <dates/calendars/calendarBuilder.hpp>

namespace julian {
  
  /** \brief Constructor
   * 
   *  This is a constructor of the class. At initialization of the object following values are set:
   * * day rolling convention: Unadjusted,
   * * spot lag: 0 days,
   * * no end of month adjustment.
   * * settlement date calculated from spot (see SettlementFromSpot)
   */
  BuildCalendar::BuildCalendar() {
    convention_ = UNADJUSTED;
    spot_lag_ = 0;
    end_of_month_ = false;
    SettlementFromSpot set;
    settlement_ = set;
  }

  /**\brief Set convention
   *
   * Method sets the convention (DayRollingConvention)for which calendar will be generated.
   * \param convention Calendar with this convention will be generated. 
   */
  BuildCalendar& BuildCalendar::withConvention(const DayRollingConvention& convention) {
    convention_ = convention;
    return *this;
  }

  /**\brief Set spot lag
   *
   * Method sets the value of the spot lag. 
   * \param spot_lag Value of the spot lag which will be set in the calendar.
   */
  BuildCalendar& BuildCalendar::withSpotLag(const int spot_lag) {
    spot_lag_ = spot_lag;
    return *this;
  }

  /**\brief Marking day as holiday
   *
   * Date provided with this method will be considered as holiday by generated calendar.
   * \param holiday The date which should be considered by generated calendar as holiday.
   */
  BuildCalendar& BuildCalendar::addHoliday(const Date& holiday) {
    holidays_vector_.push_back(holiday);
    return *this;
  }

  /**\brief Marking day as business day
   *
   * Date provided with this method will be considered as business day by generated calendar.
   * \param business_day The date which should be considered by generated calendar as business day.
   */
  BuildCalendar& BuildCalendar::removeHoliday(const Date& business_day) {
    business_days_vector_.push_back(business_day);
    return *this;
  }

  /**\brief Set holiday
   *
   * This method sets the predefined sets of holidays (see class Holiday).
   * \param holiday This is an object of Holiday class. Days recognized as holiday by provided class will be also recognized as holidays by calendar.
   */
  BuildCalendar& BuildCalendar::addHoliday(const SmartPointer<Holiday>& holiday) {
    holidays_.push_back(holiday);
    return *this;
  }

  /**\brief Set holiday
   *
   * This method sets the holiday on given day and month each year.
   * \param month The month of holiday.
   * \param day The day of holiday.
   */
  BuildCalendar& BuildCalendar::addHoliday(const NameOfMonth month,const int day) {
    FixedHoliday fix(month,day);
    holidays_.push_back(fix);
    return *this;
  }
  
  /**\brief End of month
   *
   * If this method is called, generated calendar will apply end month convention while calculating the settlement and expiry dates. 
   */
  BuildCalendar& BuildCalendar::endOfMonth() {
    end_of_month_ = true;
    return *this;
  }

  /**\brief creates  calendar
   *
   * This is conversion operator. It generates the calendar with settings provided by other methods.
   */
  BuildCalendar::operator Calendar() {
    return Calendar(convention_, spot_lag_, business_days_vector_, holidays_vector_, holidays_, end_of_month_, settlement_);
  }

  /**\brief sets settlement convention
   *
   *  This method sets the settlement convention for the calendar being build.
   */
  BuildCalendar& BuildCalendar::withSettlementDateConvention(SmartPointer<SettlementDateConvention> settlement) {
    settlement_ = settlement;
    return *this;
  }
}
