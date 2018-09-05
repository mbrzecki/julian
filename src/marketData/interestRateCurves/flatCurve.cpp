#include <marketData/interestRateCurves/flatCurve.hpp>
#include <utils/formatters.hpp>
#include <iomanip>

namespace julian {
namespace ir {

  /** \brief default constructor
   */
  FlatCurve::FlatCurve() {
  }

  /** \brief constructor
   */
  FlatCurve::FlatCurve(InterestRate& rate, double zero_coupon_rate, Date curve_date, Calendar& calendar):
    rate_(rate), zero_coupon_rate_(zero_coupon_rate), curve_date_(curve_date), calendar_(calendar) {}

  double FlatCurve::DF(Date date) const {
    if (date > curve_date_)
      return rate_.DF(curve_date_, date, zero_coupon_rate_);
    return 0.0;
  }

  double FlatCurve::DF(Date date1, Date date2) const {
    if (date1 > curve_date_)
      return rate_.DF(date1, date2, zero_coupon_rate_);
    return 0.0;
  }

  double FlatCurve::DF(Tenor t) const {
    auto date = calendar_.settlementDate(curve_date_, t);
    if (date > curve_date_)  
      return rate_.DF(curve_date_, date, zero_coupon_rate_);
    return 0.0;
  }

  double FlatCurve::DF(Tenor t1, Tenor t2) const {
    auto date = calendar_.settlementDate(curve_date_, t1);
    if (date > curve_date_)  
      return rate_.DF(date, calendar_.settlementDate(curve_date_, t2), zero_coupon_rate_);
    return 0.0;
  }

  double FlatCurve::capitalization(Date date) const {
    return 1.0 / this->DF(date);
  }

  double FlatCurve::capitalization(Tenor t) const {
    return 1.0 / this->DF(t);
  }

  double FlatCurve::capitalization(Date date1, Date date2) const {
    return 1.0 / this->DF(date1, date2);
  }

  double FlatCurve::capitalization(Tenor t1, Tenor t2) const {
    return 1.0 / this->DF(t1, t2);
  }

  double FlatCurve::coupon(Date date) const {
    return 1.0 / this->DF(date) - 1.0;
  }

  double FlatCurve::coupon(Tenor t) const {
    return 1.0 / this->DF(t) - 1.0;
  }

  double FlatCurve::coupon(Date date1, Date date2) const {
    return 1.0 / this->DF(date1, date2) - 1.0;
  }

  double FlatCurve::coupon(Tenor t1, Tenor t2) const {
    return 1.0 / this->DF(t1, t2) - 1.0;
  }

  double FlatCurve::rate(Date) const {
    return zero_coupon_rate_;
  }

  double FlatCurve::rate(Tenor) const {
    return zero_coupon_rate_;
  }

  double FlatCurve::rate(Date date,InterestRate rate) const {
    return rate.zcRate(curve_date_, date, this->DF(date));
  }

  double FlatCurve::rate(Tenor t, InterestRate rate) const {
    return this->rate(calendar_.settlementDate(curve_date_, t), rate);
  }

  double FlatCurve::fwdRate(Date date1, Date date2) const {
    return rate_.fwdRate(date1, date2, this->DF(date1), this->DF(date2));
  }

  double FlatCurve::fwdRate(Tenor t1, Tenor t2) const {
    return this->fwdRate(calendar_.settlementDate(curve_date_, t1), calendar_.settlementDate(curve_date_, t2));
  }

  double FlatCurve::fwdRate(Date date, Tenor t) const {
    return this->fwdRate(date, calendar_.settlementDate(curve_date_, t));
  }

  double FlatCurve::fwdRate(Date date1, Date date2, InterestRate rate) const {
    return rate.fwdRate(date1, date2, this->DF(date1), this->DF(date2));
  }

  double FlatCurve::fwdRate(Tenor t1, Tenor t2, InterestRate rate) const {
    return this->fwdRate(calendar_.settlementDate(curve_date_, t1), calendar_.settlementDate(curve_date_, t2), rate);
  }

  double FlatCurve::fwdRate(Date date ,Tenor t, InterestRate rate) const {
    return this->fwdRate(date, calendar_.settlementDate(curve_date_, t), rate);
  }

  Date FlatCurve::getValuationDate() const {
    return curve_date_;
  }

  FlatCurve* FlatCurve::clone() const {
    return new FlatCurve(*this);
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, FlatCurve& c){
    s << "Object: FlatCurve"
      << "\nAsOfDate: " << c.curve_date_
      << "\nInterestRate: " << c.rate_ 
      << "\nRate_level: "
      <<  formatter::percentage(c.zero_coupon_rate_); 

    return s;
  }

}  // namespace ir
}  // namespace julian
