#ifndef JULIAN_CUBICINTERPOLATION_HPP
#define JULIAN_CUBICINTERPOLATION_HPP

#include <mathematics/interpolation/interpolation.hpp>

namespace julian {
  /**
   * @file   cubicInterpolation.hpp
   * @brief  File contains class of cubic interpolant.
   */
  
  /** \ingroup interpolation
   * \brief Class implements the cubic local interpolation technique
   *  
   * The idea of linear interpolation of set of point is to approximate value \f$y\f$ at a point \f$x\f$ by a line passing through two data points \f$(x_j,y_j)\f$ and \f$(x_{j+1},y_{j+1})\f$ closest to \f$(x,y)\f$. The formula for cubic interpolation is:
   * \f[ y =  y_j + \frac{y_{j+1} - y_j}{x_{j+1}^3 - x_j^3} (x^3-x_j^3)\f]
   * 
   * @image html cubic_interpolation.png
   * 
   * \pre x vector must be sorted.
   * \note Interpolation is only defined for interval defined by the first and the last argument given. The interpolation objects do not extrapolate values outside the interval.
   *
   */

  class CubicInterpolation: public Interpolation {
  public:
    CubicInterpolation(){};
    virtual double operator()(const std::vector<double>&,const std::vector<double>&,const double&) const;
    virtual CubicInterpolation* clone() const;
    virtual ~CubicInterpolation(){};
    virtual std::string info() const;
    virtual unsigned int getMinSize() const;
    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int){
      boost::serialization::base_object<Interpolation>(*this);
    }
  };
}
#endif
