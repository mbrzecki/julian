#ifndef JULIAN_EXTRAPOLATEFLATZCR_HPP
#define JULIAN_EXTRAPOLATEFLATZCR_HPP

#include <marketData/interestRateCurves/interpolators/irCurveExtrapolator.hpp>

namespace julian {
namespace ir {

  /**
   * @file   extrapolateFlatZCR.hpp
   * @brief  File contains definition of extrapolate of interest rate curve.
   */
  
  /** \ingroup ir_interpolators
   * \brief Class extrapolates the zero coupon rate. 
   *
   * For date earlier than first grid date of interpolated curve the DF is calculated using the ZCR for first grid date.
   * For date later than last grid date of interpolated curve the DF is calculated using the ZCR for last grid date.
   * This results in flat piecewise function before first and after last grid dates. 
   *
   */
    
    class ExtrapolateFlatZCR: public Extrapolator {
    public:
      ExtrapolateFlatZCR();
      virtual double operator()(const Calendar&, const InterestRate&, const Date& , const std::vector<Date>&,const std::vector<double>&,const Date&) const;
      virtual ExtrapolateFlatZCR* clone() const;
      ~ExtrapolateFlatZCR(){};
      virtual std::string info() const;  
      friend class boost::serialization::access;
    private:

      /** \brief interface used by Boost serialization library
       */
      template<class Archive>
      void serialize(Archive & , const unsigned int) {
    	boost::serialization::base_object<Extrapolator>(*this);
      }
    };
}  // namespace ir
}  // namespace julian
#endif
