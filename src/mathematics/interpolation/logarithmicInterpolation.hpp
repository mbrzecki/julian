#ifndef JULIAN_LOGARITHMIC_HPP
#define JULIAN_LOGARITHMIC_HPP

#include <mathematics/interpolation/interpolation.hpp>

namespace julian {
  /**
   * @file   logarithmicInterpolation.hpp
   * @brief  File contains class of logarithmic interpolant.
   */
  
  /** \ingroup interpolation
   * \brief Class implements the logarithmic local interpolation technique
   *  
   * The idea of linear interpolation of set of point is to approximate value \f$y\f$ at a point \f$x\f$ by a line passing through two data points \f$(x_j,y_j)\f$ and \f$(x_{j+1},y_{j+1})\f$ 
   * closest to \f$(x,y)\f$. The formula for linear interpolation is:
   * \f[ y = y_j + \frac{y_{j+1} - y_j}{ln(x_{j+1}) - ln(x_j)} (ln(x) - ln(x_j))\f]
   * 
   *
   *
   * \pre x vector must be sorted.
   * \note Interpolation is only defined for interval defined by the first and the last argument given. The interpolation objects do not extrapolate values outside the interval.
   * \note x must be positive.
   */

  class LogarithmicInterpolation: public Interpolation {
  public:
    LogarithmicInterpolation(){};
    virtual double operator()(const std::vector<double>&,const std::vector<double>&,const double&) const;
    virtual LogarithmicInterpolation* clone() const;
    virtual ~LogarithmicInterpolation(){};
    virtual unsigned int getMinSize() const;
    virtual std::string info() const;
    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int){
      boost::serialization::base_object<Interpolation>(*this);
    }
  };
}  // namespace julian

#endif
