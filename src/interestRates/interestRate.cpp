#include <interestRates/interestRate.hpp>
#include <dates/yearFractions/ACT365.hpp>
#include <interestRates/simpleRate.hpp>
namespace julian {

  /**
     \brief Constructor
   
     Method creates the interest rate instance on the basis of compounding and year fraction convention.
     
  */
  InterestRate::InterestRate() {
    compounding_ = SimpleRate();
    year_fraction_ = ACT365();
  }
  
  /**
    \brief Constructor
   
    Method creates the interest rate instance on the basis of compounding and year fraction convention.
     
  */
  InterestRate::InterestRate(const SmartPointer<Compounding>& compounding, const SmartPointer< YearFraction>& year_fraction):
    compounding_(compounding), year_fraction_(year_fraction) {}

  /** \brief Calculates capitalization
	
      This method calculates the future value of 1 monetary unit. More specifically it calculates what is the value of 1 monetary unit invested on date1 at a rate of r per year. 
	  The investment ends at date2. The compounding and year fraction convention is defined during construction of the interest rate object.
  */
  double InterestRate::capitalization(Date d1,Date d2, double r) const {
    double t = (*year_fraction_)(d1, d2);
    return (*compounding_).getCapitalization(r, t);;
}

  /** \brief Calculates discount factor

      This method calculates the present value of 1 monetary unit. 
	  More specifically it calculates how many monetary units should be invested at date1 at a rate of r per year in order to receive 1 monetary unit at date2. 
	  The compounding and year fraction convention is defined during construction of the interest rate object.
  */ 
  double InterestRate::DF(Date d1, Date d2, double r) const {
    double t = (*year_fraction_)(d1, d2);
    return  1 / (*compounding_).getCapitalization(r, t);
  }

  /**  \brief Calculates coupon

       This method calculates the yield of investment that starts at date1 and ends at date2. The interest rate value should be provided. 
	   The compounding and year fraction convention is defined during construction of the interest rate object. 
  */
  double InterestRate::coupon(Date d1, Date d2, double r) const {
    double t = (*year_fraction_)(d1, d2);
    return (*compounding_).getCapitalization(r, t) - 1.0;
}

  /** \brief Calculates forward rate
    
      This methods calculate forward rate on the basis of two discount factors and two dates. 
	  The forward rate is the interest rate for the investment that starts at future date date1 and ends at date2. 
	  The compounding and year fraction convention is defined during construction of the interest rate object. 
  */ 
  double InterestRate::fwdRate(Date d1,Date d2, double DF1, double DF2) const {
    double t = (*year_fraction_)(d1, d2);
    double x = DF1 / DF2;
    return (*compounding_).getRate(x, t);
}

  /** \brief Calculates zero coupon rate

      This methods calculate zero coupon rate on the basis of discount factor and two dates. 
	  The zero coupon rate is the interest rate for the investment that starts at date1 and ends at datd2. 
	  The compounding and year fraction convention is defined during construction of the interest rate object.
  */
  double InterestRate::zcRate(Date d1, Date d2, double DF) const {
    double t = (*year_fraction_)(d1, d2);
    return (*compounding_).getRate(1/DF, t);;
  }

  /** \brief Calculates year fraction
	
      This methods calculates the year fraction between two dates. The year fraction convention is defined during the construction of interest rate object. 
  */
  double InterestRate::yf(Date d1, Date d2) const {
    return (*year_fraction_)(d1, d2);
  }

  /** \brief Virtual copy constructor
    
      Method is an implementation of virtual copy constructor.
  */
  InterestRate* InterestRate::clone() const {
    return new InterestRate(*this);
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, InterestRate& r) {
    std::string yf = r.year_fraction_->info();
    std::string cm = r.compounding_->info();
    s << yf << "_" << cm;
    return s;
  }
}  // namespace julian
