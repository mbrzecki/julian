#ifndef JULIAN_VOLATILITYSURFACE_HPP
#define JULIAN_VOLATILITYSURFACE_HPP

#include <string>
#include <dates/date.hpp>
#include <utils/smartPointer.hpp>
#include <dates/yearFractions/yearFraction.hpp>

namespace julian {
  /**
   * @file   volatility.hpp
   * @brief  File contains interface for volatility surface.
   */
  
  /** \ingroup volatility
   *  \brief The class interfaces volatility surface.  
   *
   * Volatility implements the interface for volatility surface. 
   *
   * More information see: \cite wystupsmile 
   * 
   */

  
  class Volatility {
  public:
    /** \brief default constructor
     */
    Volatility(){};
    /** \brief returns volatility for a give strike and date
     *
     * \param K strike 
     * \param T date
     * \return annualized volatility 
     */
    virtual double getVolatility(double K,Date T) const = 0;
    /** \brief returns volatility for a give strike and expiration time
     *
     * \param K strike 
     * \param T expiration time
     * \return annualized volatility 
     */
    virtual double getVolatility(double K,double T) const = 0;
    /** \brief returns variance for a give strike and date
     *
     * \param K strike 
     * \param T date
     * \return annualized variance 
     */
    virtual double getVariance(double K,Date T) const = 0;

    /** \brief returns variance for a give strike and expiration time
     *
     * \param K strike 
     * \param T expiration time
     * \return annualized variance 
     */
    virtual double getVariance(double K,double T) const = 0;
    /** \brief returns the date for which curve was defined.
     */
    virtual Date getDate() const = 0;
    /** \brief bump volatility
     *
     *  \param h bump size
     *  \note Depending on the implementation of volatility surface  bumping volatility may have different mechanism
     */
    virtual void bumpVolatility(double h) = 0;
    /** \brief Calculates year fraction
     *
     *This methods calculates the year fraction between two dates. 
     * The year fraction convention is defined during the construction of interest rate object. 
     */
    virtual double getYearFraction(Date,Date) const = 0;
    /** \brief virtual copy constructor
     */
    virtual Volatility* clone() const = 0;
    /** \brief type of volatility surface 
     */
    virtual std::string info() const = 0;
    /** \brief destructor
     */
    virtual ~Volatility(){};
  };
}  // namespace julian
#endif
