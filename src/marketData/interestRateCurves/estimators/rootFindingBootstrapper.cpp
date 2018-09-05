#include <marketData/interestRateCurves/estimators/rootFindingBootstrapper.hpp>

namespace julian {
namespace ir {

  RootFindingBootstrapper* RootFindingBootstrapper::clone() const {
    return new RootFindingBootstrapper(*this);
  }

  std::vector<double> RootFindingBootstrapper::getDF() const {
    return discount_factors_;
  }

  std::string RootFindingBootstrapper::info() const {
    return "Root_finding_bootstrapper";
  }
    
  std::vector<Date> RootFindingBootstrapper::getDates() const {
    return dates_;
  }

  void RootFindingBootstrapper::calculate(const std::vector<SmartPointer<BuildingBlock> >& instruments,
					  const CurveSettings& settings,
					  SmartPointer<Curve>& discounting_curve,
					  SmartPointer<Curve>& projection_curve) {
    discount_factors_.erase(discount_factors_.begin(), discount_factors_.end());
    dates_.erase(dates_.begin(), dates_.end());
    // initial grid point is (date = today. DF = 1.0)
    dates_.push_back(settings.today_);
    discount_factors_.push_back(1.0);

    SmartPointer<Curve> temp_discounting_curve;
    SmartPointer<Curve> temp_projecting_curve;

    // looping instruments
    for (auto instr : instruments) {
      // add maturity date to grid dates of curve
      dates_.push_back((*instr).getDate());
      // guessing the next DF value, assuming that DFt = DFt-1
      discount_factors_.push_back(discount_factors_.back());

      // defining function which root will be found 
      auto func = [&](double x)->double {
	double res = 0.0;
	discount_factors_.back() = x;
	InterpolatedCurve c(settings, dates_, discount_factors_);

	if ( (discounting_curve.isEmpty()) && (projection_curve.isEmpty())) {
	  res = (*instr).calibrate(c);
	} else {	
	  // if no additional curve provided set discounting curve equal to calibrated curve
	  if (discounting_curve.isEmpty()) {
	    temp_discounting_curve = c;
	  } else {
	    temp_discounting_curve = discounting_curve;
	  } 
	  // if no additional curve provided set projection curve equal to calibrated curve
	  if (projection_curve.isEmpty()) {
	    temp_projecting_curve = c;
	  } else {
	    temp_projecting_curve = projection_curve;
	  }
	  res = (*instr).calibrate(temp_discounting_curve, temp_projecting_curve, c);
	}
	return res;
      };

      auto dfunc = [&](double x)->double {
	return (func(x + 1e-6) - func(x)) * 10e6;
      };

      discount_factors_.back() = derivativeRootFinder<decltype(func),decltype(dfunc)>(func, dfunc, discount_factors_.back(), method_, 1e-15,500);

      // removes the DF for today  
      if (discount_factors_.size() == 2 && dates_.front() == settings.today_) {
	dates_.erase(dates_.begin());
	discount_factors_.erase(discount_factors_.begin());
      }
    }
  }
}  // namespace ir
}  // namespace julian
