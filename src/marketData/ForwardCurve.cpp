#include <marketData/ForwardCurve.hpp>
#include <utils/vectorOperations.hpp>

namespace julian {

  /** \brief default constructor
   */

  ForwardCurve::ForwardCurve() {
  }

  /** \brief default
   */
  ForwardCurve::ForwardCurve(const Date as_of_date, const SmartPointer<Interpolation>& interpolation,
			     const SmartPointer<YearFraction>& yf, const std::vector<Date>& dates, const std::vector<double>& prices) {
    as_of_date_ = as_of_date;
    interpolation_ = interpolation;
    yf_ = yf;
    dates_ = dates;
    prices_ = prices;

    sort_vectors<Date, double>(dates_, prices_);
    for (auto date : dates_) {
      time_.push_back(yf_->operator()(as_of_date_, date));
    }
  }

  /** \brief calculates the forward for a given date
   */
  double ForwardCurve::getForwardPrice(Date d) {
    double tx = yf_->operator()(as_of_date_, d);
    return interpolation_->operator()(time_, prices_, tx);
  }

  /** \brief returns grid dates
   */
  std::vector<Date> ForwardCurve::getDates() {
    return dates_;
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, julian::ForwardCurve& c) {
    s << "Object: ForwardCurve"
      << "\nAsOfDate: " << c.as_of_date_
      << "\nInterpolation: " << c.interpolation_->info()
      << "\nYearFraction: " << c.yf_->info()
      << "\nDate \t\tPrice\n";

    for (unsigned int i = 0; i < c.dates_.size(); i++ ) {
      s << c.dates_.at(i) << "\t" << std::fixed << std::setprecision(2) << c.prices_.at(i) << "\n";
    }
    return s;
  }
}


