#include <juliant.hpp>
#include "factoryInit.hpp"

/**
 * \example constrainedBootstrapperExample.cpp 
 * \brief This example show how to build curve using constrained bootstrapper (ConstrainedBootstrapper). Programme uses data files stored as csv in ./data directory 
 *
 *
 * Plots below presents the interest rate curves build using different smoothing parameters. Larger smoothing parameter produce smoother curve
 * @image html constrained_curves_smoothing.png
 * Here we present the calibration of the curve. Note that difference between model and market is controlled by smoothing parameter. Larger smoothing parameter expends the area where solver searches for minimum.
 * @image html constrained_curves_calibration.png
 * Here we present the effect of interpolation method on the curve. 
 * @image html constrained_curves_interpolation.png
 */

using namespace julian;


int main(int argc, char *argv[]) {
  RunTimeMeasurment timer;
  //
  // Setting the calendar and the today date
  //
  
  Date today(2018, JUN, 20);
  PLNHoliday holiday;
  Calendar calendar = BuildCalendar()
    .withConvention(MODIFIEDFOLLOWING)
    .addHoliday(holiday)
    .withSpotLag(2);

  //
  // Reading the command line arguments; If not provided, program uses default names
  //
  auto args =  catchDataAndSettingFileNames(argc, argv);
  auto data_file     = args.first.empty() ? "../data/curve_data.csv" : args.first;
  auto settings_file = args.second.empty() ? "../data/curve_settings.csv" : args.second;

  //
  // Creating benchmark instruments
  //
  DataFrame df_instruments(data_file, ';', true);
  auto df_depo = df_instruments.filter("Type",   [](std::string x)->bool{return x == "Deposit";} );
  auto df_fra  = df_instruments.filter("Type",   [](std::string x)->bool{return x == "FRA";} );
  auto df_irs  = df_instruments.filter("Type",   [](std::string x)->bool{return x == "IRS";} );

  std::vector<Deposit> deposits = ir::readDeposit(df_depo, today, calendar);
  std::vector<FRA> fras     = ir::readFRA(df_fra, today, calendar);
  std::vector<IRS> swaps    = ir::readIRS(df_irs, today, calendar);

  std::vector<SmartPointer<ir::BuildingBlock> > benchmarks;
  benchmarks.insert(benchmarks.end(), deposits.begin(), deposits.end());
  benchmarks.insert(benchmarks.end(), fras.begin(), fras.end());
  benchmarks.insert(benchmarks.end(), swaps.begin(), swaps.end());

  //
  // Reading curve settings
  //
  DataFrame df_settings(settings_file, ';', true);
  df_settings = df_settings.filter("Estimator",[](std::string x)->bool{return x == "constrained";} );


  //
  // Constructing the curve
  //
  DataFrame estimation_resuts;
  DataFrame calibration_results;
  
  for (int r = 1; r <=df_settings.getNumberOfRows(); r++) {
    auto set_name = df_settings("Id", r);
    std::cout << set_name << std::endl;
    auto interpolation = df_settings.getObject<Interpolation>("Interpolation", r);
    auto inputs        = df_settings.getObject<ir::InterpolationInput>("InterpolationInput", r);
    auto compounding   = df_settings.getObject<Compounding>("Compounding", r);
    auto yf            = df_settings.getObject<YearFraction>("YF", r);

    auto smoothing_param = df_settings.getDouble("SmoothingParam", r);
    auto iterations      = df_settings.getDouble("Iterations", r);

    SmartPointer<ir::SmootherCostFunction> scf = df_settings.getObject<ir::SmootherCostFunction>("SmoothingInput",r);

    if (df_settings.getDouble("FirstDerivative", r)) {
      scf = ir::FirstDerivativeCostFunction(scf);
    }
    if (df_settings.getDouble("SecondDerivative", r)) {
      scf = ir::SecondDerivativeCostFunction(scf);
    }

    InterestRate rate(compounding, yf);
    ir::CompoundedInterpolator interpolator(interpolation, inputs);
    auto estimator = ir::ConstrainedSmoother(scf, smoothing_param, iterations);

    ir::InterpolatedCurve curve = ir::BuildCurve()
      .asOfDate(today)
      .withCalendar(calendar)
      .withInterestRate(rate)
      .withInterpolator(interpolator)
      .withSetOfInstruments(benchmarks)
      .usingEstimator(estimator);

    auto calib      = ir::getCalibration(curve, benchmarks, set_name);
    auto curve_data = ir::getCurves(curve, 1*WEEK, 15*YEAR, set_name);
    calibration_results.append(calib);
    estimation_resuts.append(curve_data);
  }

  //
  // Saving results
  //
  calibration_results.printToCsv("constrained_calibration");
  estimation_resuts.printToCsv("constrained_results");
}

