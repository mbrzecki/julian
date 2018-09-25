#include <dates/yearFractions/ActActAFB.hpp>
#include <boost/assert.hpp>

namespace julian {

	/**
	* \brief Method calculates the year fraction on the basis of two dates.
	* In case of AFB (Association Francaise des Banques) convention the year fraction is calculated with formula:
	* \f[YearFraction(date_1,date_2) = \frac{\textrm{Actual number of days}}{\textrm{Denominator}}\f]
	* Denominator is equal 366 if period \f$(date_1,date_2)\f$ contains 29th of February and 365 otherwise.
	* \see \cite OGguide
	*/
  double ActActAFB::operator()(const Date& d1, const Date& d2) const {
    double denominator = 365.0;
    double numerator = (d1.getN() - d2.getN());

    if (d1.isLeapYear()) {
      Date thisLoopYear29Feb(d1.getYear(), FEB, 29);
      Date nextLoopYear29Feb(d1.getYear() + 4, FEB, 29);

      if (d1.getN() <= thisLoopYear29Feb.getN() && d2.getN() >= thisLoopYear29Feb.getN())
	denominator += 1.0;
      if (d1.getN() >= thisLoopYear29Feb.getN() && d2.getN() >= nextLoopYear29Feb.getN())
	denominator += 1.0;

    } else {
      int aux = 4 - (d1.getYear() % 4);
      Date next29Feb(d1.getYear() + aux, FEB, 29);
      if ( next29Feb.getN() < d2.getN())
	denominator += 1.0;
    }
    return numerator / denominator;
  }

  /** \brief Virtual copy constructor of the ACTACT class
   */
  ActActAFB* ActActAFB::clone() const {
    return new ActActAFB(*this);
  }

  /** \brief The method returns string containing the name of convention.
   */
  std::string ActActAFB::info() const {
    return "ACTACT_AFB";
  }
}  // namespace julian
