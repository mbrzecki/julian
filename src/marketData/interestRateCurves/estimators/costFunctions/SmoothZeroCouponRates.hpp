#ifndef JULIAN_SMOOTHZEROCOUPONRATES_HPP
#define JULIAN_SMOOTHZEROCOUPONRATES_HPP

#include <marketData/interestRateCurves/interpolatedCurve.hpp>
#include <marketData/interestRateCurves/estimators/costFunctions/SmootherCostFunction.hpp>
#include <armadillo>

namespace julian {
namespace ir {
  /**
   * @file   SmoothZeroCouponRates.hpp
   * @brief  File contains implementation of component of  SmootherCostFunction decorator
   */
  /** \ingroup irCurveCost
   * \brief Class implements concrete component of SmootherCostFunction
   *  
   * SmootherCostFunction implements cost function used by optimization algorithm in swap curve bootstrapping. 
   * The mathematical form of cost function is defined in classes that inherits from CostFunctionDecorator.
   * Choosing appropriate decorators, we can minimize for example the length of the swap curve etc. 
   *
   * This class specifies what we actually mean by swap curve. Swap curve can be defined by set of discount factors, zero-coupon rates, forwards rates etc.
   * Choosing this class as base class for CostFunction decorator, we will optimize the zero coupon rates.
   *
   * SmoothZeroouponRates is a concrete component in decorator structure. 
   * Concrete Component is a class that contains basic behaviour that can be altered by decorators.
   */
  
  class SmoothZeroCouponRates: public SmootherCostFunction {
  public:
    SmoothZeroCouponRates(){};
      
    virtual arma::mat giveQmatrix(const InterpolatedCurve&) const;
    virtual arma::mat giveCvector(const InterpolatedCurve&) const;
    virtual double calculateCost(const InterpolatedCurve&) const;
    virtual std::vector<double> giveSmoothedCurve(const InterpolatedCurve&) const;
    virtual void updateSmoothedCurve(InterpolatedCurve& c, const std::vector<double>& r) const;
      
    virtual SmoothZeroCouponRates* clone() const;
    virtual ~SmoothZeroCouponRates(){};
      
  private:
  };
} //  namespace ir
}  // namespace julian
#endif
