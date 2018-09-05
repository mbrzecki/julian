#ifndef JULIAN_POLYNOMIALINTERPOLATION_HPP
#define JULIAN_POLYNOMIALINTERPOLATION_HPP

#include <mathematics/interpolation/interpolation.hpp>

namespace julian {
  /**
   * @file   polynomialInterpolation.hpp
   * @brief  File contains class implementing polynomial interpolation.
   */
  
  /** \ingroup interpolation
   * \brief Class implements the polynomial interpolation.
   *  
   * Polynomial interpolation is the interpolation of a given data set by the polynomial of lowest possible degree that passes through the points of the dataset
   * 
   * @image html poly_interpolation.png
   *
   * \remarks Class uses polynomial interpolation algorithm implemented in GSL
   */
  
  
  class PolynomialInterpolation: public Interpolation {
  public:
    PolynomialInterpolation(){};
    virtual double operator()(const std::vector<double>&,const std::vector<double>&,const double&) const;
    virtual PolynomialInterpolation* clone() const;
    virtual std::string info() const;
    virtual unsigned int getMinSize() const;
    virtual ~PolynomialInterpolation(){};
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

#endif /* POLYNOMIALINTERPOLATION_HPP */
