#ifndef JULIAN_STEFFENINTERPOLATION_HPP
#define JULIAN_STEFFENINTERPOLATION_HPP

#include <mathematics/interpolation/interpolation.hpp>

namespace julian {
  /**
   * @file   steffenInterpolation.hpp
   * @brief  File contains class implementing Steffen interpolation.
   */
  
  /** \ingroup interpolation
   * \brief Class implements the Steffen interpolation.
   *  
   * Steffen’s method guarantees the monotonicity of the interpolating function between the given data points. 
   * Therefore, minima and maxima can only occur exactly at the data points, and there can never be spurious oscillations between data points. 
   * The interpolated function is piecewise cubic in each interval. The resulting curve and its first derivative are guaranteed to be continuous, but the second derivative may be discontinuous.
   * 
   *
   * @image html steffen_interpolation.png 
   * 
   * For detailed description see \cite steffen 
   * \remarks Class uses Steffen interpolation algorithm implemented in GSL
   */
  
  
  class SteffenInterpolation: public Interpolation {
  public:
    SteffenInterpolation(){};
    virtual double operator()(const std::vector<double>&,const std::vector<double>&,const double&) const;
    virtual SteffenInterpolation* clone() const;
    virtual std::string info() const;
    virtual unsigned int getMinSize() const;
    virtual ~SteffenInterpolation(){};
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


