#ifndef JULIAN_NATURALCUBICSPLINE_HPP
#define JULIAN_NATURALCUBICSPLINE_HPP

#include <mathematics/interpolation/interpolation.hpp>

namespace julian {
	
	  /**
   * @file   naturalCubicSpline.hpp
   * @brief  File contains implementation of natural cubic spline.
   */
	
  /** \ingroup interpolation
   * \brief Class implements the natural cubic spline interpolation.
   *
   * A natural cubic spline is a non-local method of interpolation. The interpolant is a piecewise function build from cubic polynomial defined on each interval \f$(x_{i-1},x_{i})\f$ for \f$i = 0,1,..,n\f$: 
   * \f[f_{i}(x) = a_{i} x^{3} + b_{i} x^{2} + c_{i} x + d_{i} for x \in (x_{i-1}, x_{i})\f]
   *
   * For a given tabulated points \f$(x_{i},y_{i})\f$ where \f$i = 0,1,..,n\f$ cubic functions \f$f_{j}\f$ where \f$j = 1,..,n\f$ satisfies the conditions:
   * * \f$ f_{i}(x_{i-1}) = y_{i-1}\f$ for \f$ i = 1,..,n \f$
   * * \f$ f_{i}(x_{i}) = y_{i}\f$ for \f$ i = 1,..,n \f$
   * * \f$ \frac{df_{i}(x)}{dx}|_{x=x_{i}} = \frac{df_{i+1}(x)}{dx}|_{x=x_{i}}\f$ for \f$ i = 1,..,n-1 \f$
   * * \f$ \frac{d^{2}f_{i}(x)}{dx^{2}}|_{x=x_{i}} = \frac{d^{2}f_{i+1}(x)}{dx^{2}}|_{x=x_{i}}\f$ for \f$ i = 1,..,n-1 \f$
   * * \f$ \frac{d^{2}f_{1}(x)}{dx^{2}}|_{x=x_{0}} = 0 \f$
   * * \f$ \frac{d^{2}f_{n}(x)}{dx^{2}}|_{x=x_{n}} = 0 \f$
   *
   * @image html cubicSpline_interpolation.png
   *
   * For more details see \cite OGinterpolation.
   */
  
  class NaturalCubicSpline: public Interpolation {
  public:
    NaturalCubicSpline(){};
    virtual double operator()(const std::vector<double>&,const std::vector<double>&,const double&) const;
    virtual NaturalCubicSpline* clone() const;
    virtual unsigned int getMinSize() const;
    virtual ~NaturalCubicSpline(){};
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
}

#endif
