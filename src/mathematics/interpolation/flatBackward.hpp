#ifndef JULIAN_FLATBACKWARD_HPP
#define JULIAN_FLATBACKWARD_HPP

#include <mathematics/interpolation/interpolation.hpp>

namespace julian {
  /**
   * @file   flatBackward.hpp
   * @brief  File contains class of flat backward interpolant.
   */
  
  /** \ingroup interpolation
   * \brief  Class implements the flat backward interpolation technique
   *  
   * Flat interpolation returns the value of the left node. For \f$(x,y)\f$ lying between \f$(x_j,y_j)\f$ and \f$(x_{j+1},y_{j+1})\f$ the formula for flat interpolation is:
   * \f[ y =  y_j\f] 
   * 
   * @image html flatbwd_interpolation.png
   * 
   * \pre x vector must be sorted.
   * \note Interpolation is only defined for interval defined by the first and the last argument given. The interpolation objects do not extrapolate values outside the interval.

   */

  class FlatBackward: public Interpolation {
  public:
    FlatBackward(){};
    virtual double operator()(const std::vector<double>&,const std::vector<double>&,const double&) const;
    virtual FlatBackward* clone() const;
    virtual std::string info() const;
    virtual unsigned int getMinSize() const;
    virtual ~FlatBackward(){};
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
