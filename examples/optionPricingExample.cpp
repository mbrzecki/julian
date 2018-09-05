#include <juliant.hpp>

/**
 * \example optionPricingExample.cpp 
 * \brief This example show how to price option using Black-Scholes model.  
 *
 * <table style="width:100%">
 * <tr>
 * <th></th>
 * <th></th> 
 * </tr>
 * <tr>
 * <td>@image html option_example_call_pv.png</td>
 * <td>@image html option_example_put_pv.png</td> 
 * </tr>
  * </tr>
 * <tr>
 * <td>@image html option_example_call_delta.png</td>
 * <td>@image html option_example_put_delta.png</td> 
 * </tr>
  * </tr>
 * <tr>
 * <td>@image html option_example_gamma.png</td>
 * <td>@image html option_example_vega.png</td> 
 * </tr>
  * </tr>
 * <tr>
 * <td>@image html option_example_volga.png</td>
 * <td>@image html option_example_vanna.png</td> 
 * </tr>
 * </table>
 */
using namespace julian;

int main() {
  //
  // Defining auxiliary objects
  //
  Date today(2018,APR,26);
  PLNHoliday holiday;
  Calendar calendar = BuildCalendar()
    .withConvention(MODIFIEDFOLLOWING)
    .addHoliday(holiday)
    .withSpotLag(2);

  InterestRate rate;
  ACT365 yf;
  
  //
  // Creating market model
  //
  ir::FlatCurve curve1(rate, 0.05, today, calendar);
  ir::FlatCurve curve2(rate, 0.02, today, calendar);
  FlatVolatility volatility(today, 0.15, yf);

  BlackScholesModel model(today, 100.0, curve1, curve2, volatility);

  //
  // Creating option
  //
  auto exp = today + 2*YEAR;
  EuropeanOpt option_c(today, today, exp, exp, 1000.0, 100.0, CALL);
  EuropeanOpt option_p(today, today, exp, exp, 1000.0, 100.0, PUT);

  //
  // Creating pricer and  greeks report
  //
  AnalyticalPricingEngine pricer;

  SmartPointer<OptionGreeks> risks = BuildGreeksReport()
    .withDelta()
    .withDelta(1e-4, NumDiffScheme::FWD, "Delta_fwd")
    .withDelta(1e-3, NumDiffScheme::BWD, "Delta_bwd")
    .withGamma()
    .withVega()
    .withVolga()
    .withVanna()
    .withTheta()
    .build();

  //
  // Performing calculations
  //
  DataFrame df;

  for (double s = 50.0; s <= 150.0; s += 0.25) {
    model.setAssetPrize(s);
    auto greeks = risks->getRisks(model, pricer, option_c);
	
    DataEntryClerk input;
    input.add("Spot", s);
    input.add("Type", "Call");
    input.add(greeks);
	
    df.append(input);
  }
  for (double s = 50.0; s <= 150.0; s += 0.25) {
    model.setAssetPrize(s);
    auto greeks = risks->getRisks(model, pricer, option_p);
	
    DataEntryClerk input;
    input.add("Spot", s);
    input.add("Type", "Put");
    input.add(greeks);
	
    df.append(input);
  }
  df.printToCsv("options",';');
}
