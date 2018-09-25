#include <juliant.hpp>
using namespace julian;

/**
 * \example bondsExample.cpp 
 * \brief This example show how to build different kinds of bonds. 
 *
 * @verbinclude bondsExample.dox 
 *
 */

int main () {
  //
  // Creating interest rates: default values are ACT365 and simple compounding
  //
  InterestRate rate;

  //
  // Building calendar
  //
  PLNHoliday holiday;  
  Calendar calendar = BuildCalendar()
    .withConvention(MODIFIEDFOLLOWING)
    .addHoliday(holiday)
    .withSpotLag(2);
  
  //
  // Building two curves: one for discounting and another for projection
  //  
  ir::FlatCurve discounting_curve = ir::BuildCurve()
    .asOfDate(20180531)
    .withCalendar(calendar)
    .withInterestRate(rate)
    .withZeroCouponRate(0.045);

  ir::FlatCurve projection_curve = ir::BuildCurve()
    .asOfDate(20180531)
    .withCalendar(calendar)
    .withInterestRate(rate)
    .withZeroCouponRate(0.055);

  //
  // Fixed income bond
  //  
  FixedIncomeBond fixed_bond = BuildBond()
    .usingCalendar(calendar)
    .withNotional(1000)
    .withStartDate(20180531)
    .withTenor(4*YEAR)
    .withFrequencyOfPayment(SEMIANNUALLY)
    .withCoupon(0.05)
    .withInterestRate(rate);

  std::cout << "Printing fixed income bond" << std::endl;   
  SHOW(fixed_bond);
  std::cout << "Valuation of fixed income bond" << std::endl<< std::endl; 
  fixed_bond.valuation(discounting_curve);   

  std::cout << std::endl << std::endl;

  //
  // Floating rate bond
  //  
  FloatingRateBond floating_bond = BuildBond()
    .usingCalendar(calendar)
    .withNotional(1000)
    .withStartDate(20180531)
    .withTenor(4*YEAR)
    .withFrequencyOfPayment(SEMIANNUALLY)
    .withMargin(0.01)
    .withInterestRate(rate);


  std::cout << "Printing floating rate bond" << std::endl; 
  SHOW(floating_bond);
  std::cout << "Valuation of floating rate bond" << std::endl << std::endl; 
  floating_bond.valuation(discounting_curve, projection_curve);

  std::cout << std::endl << std::endl;

  //
  // Zero coupon bond
  //  
  ZeroCouponBond zcbond = BuildBond()
    .usingCalendar(calendar)
    .withNotional(100000)
    .withStartDate(20180531)
    .withMaturityDate(20240531)
    .withFaceValue(0.995);

  std::cout << "Printing zero-coupon bond" << std::endl; 
  SHOW(zcbond);
  std::cout << "Valuation of zero-coupon bond" << std::endl << std::endl; 
  zcbond.valuation(discounting_curve);
}
