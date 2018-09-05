#ifndef JULIAN_INTERPOLATEINVERSEDF_HPP
#define JULIAN_INTERPOLATEINVERSEDF_HPP

#include <marketData/interestRateCurves/interpolators/interpolationInput.hpp>

namespace julian {
namespace ir {

    /**
     * @file   interpolateInverseDF.hpp
     * @brief  File contains definition of interpolate inverse DF class.
     */

    /** \ingroup interpolators
     * \brief The class encapsulates the concept of interpolating inverse discount factors.
     *
     * Class encapsulates the idea of interpolating discount factors. It is a part of \a strategy \a design \a pattern implemented in swap curve interpolator.
     */

  class InterpolateInverseDF: public InterpolationInput {
  public:
    /**
       \brief Constructor.
       
       Constructor.
    */
    InterpolateInverseDF(){};
    virtual double operator()(double,double,InterestRate,Date,Date,Date) const;
    virtual double getDF(double,InterestRate,Date,Date) const;
    virtual InterpolateInverseDF* clone() const;

    /**\brief Destructor
       
       Deconstructor.
    */
    virtual ~InterpolateInverseDF(){};
    virtual std::string info() const;
    friend class boost::serialization::access;
  private:
    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int) {
      boost::serialization::base_object<InterpolationInput>(*this);
    }
  };
}  // namespace ir
}  // namespace julian
#endif
