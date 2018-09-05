#ifndef JULIAN_FLATVOLATILITYSURFACE_HPP
#define JULIAN_FLATVOLATILITYSURFACE_HPP

#include <marketData/volatility/volatility.hpp>
#include <iostream>
#include <string>

namespace julian {
  /**
   * @file   flatVolatility.hpp
   * @brief  File contains definition of flat volatility surface.
   */
  
  /** \ingroup volatility
   *  \brief Class implements flat volatility
   *
   * Flat volatility surface is a volatility with no tenor- nor strike- dependencies.
   * It returns the same volatility level for every strike or tenor.  
   * 
   */

  class FlatVolatility: public Volatility  {
  public:

    /** \brief constructor
     */
    FlatVolatility(Date date, double volatility, SmartPointer<YearFraction> yf):
      date_(date), volatility_(volatility), yf_(yf) {};
    
    double getVolatility(double K, Date T) const override;
    double getVolatility(double K, double T) const override; 
    double getVariance(double K, Date T) const override;
    double getVariance(double K, double T) const override;
    Date getDate() const override;
    void bumpVolatility(double) override;
    
    double getYearFraction(Date,Date) const override;
    
    FlatVolatility* clone() const override;
    std::string info() const override;
    ~FlatVolatility(){};

    friend std::ostream& operator<<(std::ostream&, FlatVolatility&);
  private:
    Date date_; /*!< \brief represent the date on which the curve is valid*/
    double volatility_; /*!< \brief volatility level*/
    SmartPointer<YearFraction> yf_; /*!< \brief Year fraction convention*/
  };
}
#endif
