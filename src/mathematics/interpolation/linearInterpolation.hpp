#ifndef JULIAN_LINEARINTERPOLATION_HPP
#define JULIAN_LINEARINTERPOLATION_HPP

#include <mathematics/interpolation/interpolation.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>

namespace julian {

  /**
   * @file   linearInterpolation.hpp
   * @brief  File contains class of linear interpolant.
   */
  
  /** \ingroup interpolation
   * \brief Class implements the linear local interpolation technique
   *  
   * The idea of linear interpolation of set of point is to approximate value \f$y\f$ at a point \f$x\f$ by a straight line passing through two data points \f$(x_j,y_j)\f$ and \f$(x_{j+1},y_{j+1})\f$ closest to \f$(x,y)\f$. 
   The formula for linear interpolation is:
   * \f[ y =  y_j + \frac{y_{j+1} - y_j}{x_{j+1} - x_j} (x-x_j)\f]
   * 
   * 
   * @image html linear_interpolation.png
   * 
   * \pre x vector must be sorted.
   * \note Interpolation is only defined for interval defined by the first and the last argument given. The interpolation objects do not extrapolate values outside the interval.
   */

  class LinearInterpolation: public Interpolation {
  public:
    LinearInterpolation(){};
    virtual double operator()(const std::vector<double>&,const std::vector<double>&,const double&) const;
    virtual LinearInterpolation* clone() const;
    virtual std::string info() const;
    virtual unsigned int getMinSize() const;
    virtual ~LinearInterpolation(){};
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
