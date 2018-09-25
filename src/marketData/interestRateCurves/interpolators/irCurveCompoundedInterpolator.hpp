#ifndef JULIAN_COMPOUNDEDIRINTERPOLATOR_HPP
#define JULIAN_COMPOUNDEDIRINTERPOLATOR_HPP

#include <vector>
#include <mathematics/interpolation/interpolation.hpp>
#include <marketData/interestRateCurves/interpolators/interpolationInput.hpp>
#include <marketData/interestRateCurves/interpolators/irCurveInterpolator.hpp>
#include <interestRates/interestRate.hpp>
#include <iostream>
#include <utils/smartPointer.hpp>


namespace julian {
namespace ir {
  /**
   * @file   irCurveCompoundedInterpolator.hpp
   * @brief  File contains implementation of CompoundedInterpolator.
   */
  /** \ingroup ir_interpolators
   * \brief Definition of compounded interpolator
   *
   * The ir::CompoundedInterpolator implements the Strategy design pattern. It allows a flexible construction of interpolating algorithms. 
   * We can chose inputs of interpolation and method of interpolation.    
   */

  class CompoundedInterpolator: public Interpolator   {
  public:
  /** \brief Default constructor
  */
    CompoundedInterpolator(){};
	/** \brief Constructor
	  */
    CompoundedInterpolator(SmartPointer<Interpolation> interpolation, SmartPointer<InterpolationInput> inputs):
      interpolation_(interpolation), inputs_(inputs) {};

    virtual double operator()(const Calendar&,const InterestRate&, const Date& ,const std::vector<Date>&,const std::vector<double>&,const Date&) const;
    virtual CompoundedInterpolator* clone() const;
    virtual ~CompoundedInterpolator(){};
    virtual std::string info() const;

    friend class boost::serialization::access;
  private:
    template<class Archive>
    void serialize(Archive & ar, const unsigned int);
      
    SmartPointer<Interpolation> interpolation_; /*!< \brief interpolation interface*/
    SmartPointer<InterpolationInput> inputs_; /*!< \brief interface of method transforming the DFs*/
  };
  /** \brief interface used by Boost serialization library
   */
  template<class Archive>
  void CompoundedInterpolator::serialize(Archive & ar, const unsigned int) {
    boost::serialization::base_object<Interpolator>(*this);
    ar & BOOST_SERIALIZATION_NVP(interpolation_);
    ar & BOOST_SERIALIZATION_NVP(inputs_);
  }

  /** \ingroup ir_interpolators
   * \brief Simple class constructing the interpolator  
   */
  template<class INTERPOLATOR, class INPUTS>
  CompoundedInterpolator makeCompoundedInterpolator() {
    INTERPOLATOR inter;
    INPUTS input;
    return CompoundedInterpolator(inter,input);
  }
}  //namespace ir
} //namespace julian
#endif
