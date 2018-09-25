#include <juliant.hpp>
/**
 * \example bootstrapperComparison.cpp 
 * \brief Comparing different bootstrappers. 
 *
 * 
 * @verbinclude bootstrapperComparison.dox 
 *
 * @image html curves_comparison.png
 */

using namespace julian;

int main() {
  RunTimeMeasurment timer;
  //
  // Setting date and calendar
  //
  Date today(2016, SEP, 30);

  PLNHoliday plnHoli;
  Calendar calendar = BuildCalendar()
    .withConvention(MODIFIEDFOLLOWING)
    .withSpotLag(2)
    .addHoliday(plnHoli);

  //
  // Creating interest rate object that encapsulates interest rate conventions
  //
  SimpleRate comp1;
  ExponentialRate comp2;

  ACT365 yf1;
  ActActISDA yf2;

  InterestRate rate1(comp1, yf1);
  InterestRate rate2(comp1, yf2);
  InterestRate rate(comp2, yf1);
  //
  // Building benchmark instruments
  //
  BuildLinearInstrument builder;
  builder.usingCalendar(calendar);
  builder.withInterestRate(rate1);
  builder.withTradeDate(today);

  Deposit depo_ON =  builder.withTenor(OVERNIGHT).withQuote(0.016);
  Deposit depo_TN =  builder.withTenor(TOMORROWNEXT).withQuote(0.0161);
  Deposit depo_3M =  builder.withTenor(3 * MONTH).withQuote(0.0165);

  FRA FRA_3x6   = builder.withForwardTenors(3 * MONTH, 6 * MONTH).withQuote(0.01685);
  FRA FRA_6x9   = builder.withForwardTenors(6 * MONTH, 9 * MONTH).withQuote(0.01653);
  FRA FRA_9x12  = builder.withForwardTenors(9 * MONTH, 12 * MONTH).withQuote(0.01633);
  FRA FRA_12x15 = builder.withForwardTenors(12 * MONTH, 15 * MONTH).withQuote(0.01623);
  FRA FRA_15x18 = builder.withForwardTenors(15 * MONTH, 18 * MONTH).withQuote(0.01625);
  FRA FRA_18x21 = builder.withForwardTenors(18 * MONTH, 21 * MONTH).withQuote(0.01648);
  FRA FRA_21x24 = builder.withForwardTenors(21 * MONTH, 24 * MONTH).withQuote(0.01668);

  builder.withInterestRateForFixedLeg(rate2);
  builder.withInterestRateForFloatingLeg(rate1);
  builder.withFixedLegFrequency(ANNUALLY);
  builder.withFloatingLegFrequency(SEMIANNUALLY);

  IRS IRS_3Y  = builder.withTenor(3*YEAR).withQuote(0.01774);
  IRS IRS_4Y  = builder.withTenor(4*YEAR).withQuote(0.01854);
  IRS IRS_5Y  = builder.withTenor(5*YEAR).withQuote(0.01942);
  IRS IRS_6Y  = builder.withTenor(6*YEAR).withQuote(0.02022);
  IRS IRS_7Y  = builder.withTenor(7*YEAR).withQuote(0.02094);
  IRS IRS_8Y  = builder.withTenor(8*YEAR).withQuote(0.02161);
  IRS IRS_9Y  = builder.withTenor(9*YEAR).withQuote(0.02222);
  IRS IRS_10Y = builder.withTenor(10*YEAR).withQuote(0.02280);
  IRS IRS_12Y = builder.withTenor(12*YEAR).withQuote(0.02403);
  IRS IRS_15Y = builder.withTenor(15*YEAR).withQuote(0.02556);
  IRS IRS_20Y = builder.withTenor(20*YEAR).withQuote(0.02643);
 
  std::vector<SmartPointer<ir::BuildingBlock> > instruments;

  instruments.push_back(depo_ON);
  instruments.push_back(depo_TN);
  instruments.push_back(depo_3M);
  
  instruments.push_back(FRA_3x6);
  instruments.push_back(FRA_6x9);
  instruments.push_back(FRA_9x12);
  instruments.push_back(FRA_12x15);
  instruments.push_back(FRA_15x18);
  instruments.push_back(FRA_18x21);
  instruments.push_back(FRA_21x24);
  
  instruments.push_back(IRS_3Y);
  instruments.push_back(IRS_4Y);
  instruments.push_back(IRS_5Y);
  instruments.push_back(IRS_6Y);
  instruments.push_back(IRS_7Y);
  instruments.push_back(IRS_8Y);
  instruments.push_back(IRS_9Y);
  instruments.push_back(IRS_10Y);
  instruments.push_back(IRS_12Y);
  instruments.push_back(IRS_15Y);
  instruments.push_back(IRS_20Y);

  //
  // Creating curve settings
  //
  LinearInterpolation interp1;
  AKIMA interp2;
  ir::InterpolateZCRate inputs;
  ir::CompoundedInterpolator interpolator1(interp1, inputs);
  ir::CompoundedInterpolator interpolator2(interp2, inputs);
  ir::ExtrapolateFlatZCR extrapolator;

  //
  // Creating bootstrappers
  //
  ir::SmoothForwardRates cf0;
  ir::SecondDerivativeCostFunction cf1(cf0);
  SmartPointer<ir::SmootherCostFunction> cost_function = cf1;

  ir::AlgebraicBootstrapper algebraic_bootstrapper;
  ir::RootFindingBootstrapper nr_bootstrapper;
  ir::UnconstrainedSmoother ucs_bootstrapper(cost_function, 1.0);

  //
  // Building curves and printing them
  //
  ir::InterpolatedCurve curve_algebraic = ir::BuildCurve()
    .asOfDate(today)
    .withCalendar(calendar)
    .withInterestRate(rate)
    .withInterpolator(interpolator2)
    .withExtrapolator(extrapolator)
    .usingEstimator(algebraic_bootstrapper)
    .withSetOfInstruments(instruments);
  SHOW(curve_algebraic);
  auto algebraic_data = getCurves(curve_algebraic, 2*WEEK, 20*YEAR, "algebraic");
  algebraic_data.printToCsv("algebraic", ';');

  ir::InterpolatedCurve curve_rf = ir::BuildCurve()
    .asOfDate(today)
    .withCalendar(calendar)
    .withInterestRate(rate)
    .withInterpolator(interpolator1)
    .withExtrapolator(extrapolator)
    .usingEstimator(nr_bootstrapper)
    .withSetOfInstruments(instruments);
  SHOW(curve_rf);
  auto rf_data = getCurves(curve_rf, 2*WEEK, 20*YEAR, "rf");
  algebraic_data.printToCsv("rootfinding", ';');

  ir::InterpolatedCurve curve_ucs = ir::BuildCurve()
    .asOfDate(today)
    .withCalendar(calendar)
    .withInterestRate(rate)
    .withInterpolator(interpolator1)
    .withExtrapolator(extrapolator)
    .usingEstimator(ucs_bootstrapper)
    .withSetOfInstruments(instruments);
  SHOW(curve_ucs);
  auto usmoothed_data = getCurves(curve_ucs, 2*WEEK, 20*YEAR,"usmooth");
  usmoothed_data.printToCsv("usmoothed", ';');
}
