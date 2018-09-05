#ifndef JULIAN_QUADRATICINTERPOLATION_HPP
#define JULIAN_QUADRATICINTERPOLATION_HPP

#include <mathematics/interpolation/interpolation.hpp>

namespace julian {
  /**
   * @file   quadraticInterpolation.hpp
   * @brief  File contains class of quadratic interpolant.
   */
  
  /** \ingroup interpolation
   * \brief Class implements the quadratic local interpolation technique
   *  
   * The idea of quadratic interpolation of set of points is to approximate value \f$y\f$ at a point \f$x\f$ by a line passing through two data points \f$(x_j,y_j)\f$ and \f$(x_{j+1},y_{j+1})\f$ closest to \f$(x,y)\f$. The formula for linear interpolation is:
   * \f[ y = y_j + \frac{y_{j+1} - y_j}{x_{j+1}^2 - x_j^2} (x^2-x_j^2) \f]
   * 
   * @image html quadratic_interpolation.png
   *
   * \pre x vector must be sorted.
   * \note Interpolation is only defined for interval defined by the first and the last argument given. The interpolation objects do not extrapolate values outside the interval.

   */

  class QuadraticInterpolation: public Interpolation {
  public:
    QuadraticInterpolation(){};
    virtual double operator()(const std::vector<double>&,const std::vector<double>&,const double&) const;
    virtual QuadraticInterpolation* clone() const;
    virtual std::string info() const;
    virtual unsigned int getMinSize() const;
    virtual ~QuadraticInterpolation(){};
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
