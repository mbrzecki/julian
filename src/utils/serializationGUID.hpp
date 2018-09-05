#ifndef JULIAN_SERIALIZATIONGUID_HPP
#define JULIAN_SERIALIZATIONGUID_HPP

  /**
   * @file   serializationGUID.hpp
   * @brief  Definitions of GUID needed to serialize objects.
   */

#include <interestRates/_all_interestRate.hpp>
#include <instruments/_all_instruments.hpp>

BOOST_CLASS_EXPORT(julian::YearFraction)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(julian::YearFraction)
BOOST_CLASS_EXPORT_GUID(julian::ACT360, "ACT360")
BOOST_CLASS_EXPORT_GUID(julian::ACT360addOne, "ACT360addOne")
BOOST_CLASS_EXPORT_GUID(julian::ACT365, "ACT365")
BOOST_CLASS_EXPORT_GUID(julian::ActActAFB, "ActActAFB")
BOOST_CLASS_EXPORT_GUID(julian::ActActISDA, "ActActISDA")
BOOST_CLASS_EXPORT_GUID(julian::E30360, "E30360")
BOOST_CLASS_EXPORT_GUID(julian::OneYF, "OneYF")
BOOST_CLASS_EXPORT_GUID(julian::US30360, "US30360")

BOOST_CLASS_EXPORT(julian::Holiday)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(julian::Holiday)
BOOST_CLASS_EXPORT_GUID(julian::PLNHoliday, "PLNHoliday")
BOOST_CLASS_EXPORT_GUID(julian::CHFHoliday, "CHFHoliday")
BOOST_CLASS_EXPORT_GUID(julian::CZKHoliday, "CZKHoliday")
BOOST_CLASS_EXPORT_GUID(julian::EURHoliday, "EURHoliday")
BOOST_CLASS_EXPORT_GUID(julian::USDHoliday, "USDHoliday")
BOOST_CLASS_EXPORT_GUID(julian::GBPHoliday, "GBPHoliday")
BOOST_CLASS_EXPORT_GUID(julian::HUFHoliday, "HUFHoliday")
BOOST_CLASS_EXPORT_GUID(julian::JPYHoliday, "JPYHoliday")
BOOST_CLASS_EXPORT_GUID(julian::CADHoliday, "CADHoliday")
BOOST_CLASS_EXPORT_GUID(julian::EasterMonday, "EasterMonday")
BOOST_CLASS_EXPORT_GUID(julian::CorpusChristi, "CorpusChristi")
BOOST_CLASS_EXPORT_GUID(julian::GoodFriday, "GoodFriday")
BOOST_CLASS_EXPORT_GUID(julian::WhitMonday, "WhitMonday")
BOOST_CLASS_EXPORT_GUID(julian::FixedHoliday, "FixedHoliday")

BOOST_CLASS_EXPORT(julian::SettlementDateConvention)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(julian::SettlementDateConvention)
BOOST_CLASS_EXPORT_GUID(julian::SettlementFromSpot, "SettlementFromSpot")
BOOST_CLASS_EXPORT_GUID(julian::SettlementFromExpiry, "SettlementFromExpiry")

BOOST_CLASS_EXPORT(julian::Compounding)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(julian::Compounding)
BOOST_CLASS_EXPORT_GUID(julian::SimpleRate, "SimpleRate")
BOOST_CLASS_EXPORT_GUID(julian::CompoundedRate, "CompoundedRate")
BOOST_CLASS_EXPORT_GUID(julian::ExponentialRate, "ExponentialRate")
BOOST_CLASS_EXPORT_GUID(julian::FractionRate, "FractionRate")

BOOST_CLASS_EXPORT(julian::CashFlow)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(julian::CashFlow)
BOOST_CLASS_EXPORT_GUID(julian::FixedCashFlow, "FixedCashFlow")
BOOST_CLASS_EXPORT_GUID(julian::FloatingCashFlow, "FloatingCashFlow")

BOOST_CLASS_EXPORT(julian::Interpolation)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(julian::Interpolation)
BOOST_CLASS_EXPORT_GUID(julian::AKIMA, "AKIMA")
BOOST_CLASS_EXPORT_GUID(julian::CubicInterpolation, "CubicInterpolation")
BOOST_CLASS_EXPORT_GUID(julian::FlatBackward, "FlatBackward")
BOOST_CLASS_EXPORT_GUID(julian::FlatForward, "FlatForward")
BOOST_CLASS_EXPORT_GUID(julian::LinearInterpolation, "LinearInterpolation")
BOOST_CLASS_EXPORT_GUID(julian::LogarithmicInterpolation, "LogarithmicInterpolation")
BOOST_CLASS_EXPORT_GUID(julian::NaturalCubicSpline, "NaturalCubicSpline")
BOOST_CLASS_EXPORT_GUID(julian::QuadraticInterpolation, "QuadraticInterpolation")
BOOST_CLASS_EXPORT_GUID(julian::SteffenInterpolation, "SteffenInterpolation")

BOOST_CLASS_EXPORT(julian::ir::InterpolationInput)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(julian::ir::InterpolationInput)
BOOST_CLASS_EXPORT_GUID(julian::ir::InterpolateInverseDF, "InterpolateInverseDF")
BOOST_CLASS_EXPORT_GUID(julian::ir::InterpolateLogarithmOfDF, "InterpolateLogarithmOfDF")
BOOST_CLASS_EXPORT_GUID(julian::ir::InterpolateZCRate, "InterpolateZCRate")
BOOST_CLASS_EXPORT_GUID(julian::ir::InterpolateDF, "InterpolateDF")

BOOST_CLASS_EXPORT(julian::ir::Extrapolator)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(julian::ir::Extrapolator)
BOOST_CLASS_EXPORT_GUID(julian::ir::ExtrapolateFlatZCR, "ExtrapolateFlatZCR")
BOOST_CLASS_EXPORT_GUID(julian::ir::ExtrapolateLogOfDF, "ExtrapolateLogOfDF")

BOOST_CLASS_EXPORT(julian::Option)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(julian::Option)
BOOST_CLASS_EXPORT_GUID(julian::EuropeanOpt, "EuropeanOpt")

BOOST_CLASS_EXPORT(julian::ir::Interpolator)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(julian::ir::Interpolator)
BOOST_CLASS_EXPORT_GUID(julian::ir::CompoundedInterpolator, "CompoundedInterpolator")

BOOST_CLASS_EXPORT(julian::ir::Curve)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(julian::ir::Curve)
BOOST_CLASS_EXPORT_GUID(julian::ir::FlatCurve, "FlatCurve")
BOOST_CLASS_EXPORT_GUID(julian::ir::InterpolatedCurve, "InterpolatedCurve")


#endif 
