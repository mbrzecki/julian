#include <juliant.hpp>
#include "factoryInit.hpp"
#include <algorithm>
#include <vector>
#include <set>

/**
 * \example algebraicBootstrapperExample.cpp 
 * \brief This example show how to build curve using Algebraic bootstrapper. Programme uses data files stored as csv in ./data directory 
 *
 * @verbinclude algebraicBootstrapperExample.dox 
 *
 * Plots below presents the interest rate curves build using different interpolation type
 * @image html algebraic_curves_interpolation.png
 * Plots below presents the interest rate curves build using different interpolation inputs
 * @image html algebraic_curves_inputs.png
 * Here we present the calibration of the curve. We see perfect match between market quotings and curve implied par rates.
 * @image html algebraic_curves_calibration.png
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

  //
  // Printing instruments set
  //
  SHOW(df_instruments);
  std::vector<Deposit> deposits = ir::readDeposit(df_depo, today, calendar);
  std::vector<FRA> fras     = ir::readFRA(df_fra, today, calendar);
  std::vector<IRS> swaps    = ir::readIRS(df_irs, today, calendar);

  std::vector<SmartPointer<ir::BuildingBlock> > instruments;
  instruments.insert(instruments.end(), deposits.begin(), deposits.end());
  instruments.insert(instruments.end(), fras.begin(), fras.end());
  instruments.insert(instruments.end(), swaps.begin(), swaps.end());

  //
  // Reading data settings
  //
  DataFrame df_settings(settings_file, ';', true);
  df_settings = df_settings.filter("Estimator", [](std::string x)->bool{return x == "algebraic";} );

  //
  // Printing curves' settings
  //
  SHOW(df_settings);

  //
  // Constructing the curve
  //
  DataFrame estimation_resuts;
  DataFrame calibration_results;
  
  for (int r = 1; r <=df_settings.getNumberOfRows(); r++) {
    auto set_name = df_settings("Id", r);

    auto interpolation = df_settings.getObject<Interpolation>("Interpolation", r);
    auto inputs        = df_settings.getObject<ir::InterpolationInput>("InterpolationInput", r);
    auto compounding   = df_settings.getObject<Compounding>("Compounding", r);
    auto yf            = df_settings.getObject<YearFraction>("YF", r);

    InterestRate rate(compounding, yf);
    ir::CompoundedInterpolator interpolator(interpolation, inputs);
    ir::AlgebraicBootstrapper estimator;

    ir::InterpolatedCurve curve = ir::BuildCurve()
      .asOfDate(today)
      .withCalendar(calendar)
      .withInterestRate(rate)
      .withInterpolator(interpolator)
      .withSetOfInstruments(instruments)
      .usingEstimator(estimator);

    auto calib      = ir::getCalibration(curve, instruments, set_name);
    auto curve_data = ir::getCurves(curve, 1*WEEK, 15*YEAR, set_name);
    calibration_results.append(calib);
    estimation_resuts.append(curve_data);
  }

  //
  //  Saving results
  //
  calibration_results.printToCsv("algebraic_bootstrapper_calibration");
  estimation_resuts.printToCsv("algebraic_bootstrapper_results");

}

