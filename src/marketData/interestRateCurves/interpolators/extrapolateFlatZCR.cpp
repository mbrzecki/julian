#include <marketData/interestRateCurves/interpolators/extrapolateFlatZCR.hpp>
#include <string>

namespace julian {
namespace ir {

  /** \brief default constructor
   */
  ExtrapolateFlatZCR::ExtrapolateFlatZCR(){
  }

  /** \brief method extrapolates the curve
   */
  double ExtrapolateFlatZCR::operator()(const Calendar&, const InterestRate& rate, const Date& today, const std::vector<Date>& dates,const std::vector<double>& DFs,const Date& date) const {
    Date end;
    double DF;
    if (date < dates.at(0)) {
      end = dates.at(0);
      DF  = DFs.at(0);
    } else {
      end = dates.at(dates.size() - 1);
      DF  = DFs.at(DFs.size() - 1);
    }
    double zcr = rate.zcRate(today, end, DF);
    return rate.DF(today, date, zcr);
  }

  /** \brief virtual copy constructor
   */
  ExtrapolateFlatZCR* ExtrapolateFlatZCR::clone() const {
    return new ExtrapolateFlatZCR(*this);
  }

  /** \brief returns the name of class
   */
  std::string ExtrapolateFlatZCR::info() const {
    return "Flat_zero_coupon_rates";
  }
}  // namespace ir
}  // namespace julian
