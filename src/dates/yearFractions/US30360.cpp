#include <dates/yearFractions/US30360.hpp>

namespace julian {
	/**
	* \brief Calculates year fraction
	*
	*
	* According to 30/360 US convention the year fraction is calculated using following formula:
	* \f[YearFraction(dates_1,date_2)  = \frac{360(Y_2 - Y_1)+30(M_2-M_1)+(D_2-D_1)}{360}\f] 
	* where:
	* * \f$Y_i\f$ is number of years in \f$date_i\f$,
	* * \f$M_i\f$ is number of months in \f$date_i\f$,
	* * \f$D_i\f$ is number of days in \f$date_i\f$. 
	*
	* Additionally the following adjustment is applied:
	* * If D_1 is 31, then change D_1 to 30.
	* * If D_2 is 31 and D_1 is 30 or 31, then change D_2 to 30
	*/
  double US30360::operator()(const Date& d1,const Date& d2) const {
    int dn1 = d1.getDay();
    int dn2 = d2.getDay();

    if( dn1 == 31 )
      dn1 = 30;
    if( dn2 == 31 && dn1 == 30  )
      dn2 = 30;

    int n =  360 * (d2.getYear()  - d1.getYear())
      + 30 * (d2.getMonth() - d1.getMonth())
      + dn2 - dn1;
    return  n / 360.0;;
  }

  /** \brief Virtual copy constructor
   * 
   * Virtual copy constructor of the US30360 class
   */
  US30360* US30360::clone() const {
    return new US30360(*this);
  }

  std::ostream& operator<<(std::ostream& s, US30360& ) {
    s << "30360US";
    return s;
  }

  /** \brief Name of a class
      
      Method returns string that containing information about class. 
  */
  std::string US30360::info() const {
    return "30360US";
  }
}  // namespace julian
