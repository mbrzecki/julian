#ifndef JULIAN_IRESTIMATOR_HPP
#define JULIAN_IRESTIMATOR_HPP

#include <marketData/interestRateCurves/irCurve.hpp>
#include <marketData/interestRateCurves/curveBuildingBlock.hpp>
#include <marketData/interestRateCurves/curveSettings.hpp>

namespace julian {
namespace ir {

  /**
   * @file   irCurveEstimator.hpp
   * @brief  File contains interface of algorithms that performs interest rate curve estimations.
   */


  /** \ingroup irCurveEstimator
   * \brief Class defines the interface of algorithms that perform estimation of interest rate curve (see InterpolatedCurve)
   *
   * Interest rate estimators calculate dated DFs on the basis of provided benchmark instruments using. Maturities of benchmark instruments are used as grid dates..  
   */

  class Estimator {
  public:
    /** \brief default constructor
     */
    Estimator(){};
    
    /** \brief estimates the curve
     *
     * calculates method estimates the curve and saves the result into the class members
     */
    virtual void calculate(const std::vector<SmartPointer<BuildingBlock> >& instruments, const CurveSettings& settings,
			   SmartPointer<ir::Curve>& discounting_curve, SmartPointer<ir::Curve>& projection_curve) = 0;

    /** \brief returns DFs
     *
     * Method should be called after calling method Estimator::calculate
     */
    virtual std::vector<double> getDF() const = 0;
    
    /** \brief returns dates
     *
     * Method should be called after calling method Estimator::calculate
     */
    virtual std::vector<Date> getDates() const = 0;

    /** \brief returns name of estimator
     *
     */
    virtual std::string info() const = 0;

    /** \brief virtual copy constructor
     *
     */
    virtual Estimator* clone() const = 0;

    /** \brief destructor
     *
     */
    virtual ~Estimator(){};
  };

}  // namespace ir
}  // namespace juliant
#endif
