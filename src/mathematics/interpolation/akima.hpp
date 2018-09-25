#ifndef JULIAN_AKIMA_HPP
#define JULIAN_AKIMA_HPP

#include <mathematics/interpolation/interpolation.hpp>
#include <gsl/gsl_spline.h>
  
namespace julian {

  /**
   * @file   akima.hpp
   * @brief  File contains implementation of AKIMA interpolant.
   */
  
  /** \ingroup interpolation
   *  \brief Class implements the AKIMA interpolation technique
   *  
   * Akima interpolation is similar to cubic spline interpolation. The difference is that 
   * the discrete derivatives (slopes) are modified to produce a positivity-preserving interpolant.
   *
   * @image html akima_interpolation.png
   *
   * For detailed description see \cite akima \cite duffy4 \cite OGinterpolation
   *
   *  \pre More than 4 points needed.
   *  \remarks Class uses AKIMA algorithm implemented in GSL
   */

  class AKIMA: public Interpolation {
  public:
    AKIMA(){};
    virtual double operator()(const std::vector<double>&,const std::vector<double>&,const double&) const;
    virtual AKIMA* clone() const;
    virtual ~AKIMA(){};
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
