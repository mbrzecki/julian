#include <juliant.hpp>

using namespace julian;

namespace {
  ObjectFactoryHelper< Interpolation, LinearInterpolation>    registerInterpolation1("linear");
  ObjectFactoryHelper< Interpolation, QuadraticInterpolation> registerInterpolation2("quadratic");
  ObjectFactoryHelper< Interpolation, CubicInterpolation>     registerInterpolation3("cubic");
  ObjectFactoryHelper< Interpolation, NaturalCubicSpline>     registerInterpolation4("cubic_spline");
  ObjectFactoryHelper< Interpolation, AKIMA>                  registerInterpolation5("AKIMA");
  ObjectFactoryHelper< Interpolation, SteffenInterpolation>   registerInterpolation6("Steffen");
  ObjectFactoryHelper< Interpolation, FlatBackward>           registerInterpolation7("flat");
  
  ObjectFactoryHelper< ir::InterpolationInput, ir::InterpolateDF>            registerInputs1("DF");
  ObjectFactoryHelper< ir::InterpolationInput, ir::InterpolateInverseDF>     registerInputs2("invDF");
  ObjectFactoryHelper< ir::InterpolationInput, ir::InterpolateLogarithmOfDF> registerInputs3("logDF");
  ObjectFactoryHelper< ir::InterpolationInput, ir::InterpolateZCRate>        registerInputs4("ZCR");
  
  ObjectFactoryHelper< YearFraction, ACT360>     registerYf1("ACT360");
  ObjectFactoryHelper< YearFraction, ACT365>     registerYf2("ACT365");
  ObjectFactoryHelper< YearFraction, E30360>     registerYf3("E30360");
  ObjectFactoryHelper< YearFraction, US30360>    registerYf4("US30360");
  ObjectFactoryHelper< YearFraction, ActActISDA> registerYf5("ActActISDA");
  ObjectFactoryHelper< YearFraction, ActActAFB>  registerYf6("ActActAFB");

  ObjectFactoryHelper< Compounding, SimpleRate>      registerComp1("simple");
  ObjectFactoryHelper< Compounding, CompoundedRate>  registerComp2("compounded");
  ObjectFactoryHelper< Compounding, ExponentialRate> registerComp3("exponential");

  ObjectFactoryHelper< ir::SmootherCostFunction, ir::SmoothForwardRates>    registerSmooth1("forward");
  ObjectFactoryHelper< ir::SmootherCostFunction, ir::SmoothZeroCouponRates> registerSmooth2("zerocoupon");
    
  ValueFactoryHelper<Frequency> registerFreq1("annually", ANNUALLY);
  ValueFactoryHelper<Frequency> registerFreq2("semiannually", SEMIANNUALLY);
  ValueFactoryHelper<Frequency> registerFreq3("quarterly", QUARTERLY);
  ValueFactoryHelper<Frequency> registerFreq4("monthly", MONTHLY);

  ValueFactoryHelper<CallPut> registerType1("call", CallPut::CALL);
  ValueFactoryHelper<CallPut> registerType2("put", CallPut::PUT);
}  // namespace
