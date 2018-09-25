#ifndef JULIAN_INTERPOLATEZCRATE_HPP
#define JULIAN_INTERPOLATEZCRATE_HPP

#include <marketData/interestRateCurves/interpolators/interpolationInput.hpp>
#include <interestRates/interestRate.hpp>

namespace julian {
namespace ir {

  /**
   * @file   interpolateZCRate.hpp
   * @brief  File contains definition of interpolate zero-coupon rate class.
   */
  
  /** \ingroup interpolators
   * \brief The class encapsulates the concept of interpolating zero-coupon rates.
   *
   * Class encapsulates the idea of interpolating zero-coupon rates. It is a part of \a strategy \a design \a pattern implemented in interpolator.
   */

  class InterpolateZCRate: public InterpolationInput {
  public:
    /** \brief Constructor.
    */
    InterpolateZCRate(){};
    virtual double operator()(double,double,InterestRate,Date,Date,Date) const;
    virtual double getDF(double,InterestRate,Date,Date) const;
    virtual InterpolateZCRate* clone() const;

    /**\brief Destructor
     */
    virtual ~InterpolateZCRate(){};
    virtual std::string info() const;
    friend class boost::serialization::access;
  private:
    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int);
  };
  /** \brief interface used by Boost serialization library
   */
  template<class Archive>
  void InterpolateZCRate::serialize(Archive & , const unsigned int) {
    boost::serialization::base_object<InterpolationInput>(*this);
  }
}  // namespace ir
}  // namespace julian

#endif
