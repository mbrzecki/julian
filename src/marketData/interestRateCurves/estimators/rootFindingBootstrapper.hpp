#ifndef JULIAN_ROOTFINDINGBOOTSTRAPPER_HPP
#define JULIAN_ROOTFINDINGBOOTSTRAPPER_HPP

#include <marketData/interestRateCurves/estimators/irCurveEstimator.hpp>
#include <marketData/interestRateCurves/interpolatedCurve.hpp>
#include <mathematics/numericalAlgorithms/derivativeRootFinder.hpp>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>

namespace julian {
namespace ir {
  /**
   * @file   rootFindingBootstrapper.hpp
   * @brief  File contains definition of RootFindingBootstrapper.
   */
  
  /** \ingroup irCurveEstimator
   * \brief Interest rate curve estimating algorithm  using the derivative root finder.
   *
   * Class implements the algorithm estimating interest rate curves using the derivative root finder (compare DerivativeRootFinder).
   * The curve is estimated as follows:
   *
   * 1) Setting first grid point: today dates and DF1 = 1. Reading the first (with shortest maturity) instrument (\f$isntr_1\f$) and getting its maturity date \f$date_1\f$. 
   *
   * 2) Creating new curve \f$C\f$ with dates \f$= [today, date_1 ] \f$ and discount factors \f$= [1.0, DF1 ] \f$
   *
   * 3) Solving function f1 using root finding algorithm: \f$f1(DF1) = isntr_{1}.price(C)\f$.
   *
   * 4) Reading the next instrument (\f$isntr_2\f$) with maturity \f$date_2\f$. Creating new curve \f$C\f$ with dates \f$= [date_1, date_2 ] \f$ and discount factors \f$= [DF1, DF2]\f$
   *
   * 5) Solving function f2 using root finding algorithm: \f$f2(DF2) = isntr_{2}.price(C)\f$.
   *
   * 6) Reading the next instrument (\f$isntr_3\f$) with maturity \f$date_3\f$. Creating new curve \f$C\f$ with dates \f$= [date_1, date_2, date_3 ] \f$ and discount factors \f$= [DF1, DF2, DF3]\f$
   *
   * 7) Solving function f3 using root finding algorithm: \f$f3(DF3) = isntr_{3}.price(C)\f$.
   *
   * etc.
   * 
   * The derivative of f function is calculated numerically using finite difference approximation. If discounting curve and projection curve are provided, 
   * they are used when instrument is priced. This approach enables estimating the curve in the multi-curve framework (see \cite Fujii).
   *
   *
   * \warning Estimator does not work properly with FlatBackward interpolation. RootFindingBootstrapper estimates curve by varying last DF. In FlatBackward the shape of the curve does not depend on last DF so calibration cannot be performed 
   **/

  class RootFindingBootstrapper: public Estimator {
  public:
    /** \brief constructor
     */
    RootFindingBootstrapper(DerivativeRootFinder method = DerivativeRootFinder::STEFFENSEN): method_(method) {};
    void calculate(const std::vector<SmartPointer<BuildingBlock> >& instruments,
		   const CurveSettings& settings,
		   SmartPointer<ir::Curve>& discounting, SmartPointer<ir::Curve>& projection);
    std::vector<double> getDF() const;
    std::vector<Date> getDates() const;

    std::string info() const;
      
    RootFindingBootstrapper* clone() const;
    ~RootFindingBootstrapper(){};
  private:
    std::vector<double> discount_factors_; /*!< @brief Vector of discount factors*/
    std::vector<Date> dates_; /*!< @brief Vector of grid dates*/
    DerivativeRootFinder method_; /*!< @brief Algorithm type */
  };
}  // namespace ir
}  // namespace julian

#endif
