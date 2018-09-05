#ifndef JULIAN_FLATFORWARD_HPP
#define JULIAN_FLATFORWARD_HPP

#include <mathematics/interpolation/interpolation.hpp>

namespace julian {
  /**
   * @file   flatForward.hpp
   * @brief  File contains class of flat forward interpolant.
   */
  
  /** \ingroup interpolation
   * \brief  Class implements the flat forward interpolation technique
   *  
   * Flat interpolation returns the value of the right node. For \f$(x,y)\f$ lying between \f$(x_j,y_j)\f$ and \f$(x_{j+1},y_{j+1})\f$ the formula for flat forward interpolation is:
   * \f[ y =  y_{j+1}\f] 
   * 
   * @image html flatfwd_interpolation.png
   * 
   * \pre x vector must be sorted.
   * \note Interpolation is only defined for interval defined by the first and the last argument given. The interpolation objects do not extrapolate values outside the interval.
   */

  class FlatForward: public Interpolation {
  public:
    FlatForward(){};
    virtual double operator()(const std::vector<double>&,const std::vector<double>&,const double&) const;
    virtual FlatForward* clone() const;
    virtual std::string info() const;
    virtual unsigned int getMinSize() const;
    virtual ~FlatForward(){};
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
