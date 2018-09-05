#include <dates/yearFractions/ActActISDA.hpp>
#include <boost/assert.hpp>

namespace julian {

	/**
	* \brief Method calculates the year fraction on the basis of two dates.
	*
	* With ISDA convention (International Swaps and Derivative Association) the year fraction is calculated according to the formula:
	* \f[YearFraction(date_1,date_2) = \frac{\textrm{Number of days in non-leap year}}{365} + \frac{\textrm{Number of days in leap year}}{366}\f]
	*/
  double ActActISDA::operator()(const Date& input1, const Date& input2) const {
    Date date1(input1.getYear() + 1, JAN, 1);
    Date date2(input2.getYear(), JAN, 1);

    double d1basis = 366.0;
    double d2basis = 366.0;

    if (input1.getYear() % 4)
      d1basis = 365;
    if (input2.getYear() % 4)
      d2basis = 365;

    double yf = (date1.getN() - input1.getN()) / d1basis;
    yf += input2.getYear() - input1.getYear()-1;
    yf += (input2.getN() - date2.getN()) / d2basis;

    return yf;
  }

  /** Virtual copy constructor of the ACTACT ISDA class
   */
  ActActISDA* ActActISDA::clone() const {
    return new ActActISDA(*this);
  }

  /** The method returns string containing the name of convention.
   */
  std::string ActActISDA::info() const {
    return "ACTACT_ISDA";
  }
}
