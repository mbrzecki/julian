#include <juliant.hpp>

using namespace julian;

namespace TestContainer  {

  auto GetEuropeanOpt() {
    return EuropeanOpt(20190101,
		       20190101,
		       20210101,
		       20210101,
		       1000.0,
		       100.0,
		       CallPut::CALL);
  }

  auto GetBlackScholesModel() {
    Date today(2019,JAN,1);
    Calendar calendar = BuildCalendar()
      .withConvention(MODIFIEDFOLLOWING)
      .withSpotLag(0);

    ACT365 yf;
    ExponentialRate comp;
    InterestRate rate(comp, yf);

    ir::FlatCurve curve1(rate, 0.05, today, calendar);
    ir::FlatCurve curve2(rate, 0.02, today, calendar);
    FlatVolatility volatility(today, 0.15, yf);

    return BlackScholesModel(today, 100.0, curve1, curve2, volatility);
  }
  
}
