#include <juliant.hpp>

using namespace julian;

/**
   \example InterestRateExample.cpp 
   \brief This example show how to use interest class and compounding classes.
   
   @verbinclude InterestRateExample.dox 
 */

int main() {
  //  To show how to use interest rate and compounding classes, we will need some auxiliary objects/
  //  like dates, year fraction calculator and accrual period, interest rate value and future value.
  
  Date date_start(2015,8,26);
  
  Date date_middle(2016,3,11);
  double DF_middle = 0.950;

  Date date_end(2016,12,15);
  double DF_end = 0.875;

  ACT365 yf;

  double r = 0.05;
  double accrual_period = 0.85;
  double future_value = 1.025;
  
  /********************
   *** COMPOUNDINGS ***
   ********************/

  SimpleRate simple;
  CompoundedRate compounded;
  ExponentialRate exponential;

  // Following code presents how to perform calculation of capitalization and interest rate, according to a given convention. 
  
  std::cout <<"Future value of 1 CU calculated with simple rate compounding, interest rate = "
	    << r <<" accrual_period= " << accrual_period << " is " << simple.getCapitalization(r, accrual_period) << std::endl;
  
  std::cout << "Interest rate calculated with simple rate compounding, future value = "
	    << future_value << " accrual_period= " << accrual_period << " is " << simple.getRate(future_value, accrual_period) << std::endl << std::endl;  

  std::cout << "Future value of 1 CU calculated with compounded rate compounding, interest rate = "
	    << r <<" accrual_period= " << accrual_period << " is " << compounded.getCapitalization(r, accrual_period) << std::endl; 
  std::cout << "Interest rate calculated with compounded rate compounding, future value = "
	    << future_value << " accrual_period= " << accrual_period << " is " << compounded.getRate(future_value, accrual_period) << std::endl << std::endl; 

  std::cout << "Future value of 1 CU calculated with exponential rate compounding, interest rate = "
	    << r <<" accrual_period= " << accrual_period << " is " << exponential.getCapitalization(r, accrual_period) << std::endl; 
  std::cout << "Interest rate calculated with exponential rate compounding, future value = "
	    << future_value << " accrual_period= " << accrual_period << " is " << exponential.getRate(future_value, accrual_period)
	    << std::endl << std::endl << std::endl << std::endl;

  InterestRate simple_rate(simple, yf);
  InterestRate compounded_rate(compounded, yf);
  InterestRate exponential_rate(exponential, yf);

  std::cout << "Below calculation was performed for three different interest rate instances. Values of input data are as follows:\n"
  	    << "starting date:\t\t " << date_start
  	    << "\nmiddle date:\t\t " << date_middle
  	    << "\nend date:\t\t " << date_end
  	    << "\ninterest rate:\t\t " << r
  	    << "\nDF for middle date:\t " << DF_middle
    	    << "\nDF for end date:\t " << DF_end
  	    << "\n\nCapitaliation is a future value of 1CU at end date invested at starting date. "
	    << "Discount factor is present value of 1CU receive at end date.\nCoupon is the yield on investement starting at start date and ending at end date."
	    << "Zerocoupon is annualized yield rate of mention investment.\nForward rate is a rate form middle date " 
	    << "to end date if the present value of 1CU received on those dates is know." << std::endl << std::endl;

  std::cout << "Simple interest rate:\n "
  	    << "capitalization= " << simple_rate.capitalization(date_start, date_end, r) << " "
  	    << "discount factor= " << simple_rate.DF(date_start, date_end, r) << " "
    	    << "coupon= " << simple_rate.coupon(date_start, date_end, r) << " "
      	    << "zerocoupon rate= " << simple_rate.zcRate(date_start, date_end, DF_end) << " "
  	    << "forward rate= " << simple_rate.fwdRate(date_middle, date_end, DF_middle, DF_end) << std::endl;

  std::cout << "Compounded interest rate:\n  "
  	    << "capitalization= " << compounded_rate.capitalization(date_start, date_end, r)<<" "
  	    << "discount factor= " << compounded_rate.DF(date_start, date_end, r)<<" "
    	    << "coupon= " << compounded_rate.coupon(date_start, date_end, r)<<" "
      	    << "zerocoupon rate= " << compounded_rate.zcRate(date_start, date_end, DF_end)<<" "
  	    << "forward rate= " << compounded_rate.fwdRate(date_middle, date_end, DF_middle, DF_end)<<std::endl;

  std::cout << "Exponential interest rate:\n "
  	    << "capitalization= " << exponential_rate.capitalization(date_start, date_end, r)<<" "
  	    << "discount factor= " << exponential_rate.DF(date_start, date_end, r)<<" "
    	    << "coupon= " << exponential_rate.coupon(date_start, date_end, r)<<" "
      	    << "zerocoupon rate= " << exponential_rate.zcRate(date_start, date_end, DF_end)<<" "
  	    << "forward rate= " << exponential_rate.fwdRate(date_middle, date_end, DF_middle, DF_end)<<std::endl; 

}
