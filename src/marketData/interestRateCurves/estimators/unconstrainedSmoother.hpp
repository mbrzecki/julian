#ifndef JULIAN_UNCONSTRAINEDSMOOTHER_HPP
#define JULIAN_UNCONSTRAINEDSMOOTHER_HPP

#include <marketData/interestRateCurves/interpolatedCurve.hpp>
#include <marketData/interestRateCurves/curveBuildingBlock.hpp>
#include <marketData/interestRateCurves/curveSettings.hpp>
#include <marketData/interestRateCurves/estimators/costFunctions/SmootherCostFunction.hpp>
#include <marketData/InterestRateCurves/estimators/irCurveEstimator.hpp>
#include <gsl/gsl_multifit_nlin.h>

namespace julian {
namespace ir {

/**
* @file   unconstrainedSmoother.hpp
* @brief  Implementation of UnconstrainedSmoother.
*/
  /**
   *  \ingroup irCurveEstimator
   * \todocument Methods and fields
   */

  class UnconstrainedSmoother: public Estimator {
  public:
    UnconstrainedSmoother(SmartPointer<SmootherCostFunction> cost_function, double lambda):
      cost_function_(cost_function), lambda_(lambda) {};

    virtual void calculate(const std::vector<SmartPointer<BuildingBlock> >& instruments,
			   const CurveSettings& settings,
			   SmartPointer<Curve>& discounting_curve,
			   SmartPointer<Curve>& projection_curve);
    
    virtual std::vector<double> getDF() const;
    virtual std::vector<Date> getDates() const;
    virtual UnconstrainedSmoother* clone() const;
    virtual ~UnconstrainedSmoother(){};

    std::string info() const;

  private:           
    std::vector<double> DFs_; /*!< @brief Vector holding the Discount Factors being result of estimation*/
    std::vector<Date> dates_; /*!< @brief Grid dates of resulting curve*/
    SmartPointer<SmootherCostFunction> cost_function_; /*!< @brief Cost Function */ 
    double lambda_;

  };
}  // namespace ir
}  // namespace julian

#endif





