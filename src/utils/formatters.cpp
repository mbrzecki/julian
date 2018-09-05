#include <utils/formatters.hpp>


namespace julian {
  namespace formatter {
    /** \ingroup utils				       
     *
     * \fn std::string currency(double x) 
     * \brief Function converts double to money value.
     * 
     *  Function converts double to money value. For example: 12345.6789 to 12'345.68
     *
     * \param x Given number
     * \return string representing money value
     */
    std::string currency(double x) {
      std::string sign;
      if (x > 0) {
	sign = " ";
      } else {
	sign = "-";
      }

      x  = x > 0 ? x : -x;

      if ( x < 0.009)
	return "0.00";
      std::string x_string, digit;
      int i = -2;
      unsigned long long v = (unsigned long long) ( (x *100) + .5);

      do {
	if (i == 0) {
	  x_string = "." + x_string;
	}

	if ((i > 0) && (!(i % 3))) {
	  x_string = "'" + x_string;
	}

	digit = (v % 10) + '0';
	x_string = digit + x_string;
	v /= 10;
	i++;
      } while ((v) || (i < 1));
      return (sign +  x_string);
    }

    /** \ingroup utils				       
     *
     * \fn std::string percentage(double x) 
     * \brief Function converts double to percentage.
     * 
     *  Function converts double to money value. For example: 0.054321 to 5.4321%
     *
     * \param x Given number
     * \return string representing money value
     */
    std::string percentage(double x) {
      auto xstr = std::to_string(100.0*x);
      return xstr.substr(0,6) + "%";
    }
  }  // namespace formatter
}  // namespace julian
