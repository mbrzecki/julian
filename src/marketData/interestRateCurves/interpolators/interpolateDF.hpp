#ifndef JULIAN_INTERPOLATEDF_HPP
#define JULIAN_INTERPOLATEDF_HPP

#include <marketData/interestRateCurves/interpolators/interpolationInput.hpp>
#include <interestRates/interestRate.hpp>

namespace julian {
  namespace ir {

    /**
     * @file   interpolateDF.hpp
     * @brief  File contains definition of interpolate DF class.
     */

    /** \ingroup interpolators
     * \brief The class encapsulates the concept of interpolating discount factors.
     *
     * Class encapsulates the idea of interpolating discount factors. It is a part of \a strategy \a design \a pattern implemented in interpolator.
     *
     */

  class InterpolateDF: public InterpolationInput {
  public:
    /** \brief Constructor.
    */
    InterpolateDF(){};
    
    /**\brief Destructor

       Destructor.
    */
    virtual ~InterpolateDF(){};

    virtual double operator()(double ,double DF2,InterestRate ,Date ,Date ,Date ) const;
    virtual double getDF(double,InterestRate,Date,Date) const;
    virtual InterpolateDF* clone() const;
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
  }
}

#endif
