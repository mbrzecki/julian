#include <string>
#include <dates/yearFractions/E30360.hpp>

namespace julian {

	/**
	* \brief Calculates year fraction
	*
	* Method calculates the year fraction on the basis of two dates.
	* An object of E30360 class is derived from YearFraction. It calculates year fraction on the basis of two dates using the formula:
	* \f[YearFraction(date_1,date_2) = \frac{360 \times (Y_{2}-Y_{1}) +30 \times (M_{2}-M_{1})+min(D_{2},30) - min(D_{1},30)}{360}\f] 
	* where: \f$\textrm{Y}_{i}\f$ is a year number of the \f$\textrm{date}_{i}\f$, \f$\textrm{M}_{i}\f$ is a month number of the  \f$\textrm{date}_{i}\f$ and  \f$\textrm{D}_{i}\f$ is a day number of the  \f$\textrm{date}_{i}\f$. 
	*
	*/
  double E30360::operator()(const Date& d1, const Date& d2) const {
    int dn1 = d1.getDay();
    int dn2 = d2.getDay();

    if (dn1 == 31)
      dn1 = 30;
    if (dn2 == 31)
      dn2 = 30;

    int n = 360 * (d2.getYear()  - d1.getYear())
      +  30 * (d2.getMonth() - d1.getMonth())
      + dn2 - dn1;

    return n / 360.0;;
  }

  /** \brief Virtual copy constructor
   * 
   * Virtual copy constructor of the E30360 class
   */

  E30360* E30360::clone() const {
    return new E30360(*this);
  }

  /** \brief Name of a class
      
      Overloading << operator
  */
  std::ostream& operator<<(std::ostream& s, E30360&) {
    s << "YearFraction: E30360";
    return s;
  }
  
  /** \brief Name of a class
      
      Method returns string that containing information about class. 
  */
  std::string E30360::info() const {
    return "E30360";
  }
}  // namespace julian
