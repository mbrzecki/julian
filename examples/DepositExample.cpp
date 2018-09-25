#include <juliant.hpp>

/**
 * \example DepositExample.cpp 
 * \brief This example show how to create and value deposits.
 *
 *@verbinclude DepositExample.dox 
 *
 */

using namespace julian;
using namespace std;

int main() {
  //
  // Defining auxiliary objects: calendar, interestRate, interest rate
  //
  Date today(2015,JUL,17);
  
  PLNHoliday hol1;
  
  Calendar calendar = BuildCalendar()
    .withConvention(MODIFIEDFOLLOWING)
    .addHoliday(hol1)
    .withSpotLag(2);

  SimpleRate simple;
  ACT365 yfact;
  InterestRate wibor(simple,yfact); 

  ir::FlatCurve discounting_curve(wibor, 0.045, today, calendar);
  
  //
  // Defining deposits
  //
  Deposit deposit1 = BuildLinearInstrument()
    .withTradeDate(today)
    .usingCalendar(calendar)
    .withNotional(10000)
    .withInterestRate(wibor)
    .withQuote(0.0515)
    .withTenor(1*MONTH);

  Deposit deposit2 = BuildLinearInstrument()
    .usingCalendar(calendar)
    .withNotional(2000000)
    .withInterestRate(wibor)
    .withQuote(0.0495)
    .withTradeDate(2015, MAY, 15)
    .withTenor(6*MONTH);
  
  Deposit deposit3 = BuildLinearInstrument()
    .withNotional(500000)
    .withInterestRate(wibor)
    .withQuote(0.0495)
    .withTradeDate(2015, APR, 17)
    .withStartDate(2015, APR, 18)
    .withMaturityDate(2015, AUG, 22);

  Deposit deposit4 = BuildLinearInstrument()
    .usingCalendar(calendar)
    .withNotional(307000)
    .withInterestRate(wibor)
    .withQuote(0.0548)
    .withTradeDate(2014, OCT, 24)
    .withStartDate(2014, OCT, 24)
    .withMaturityDate(2015, NOV, 6);

  std::cout << "\tPrinting deposit\n";
  //
  // Printing deposits
  //
  SHOW(deposit2);

  //
  // Value deposits
  //
  std::cout << "\tPricing deposit\n\n";
  deposit4.valuation(discounting_curve);
}
