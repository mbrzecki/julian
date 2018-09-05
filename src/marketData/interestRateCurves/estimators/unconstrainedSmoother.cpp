#include <marketData/interestRateCurves/estimators/UnconstrainedSmoother.hpp>
#include <marketData/interestRateCurves/estimators/rootFindingBootstrapper.hpp>
#include <marketData/interestRateCurves/curveBuildingBlock.hpp>
#include <marketData/interestRateCurves/irCurveBuilder.hpp>
#include <mathematics/numericalAlgorithms/derivativeMinimizer.hpp>
#include <mathematics/numericalAlgorithms/nonDerivativeMinimizer.hpp>

namespace julian {
namespace ir {

  UnconstrainedSmoother* UnconstrainedSmoother::clone() const {
    return new UnconstrainedSmoother(*this);
  }

  std::vector<double> UnconstrainedSmoother::getDF() const {
    return DFs_;
  }

  std::vector<Date> UnconstrainedSmoother::getDates() const {
    return dates_;
  }

  std::string UnconstrainedSmoother::info() const {
    return "unconstrained_smoother";
  }
    
  void UnconstrainedSmoother::calculate(const std::vector<SmartPointer<BuildingBlock> >& instruments,
					const CurveSettings& settings,
					SmartPointer<Curve>& discounting_curve,
					SmartPointer<Curve>& projection_curve) {

    std::vector<Date> dates;
    std::vector<double> zc;
    for (auto i : instruments) {
      dates.push_back(i->getDate());
      zc.push_back(0.03);
    }

    InterpolatedCurve curve = BuildCurve()
      .asOfDate(settings.today_)
      .withCalendar(settings.calendar_)
      .withInterestRate(settings.rate_)
      .withInterpolator(settings.interpolator_)
      .withExtrapolator(settings.extrapolator_)
      .withDates(dates)
      .withZeroCouponRates(zc)
      .usingDiscountingCurve(discounting_curve)
      .usingProjectionCurve(projection_curve)
      .withFxSpot(settings.fx_spot_);
    
    auto aim = [&](std::vector<double> v)->double {
      cost_function_->updateSmoothedCurve(curve, v);
      SmartPointer<Curve> disc, proj;
      if (discounting_curve.isEmpty()) {
    	disc = curve;
      } else {
    	disc = discounting_curve;
      }
      if (projection_curve.isEmpty()) {
    	proj = curve;
      } else {
    	proj = projection_curve;
      }
      double cost = lambda_ * cost_function_->calculateCost(curve);
      for (unsigned int i = 0; i < instruments.size(); i++) {
       	auto inst = instruments.at(i);
       	double diff  = inst->getQuoting() - inst->getParRate(disc, proj, curve);
       	cost += std::pow(100.0 * diff, 2);
      }
      return cost;
    };

    auto x_init = cost_function_->giveSmoothedCurve(curve);
    auto results = derivativeMinimizer(aim,
    				       x_init,
    				       DerivativeMinimizer::BROYDEN_FLETCHER,
    				       0.001 /*step size*/,
    				       1e-3 /*linear minimization parameter*/,
    				       1e-6 /*increment in numerical different algorithm*/,
    				       1e-8 /*abs tolerance for gradient*/,
    				       500 /*max iter*/);
    cost_function_->updateSmoothedCurve(curve, results);
    dates_ = curve.getDates();
    DFs_ = curve.getDFs();
  }
}  // namespace ir
}  // namespace julian
