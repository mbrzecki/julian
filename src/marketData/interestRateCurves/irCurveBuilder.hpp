#ifndef JULIAN_SWAPCURVEBUILDER_HPP
#define JULIAN_SWAPCURVEBUILDER_HPP

#include <marketData/interestRateCurves/flatCurve.hpp>
#include <marketData/interestRateCurves/interpolatedCurve.hpp>
#include <marketData/interestRateCurves/curveBuildingBlock.hpp>
#include <marketData/interestRateCurves/estimators/irCurveEstimator.hpp>
#include <instruments/_all_instruments.hpp>
#include <string>
#include <utils/smartPointer.hpp>



namespace julian {
namespace ir {

  /**
   * @file   irCurveBuilder.hpp
   * @brief  File contains interest rate curve builder.
   */
  
  /** \ingroup irCurve
   * \brief Class implements Builder design pattern that can be used to create interest rate curves
   *
   * Class provides simple and clear interface for constructing the interest rate curve. The class contains the methods through which the parameters of curve are established. 
   * If some parameters are not given builder sets following default setting:
   * * interpolator - linear interpolation of zero-coupon rates
   * * extrapolator - extrapolating zero-coupon rate
   * * rate - simple compounding ACT365
   *
   * The curve can be constructed by:
   * * providing the benchmark instruments and interest rate curve estimator 
   * * providing the dates (or tenors) and DFs/ZCRs/Fwds.
   *
   */
  
    class BuildCurve {
    public:
      BuildCurve();
  
      BuildCurve& asOfDate(const Date&);
      BuildCurve& withCalendar(const Calendar&);  
      BuildCurve& withDates(const std::vector<Date>&);
      BuildCurve& withTenors(const std::vector<Tenor>&);
      BuildCurve& withTenors(const std::vector<std::string>&);
  
      BuildCurve& withDiscountFactors(const std::vector<double>&);
      BuildCurve& withZeroCouponRate(const double);
      BuildCurve& withZeroCouponRates(const std::vector<double>&);
      BuildCurve& withForwardRates(const std::vector<double>&);
      BuildCurve& withSetOfInstruments(const std::vector<SmartPointer<BuildingBlock> >&);
  
      BuildCurve& usingDiscountingCurve(const SmartPointer<ir::Curve>&);
      BuildCurve& usingProjectionCurve(const SmartPointer<ir::Curve>&);

      BuildCurve& withInterestRate(const InterestRate&);
      BuildCurve& withInterpolator(const SmartPointer<Interpolator>&);
      BuildCurve& withExtrapolator(const SmartPointer<Extrapolator>&);
      BuildCurve& usingEstimator(const SmartPointer<Estimator>&);
  
      BuildCurve& withFxSpot(const double&);
  
      operator InterpolatedCurve();
      operator FlatCurve();
      
    private:
	/** \brief Auxiliary type used to identify what data are used to create curve 
	*/
      enum class InputType {NONE, DF, ZCR, FWD, INSTRUMENTS};
      
      std::vector<Date> dates_; /*!< @brief dates that can be used as grid dates of interpolated interest rate curve*/ 
      std::vector<Tenor> tenors_; /*!< @brief tenors that can be used to calculate grid dates*/ 
      std::vector<double> double_holder_; /*!< @brief vector holding the doubles which may represent DFs, ZCRs or Fwds */ 
      double zero_coupon_rate_; /*!< @brief zero coupon rate required by flat curve*/ 
      std::vector<SmartPointer<BuildingBlock> > instruments_; /*!< @brief benchmark instrument that are used to estimate curve*/ 
    
      InterestRate rate_; /*!< @brief convention of interest rate compounding*/ 
      SmartPointer<Interpolator> interpolator_; /*!< @brief interpolator used by interpolated rate curve*/ 
      SmartPointer<Extrapolator> extrapolator_; /*!< @brief extrapolator used by interpolated rate curve*/ 
      SmartPointer<Estimator> estimator_; /*!< @brief estimator used to estimate curve basing on the instruments*/ 
  
      Calendar calendar_; /*!< @brief calendar used by interest rate curve*/ 
      
      SmartPointer<ir::Curve> discounting_curve_;/*!< @brief discounting curve used in multiple curve framework*/ 
      SmartPointer<ir::Curve> projection_curve_;/*!< @brief projection curve used in multiple curve framework*/ 
  
      Date today_;/*!< @brief date of interest rate curve*/ 
      double fx_spot_;/*!< @brief fx spot used by when constructing cross currency curve */ 

      InputType method_of_construction_;/*!< @brief contains information what method was used to construct curve */ 
      // bool discounting_curve_given;/*!< @brief true if discounting curve was provided*/ 
      // bool projection_curve_given;/*!< @brief true if projection curve provided*/ 
    };
}  // namespace ir
}  // namespace julian
#endif
