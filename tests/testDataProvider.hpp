#include <juliant.hpp>

using namespace julian;

namespace TestContainer  {
  auto getOptionGreeksTestData() {
    DataFrame df("../tests/_data/OptionGreeksTest.csv", ';', true);
    std::vector<BlackScholesModel> models;
    std::vector<EuropeanOpt> options;
    std::vector<std::map<std::string, double> > results;

    for (int row = 1; row <= df.getNumberOfRows(); row++) {
      Date start_date = df.getDate("start_date", row, Date::Format::date1); 
      Date end_date = df.getDate("end_date", row, Date::Format::date1);

      EuropeanOpt option(start_date, start_date, end_date, end_date,
			 df.getDouble("Notional", row),
			 df.getDouble("strike", row),
			 df.getValue<CallPut>("Icp", row));
      ACT365 yf;
      ExponentialRate comp;
      InterestRate interest_rate(comp, yf);

      Calendar calendar = BuildCalendar()
	.withConvention(MODIFIEDFOLLOWING)
	.withSpotLag(0);
    
      ir::FlatCurve curve1(interest_rate, df.getDouble("r", row),
			   start_date, calendar);
      ir::FlatCurve curve2(interest_rate, df.getDouble("q", row),
			   start_date, calendar);
      FlatVolatility volatility(start_date,
				df.getDouble("Volatility",row),
				yf);
    
      BlackScholesModel model(start_date,
			      df.getDouble("Spot", row),
			      curve1, curve2, volatility);
      std::map<std::string, double> result;
      result["PV"]    = df.getDouble("PV", row);
      result["Delta"] = df.getDouble("delta", row);
      result["Gamma"] = df.getDouble("gamma", row);
      result["Vega"]  = df.getDouble("vega", row);
      result["Vanna"] = df.getDouble("vanna", row);
      result["Volga"] = df.getDouble("volga", row);
      
      models.push_back(model);
      options.push_back(option);
      results.push_back(result);
    }
    return std::tuple(models, options, results);
  }
}
