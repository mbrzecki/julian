#include <marketData/interestRateCurves/irCurveBuilder.hpp>
#include <boost/assert.hpp>
#include <vector>
#include <interestRates/simpleRate.hpp>
#include <dates/yearFractions/ACT365.hpp>
#include <mathematics/interpolation/linearInterpolation.hpp>
#include <marketData/interestRateCurves/interpolators/interpolateZCRate.hpp>
#include <marketData/interestRateCurves/interpolatedCurve.hpp>
#include <marketData/interestRateCurves/interpolators/irCurveCompoundedInterpolator.hpp>
#include <marketData/interestRateCurves/interpolators/extrapolateFlatZCR.hpp>

namespace julian {
namespace ir {

  /** \brief constructor
   *
   */
  BuildCurve::BuildCurve() {
    fx_spot_ = 1.0;
    method_of_construction_ = InputType::NONE;

    LinearInterpolation interp;
    InterpolateZCRate inputs;
    CompoundedInterpolator inter(interp, inputs);
    interpolator_ = inter;

    ExtrapolateFlatZCR ext;
    extrapolator_ = ext;

    SimpleRate s;
    ACT365 yf;
    InterestRate rate(s, yf);
    rate_ = rate;
  }

  /** \brief sets calendar
   */  
  BuildCurve& BuildCurve::withCalendar(const Calendar& input) {
    calendar_ = input;
    return *this;
  }

  /** \brief sets interest rate convention
   */  
  BuildCurve& BuildCurve::withInterestRate(const InterestRate& input) {
    rate_ = input;
    return *this;
  }

  /** \brief sets date of curve
   */  
  BuildCurve& BuildCurve::asOfDate(const Date& input) {
    today_ = input;
    return *this;
  }

  /** \brief sets discount factors
   */  
  BuildCurve& BuildCurve::withDiscountFactors(const std::vector<double>& input) {
    double_holder_ = input;
    method_of_construction_ = InputType::DF;
    return *this;
  }

  /** \brief sets zero coupon rates
   */  
  BuildCurve& BuildCurve::withZeroCouponRates(const std::vector<double>& input) {
    double_holder_ = input;
    method_of_construction_ = InputType::ZCR;
    return *this;
  }

  /** \brief sets forward rates
   */  
  BuildCurve& BuildCurve::withForwardRates(const std::vector<double>& input) {
    double_holder_ = input;
    method_of_construction_ = InputType::FWD;
    return *this;
  }

  /** \brief sets zero coupon rate
   */ 
  BuildCurve& BuildCurve::withZeroCouponRate(const double input) {
    zero_coupon_rate_ = input;
    return *this;
  }

  /** \brief sets grid dates of the curve
   */ 
  BuildCurve& BuildCurve::withDates(const std::vector<Date>& input) {
    dates_ = input;
    return *this;
  }

  /** \brief sets tenors, basing on tenors the grid dates of the curve are calculated
   */ 
  BuildCurve& BuildCurve::withTenors(const std::vector<Tenor>& input) {
    tenors_ = input;
    return *this;
  }

  /** \brief sets tenors, basing on tenors the grid dates of the curve are calculated
   */ 
  BuildCurve& BuildCurve::withTenors(const std::vector<std::string>& input) {
    for (auto t : input) {
      tenors_.push_back(t);
    }
    return *this;
  }

  /** \brief sets discounting curve used in multiple curve framework
   */ 
  BuildCurve& BuildCurve::usingDiscountingCurve(const SmartPointer<ir::Curve>& input) {
    discounting_curve_ = input;
    return *this;
  }

  /** \brief sets projection curve used in multiple curve framework
   */ 
  BuildCurve& BuildCurve::usingProjectionCurve(const SmartPointer<ir::Curve>& input) {
    projection_curve_ = input;
    return *this;
  }

  /** \brief sets interpolator
   */ 
  BuildCurve& BuildCurve::withInterpolator(const SmartPointer<Interpolator>& input) {
    interpolator_ = input;
    return *this;
  }

  /** \brief sets extrapolator
   */ 
  BuildCurve& BuildCurve::withExtrapolator(const SmartPointer<Extrapolator>& input) {
    extrapolator_ = input;
    return *this;
  }

  /** \brief sets fx spot
   */ 
  BuildCurve& BuildCurve::withFxSpot(const double& input) {
    fx_spot_ = input;
    return *this;
  }

  /** \brief sets benchmark instruments
   */ 
  BuildCurve& BuildCurve::withSetOfInstruments(const std::vector<SmartPointer<BuildingBlock> >& input){
    instruments_ = input;
    std::sort(instruments_.begin(), instruments_.end(), [](SmartPointer<BuildingBlock> a, SmartPointer<BuildingBlock> b) {return (*a).getDate() < (*b).getDate();});
    method_of_construction_ = InputType::INSTRUMENTS;

    for(unsigned int i = 1; i < instruments_.size(); i++) {
      BOOST_ASSERT_MSG( (*instruments_.at(i-1)).getDate() < (*instruments_.at(i)).getDate()  ,"Two instrument in the set have the same maturity date.");
    }
    return *this;
  }

  /** \brief sets estimator
   */ 
  BuildCurve& BuildCurve::usingEstimator(const SmartPointer<Estimator>& input) {
    estimator_ = input;
    return *this;
  }

  /** \brief Creates interpolated interest rate curve
   *
   * This is conversion operator. It creates the interest rate curve with settings provided by other methods.
   */ 
  BuildCurve::operator InterpolatedCurve() {
    if (tenors_.size() != 0) {
      for (auto t : tenors_) {
	dates_.push_back(calendar_.settlementDate(today_,t));
      }
    }

    std::vector<double> df;
    if (method_of_construction_ == InputType::INSTRUMENTS) {
      BOOST_ASSERT_MSG(not estimator_.isEmpty(), "No curve estimator provided");
      CurveSettings cs {today_, rate_, interpolator_, extrapolator_, calendar_, fx_spot_};
      estimator_->calculate(instruments_, cs, discounting_curve_, projection_curve_);
      dates_ = estimator_->getDates();
      df = estimator_->getDF();

    } else if (method_of_construction_ == InputType::ZCR) {
      for (unsigned int i = 0; i < double_holder_.size(); i++)
    	df.push_back(rate_.DF(today_, dates_.at(i), double_holder_.at(i)));

    } else if (method_of_construction_ == InputType::DF) {
      df = double_holder_;

    } else if (method_of_construction_ == InputType::FWD) {
      double x = rate_.DF(today_, dates_.at(0), double_holder_.at(0));
      df.push_back(x);
      for (unsigned int i = 1; i < double_holder_.size(); i++) {
    	x  = x * rate_.DF(dates_.at(i-1), dates_.at(i), double_holder_.at(i));
    	df.push_back(x);
      }

    } else {
      BOOST_ASSERT_MSG ( false, "Cannot build curve. Unknown method of construction.");
    }

    return InterpolatedCurve(today_, dates_, df, rate_, interpolator_, extrapolator_, calendar_, fx_spot_);
  }

  /** \brief creates flat interest rate curve
   *
   * This is conversion operator. It creates the flat curve with settings provided by other methods.
   */ 
  BuildCurve::operator FlatCurve() {
    return FlatCurve(rate_, zero_coupon_rate_, today_, calendar_);
  }

}  // namespace ir
}  // namespace julian
