#include <marketData/interestRateCurves/interpolators/extrapolateLogOfDF.hpp>
#include <cmath>

namespace julian {
namespace ir {

  /** \brief default constructor
   */
  ExtrapolateLogOfDF::ExtrapolateLogOfDF(){}

  /** \brief method extrapolates the curve
   */
  double ExtrapolateLogOfDF::operator()(const Calendar&, const InterestRate& rate, const Date& today, const std::vector<Date>& dates,const std::vector<double>& DFs,const Date& date) const {
    Date end;
    double DF;

    if (date < dates.at(0)) {
      end = dates.at(0);
      DF  = DFs.at(0);
    } else {
      end = dates.at(dates.size() - 1);
      DF  = DFs.at(DFs.size() - 1);
    }

    double t  = rate.yf(today, date);
    double tk = rate.yf(today, end);

    return pow(DF, t/tk);
  }
  
  /** \brief virtual copy constructor
   */
  ExtrapolateLogOfDF* ExtrapolateLogOfDF::clone() const {
    return new ExtrapolateLogOfDF(*this);
  }

  /** \brief returns the name of class
   */
  std::string ExtrapolateLogOfDF::info() const {
    return "Linear_log_of_DF";
  }
}  // namespace ir
}  // namespace julian
