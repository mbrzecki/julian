#include <marketData/volatility/flatVolatility.hpp>
#include <utils/formatters.hpp>
#include <string>
#include <iomanip>
#include <cmath>

namespace julian {

  /** \brief Returns volatility. The same value is returned regardless of the given arguments
   */
  double FlatVolatility::getVolatility(double , Date ) const {
    return volatility_;
  }

  /** \brief Returns volatility. The same value is returned regardless of the given arguments
   */
  double FlatVolatility::getVolatility(double , double ) const {
    return volatility_;
  }

  /** \brief  Returns annualize variance  
   *
   * \f[variance = yearFraction(today, T) \times volatility^{2}\f]
   */
  double FlatVolatility::getVariance(double,Date T) const {
    return pow(volatility_,2)*getYearFraction(date_,T);
  }

  /** \brief Returns annualize variance 
   *
   * \f[variance = T *\times volatility^{2}\f]
   */
  double FlatVolatility::getVariance(double,double T) const {
    return pow(volatility_,2)*T;
  }

  /** \brief Shifts volatility by bump size provided
   *
   *  \param input bump size 
   */
  void FlatVolatility::bumpVolatility(double input) {
    volatility_ += input;
  }

  /** \brief Returns the date for which curve was defined.
   */
  Date FlatVolatility::getDate() const {
    return date_;
  }

  /** \brief Virtual copy constructor
   */
  FlatVolatility* FlatVolatility::clone() const {
    return new FlatVolatility(*this);
  }
  
  /** \brief Returns type of volatility surface 
   */
  std::string FlatVolatility::info() const {
    return "FlatVolatility";  
  }

  /** \brief Calculates year fraction
   *
   * This methods calculates the year fraction between two dates. 
   * The year fraction convention is defined during the construction of interest rate object. 
   */
  double FlatVolatility::getYearFraction(Date d1,Date d2) const {
    return yf_->operator()(d1,d2);
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, FlatVolatility& v) {
    s << "Object: FlatVolatility"
      << "\nDate: " << v.date_
      << "\nVolatility: " << formatter::percentage(v.volatility_);
    return s;
  }

}  // namespace julian
