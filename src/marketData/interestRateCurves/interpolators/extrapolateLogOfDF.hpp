#ifndef JULIAN_EXTRAPOLATELOGOFDF_HPP
#define JULIAN_EXTRAPOLATELOGOFDF_HPP

#include <marketData/interestRateCurves/interpolators/irCurveExtrapolator.hpp>

namespace julian {
namespace ir {
  /**
   * @file   extrapolateLogOfDF.hpp
   * @brief  File contains definition of extrapolate of interest rate curve.
   */
  
  /** \ingroup ir_interpolators
   * \brief Class extrapolates the interest rate curve. 
   *
   * This class is used to extrapolate interpolated interest rate curve. This is done according to formula:
   * \f[DF(date_x) = DF^{\frac{YF(today,date_x)}{YF(today,date)}}\f]
   * where:
   * \f$date_x\f$ is date on which we extrapolate
   * \f$date\f$ the latest interest rate curve grid date in case when we \f$date_x\f$ is later then last grid date 
   * or the earliest interest rate curve grid date in case when we \f$date_x\f$ is earlier then first grid date
   */

    class ExtrapolateLogOfDF: public Extrapolator {
    public:
      ExtrapolateLogOfDF();
      virtual double operator()(const Calendar&, const InterestRate&, const Date& , const std::vector<Date>&,const std::vector<double>&,const Date&) const;
      virtual ExtrapolateLogOfDF* clone() const;
      ~ExtrapolateLogOfDF(){};
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
