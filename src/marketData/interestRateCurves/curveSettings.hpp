#ifndef JULIAN_CURVESETTINGS_HPP
#define JULIAN_CURVESETTINGS_HPP

#include <utils/smartPointer.hpp>
#include <dates/date.hpp>
#include <dates/calendars/calendar.hpp>
#include <interestRates/interestRate.hpp>
#include <marketData/interestRateCurves/interpolators/irCurveInterpolator.hpp>
#include <marketData/interestRateCurves/interpolators/irCurveExtrapolator.hpp>


namespace julian {
namespace ir {

    /**
     * @file   curveSettings.hpp
     * @brief  File contains definition of structure holding settings of ir::InterpolatedCurve.
     */
    
    /** \ingroup irCurve
     *
     *  \brief Structure holding settings of ir::InterpolatedCurve.
     *
     * Structure was defined to make passing curve settings easier.
     */ 
    struct CurveSettings {
      Date today_;  /*!< \brief The date of a curve*/
      InterestRate rate_;  /*!< \brief Interest rate convention*/
      SmartPointer<Interpolator> interpolator_;  /*!< \brief Interpolator of a curve*/
      SmartPointer<Extrapolator> extrapolator_;  /*!< \brief Extrapolator of a curve*/
      Calendar calendar_; /*!< \brief Calendar used by a curve*/
      double fx_spot_; /*!< \brief Fx spot value*/
    };
    
}  // namespace ir
}  // namespace julian


#endif
