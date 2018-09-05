#include <vector>
#include <marketData/interestRateCurves/estimators/ConstrainedSmoother.hpp>
#include <marketData/interestRateCurves/estimators/rootFindingBootstrapper.hpp>
#include <marketData/interestRateCurves/irCurveBuilder.hpp>
#include <marketData/interestRateCurves/interpolators/irCurveInterpolator.hpp>
#include <marketData/interestRateCurves/interpolators/irCurveExtrapolator.hpp>
#include <mathematics/numericalAlgorithms/QuadraticProgrammingSolver.hpp>

namespace julian {
namespace ir {

  /** \brief Constructor

      \param cf Cost function
      \param lT lower tolerance vector
      \param uT upper tolerance vector
      \param number_of_iterations Number of iteration of Sequential Quadratic Programming algorithm 
   */
  ConstrainedSmoother::ConstrainedSmoother(SmartPointer<SmootherCostFunction> cf,
					   const std::vector<double>& lT,
					   const std::vector<double>& uT,
					   int number_of_iterations):
    cost_function_(cf), lower_tolerance_(lT), upper_tolerance_(uT), number_of_iterations_(number_of_iterations), tolerance_(0.0) {}

  /** \brief Constructor

      \param cf Cost function
      \param tolerance Maximal deviation from market quote
      \param number_of_iterations Number of iteration of Sequential Quadratic Programming algorithm 
   */
  ConstrainedSmoother::ConstrainedSmoother(SmartPointer<SmootherCostFunction> cf,
					   double tolerance,
					   int number_of_iterations):
	cost_function_(cf),  number_of_iterations_(number_of_iterations), tolerance_(tolerance) {}

  /** \brief Estimates the curve
   *
   * Algorithm uses the SQP algorithm to estimate the curve. 
   */
  void ConstrainedSmoother::calculate(const std::vector<SmartPointer<BuildingBlock> >& instruments,
				      const CurveSettings& settings,
				      SmartPointer<ir::Curve>& discounting_curve, SmartPointer<ir::Curve>& projection_curve) {
    std::vector<double> quotings_vector;
    for (auto instr : instruments) {
      quotings_vector.push_back(instr->getQuoting());
      dates_.push_back(instr->getDate() );
    }
    arma::mat quotings(quotings_vector);
    arma::mat lT(instruments.size(), 1);
    arma::mat uT(instruments.size(), 1);

    if (tolerance_ == 0.0) {
      lT = arma::mat(lower_tolerance_);
      uT = arma::mat(upper_tolerance_);
    } else {
      lT.fill(-tolerance_);
      uT.fill( tolerance_);
    }

    RootFindingBootstrapper nr;
    InterpolatedCurve smoothed_curve = BuildCurve()
      .asOfDate(settings.today_)
      .withCalendar(settings.calendar_)
      .withInterestRate(settings.rate_)
      .withInterpolator(settings.interpolator_)
      .withExtrapolator(settings.extrapolator_)
      .usingEstimator(nr)
      .usingDiscountingCurve(discounting_curve)
      .usingProjectionCurve(projection_curve)
      .withSetOfInstruments(instruments)
      .withFxSpot(settings.fx_spot_);

    arma::mat Q = cost_function_->giveQmatrix(smoothed_curve);
    arma::mat C = cost_function_->giveCvector(smoothed_curve);

    QuadraticProgrammingSolver qp;
    qp.setQuadraticTerm(Q);
    qp.setLinearTerm(C);

    for (int i = 0; i < number_of_iterations_; i++) {
      std::vector<double> smoothed_values = cost_function_->giveSmoothedCurve(smoothed_curve);
      arma::mat rates(smoothed_values);
      arma::mat jacobian = calculateJacobian(discounting_curve, projection_curve, smoothed_curve, instruments);
      arma::mat parRates = calculateParRates(discounting_curve, projection_curve, smoothed_curve, instruments);
      arma::mat lowerConstrain = jacobian * rates - parRates + quotings + lT;
      arma::mat upperConstrain = jacobian * rates - parRates + quotings + uT;

      qp.setNonEqualityConstrainsMatrix(jacobian);
      qp.setNonEqualityConstrainsLowerVector(lowerConstrain);
      qp.setNonEqualityConstrainsUpperVector(upperConstrain);

      arma::mat solution = qp.solve();
      std::vector<double> new_rates = arma::conv_to<std::vector<double> >::from(solution);
      cost_function_->updateSmoothedCurve(smoothed_curve, new_rates);
    }
    DFs_ = smoothed_curve.getDFs();
  }

