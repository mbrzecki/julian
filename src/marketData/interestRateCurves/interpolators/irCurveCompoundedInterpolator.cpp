#include <marketData/interestRateCurves/interpolators/irCurveCompoundedInterpolator.hpp>
#include <mathematics/interpolation/polynomialInterpolation.hpp>
#include <mathematics/interpolation/linearInterpolation.hpp>
#include <string>
#include <vector>

namespace julian {
namespace ir {

  /** \brief interpolates curve for a given date 
   *
   * \note Some interpolating algorithms required minimum number of points to interpolate (like AKIMA, Steffensen).If minimal number of points is not available the polynomial interpolation is applied.
   */
  double CompoundedInterpolator::operator()(const Calendar&,const InterestRate& rate,
					    const Date& today, const std::vector<Date>& input_dates,
					    const std::vector<double>& input_DF, const Date& date_int) const {
    std::vector<double> input_x;

    for (auto d : input_dates) {
      double t = rate.yf(today, d);
      input_x.push_back(t);
    }

    std::vector<double> input_y;
    for (unsigned int i = 0; i < input_DF.size(); i++) {
      double DF = 1;
      Date d(today);

      if (i > 0) {
	DF = input_DF.at(i-1);     
	d = input_dates.at(i-1);
      }

      double y = (*inputs_)(DF, input_DF.at(i), rate, today, d, input_dates.at(i));
      input_y.push_back(y);
    }

    double x = rate.yf(today, date_int);

    if (input_x.size() >= interpolation_->getMinSize()) {
      x = interpolation_->operator()(input_x, input_y, x);
    } else if (input_x.size() == 2) {
      LinearInterpolation temp_interpolation;
      x = temp_interpolation(input_x, input_y, x);
    } else {
      PolynomialInterpolation temp_interpolation;
      x = temp_interpolation(input_x, input_y, x);      
    }

    return (*inputs_).getDF(x, rate, today, date_int);
  }

  /** \brief virtual copy constructor 
   */
  CompoundedInterpolator* CompoundedInterpolator::clone() const {
    return new CompoundedInterpolator(*this);
  }
  
  /** \brief returns name of a class 
   */
  std::string CompoundedInterpolator::info() const {
    std::string str_int  = interpolation_->info();
    std::string str_meth = inputs_->info();
    std::string str = str_int + "_interpolation_of_" + str_meth;
    return str;
  }
}  // namespace ir
}  // namespaec julia

