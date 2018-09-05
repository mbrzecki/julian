#ifndef JULIAN_INTERPOLATELOGOFDF_HPP
#define JULIAN_INTERPOLATELOGOFDF_HPP

#include <marketData/interestRateCurves/interpolators/interpolationInput.hpp>

namespace julian {
namespace ir {

    /**
     * @file   interpolateLogOfDF.hpp
     * @brief  File contains definition of interpolate of log DF class.
     */


    /** \ingroup interpolators
     * \brief The class encapsulates the concept of interpolating logarithm of discount factors.
     *  
     * Class encapsulates the idea of interpolating discount factors. It is a part of \a strategy \a design \a pattern implemented in swap curve interpolator.
     */


  class InterpolateLogarithmOfDF: public InterpolationInput {
  public:
    /**
       \brief Constructor.
     
       Constructor.
    */
    InterpolateLogarithmOfDF(){};

    virtual double operator()(double,double,InterestRate,Date,Date,Date) const;
    virtual double getDF(double,InterestRate,Date,Date) const;
    virtual InterpolateLogarithmOfDF* clone() const;

    /**\brief Destructor
     
       Destructor.
    */
    virtual ~InterpolateLogarithmOfDF(){};
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