  /** \brief Returns estimated DF
   */
  std::vector<double> ConstrainedSmoother::getDF() const {
    return DFs_;
  }

  /** \brief Returns grid dates of the curve
   */
  std::vector<Date> ConstrainedSmoother::getDates() const {
    return dates_;
  }

  /** \brief Virtual Copy Constructor
   */
  ConstrainedSmoother* ConstrainedSmoother::clone() const {
    return new ConstrainedSmoother(*this);
  }

  /** \brief Returns estimator's name
   */
  std::string ConstrainedSmoother::info() const {
    return "Constrained_smoother";
  }

  /** \brief Method used by SQP algorithm to calculate Jacobian for constrains' approximation
   *
   */
  arma::mat ConstrainedSmoother::calculateJacobian(SmartPointer<ir::Curve> disc,
						   SmartPointer<ir::Curve> proj,
						   InterpolatedCurve smoothed,
						   const std::vector<SmartPointer<BuildingBlock> >& instruments) {
    bool disc_empty = disc.isEmpty();
    bool proj_empty = proj.isEmpty();
    if (disc_empty) {
      disc = smoothed;
    }
    if (proj_empty) {
      proj = smoothed;
    }
    
    double h = 1e-4;
    std::vector<double> parRates;

    for (auto instr : instruments) {
      parRates.push_back(instr->getParRate(disc, proj, smoothed));
    }

    arma::mat jacobian(instruments.size(), smoothed.getSize());
    std::vector<double> rates = cost_function_->giveSmoothedCurve(smoothed);

    for (unsigned int instrument = 0; instrument < instruments.size(); instrument++) {
      auto instr = instruments.at(instrument);
      for (int rate = 0; rate < smoothed.getSize(); rate++) {
	rates.at(rate) += h;
	cost_function_->updateSmoothedCurve(smoothed, rates);
	
	if (disc_empty) {
	  disc = smoothed;
	}
	if (proj_empty) {
	  proj = smoothed;
	}
	
	jacobian(instrument, rate) = (instr->getParRate(disc, proj, smoothed) - parRates.at(instrument)) / h;
	rates.at(rate) -= h;
	cost_function_->updateSmoothedCurve(smoothed, rates);
      }
    }
    return jacobian;
  }

  /** \brief Calculates the vector of par rates for instruments
   *
   */
  arma::mat ConstrainedSmoother::calculateParRates(const SmartPointer<ir::Curve>& disc,
						   const SmartPointer<ir::Curve>& proj,
						   const SmartPointer<ir::Curve>& smoothed,
						   const std::vector<SmartPointer<BuildingBlock> >& instruments) {
    SmartPointer<ir::Curve> disc_temp;
    SmartPointer<ir::Curve> proj_temp;   
    if (disc.isEmpty()) {
      disc_temp = smoothed;
    } else {
      disc_temp = disc;
    }
    if (proj.isEmpty()) {
      proj_temp = smoothed;
    } else {
      proj_temp = proj;
    }

    arma::mat ret(instruments.size(), 1);

    for (unsigned int i = 0; i < instruments.size(); i++) {
      auto instr = instruments.at(i);
      ret(i, 0) = instr->getParRate(disc_temp, proj_temp, smoothed);
    }
    return ret;
  }

}  // namespace ir
}  // namespace julian
