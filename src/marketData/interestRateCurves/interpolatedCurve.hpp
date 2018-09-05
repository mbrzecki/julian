#ifndef JULIAN_IRINTERPOLATEDCURVE_HPP
#define JULIAN_IRINTERPOLATEDCURVE_HPP

#include <dates/_all_dates.hpp>
#include <vector>
#include <interestRates/interestRate.hpp>
#include <marketData/interestRateCurves/interpolators/irCurveInterpolator.hpp>
#include <marketData/interestRateCurves/interpolators/irCurveExtrapolator.hpp>
#include <marketData/interestRateCurves/curveSettings.hpp>
#include <marketData/interestRateCurves/irCurve.hpp>
#include <iostream>
#include <utils/smartPointer.hpp>
#include <utils/utils.hpp>

namespace julian {
namespace ir {

  /**
   * @file   interpolatedCurve.hpp
   * @brief  File contains definition of swap interpolated curve class.
   */

  /** \ingroup irCurve
   * \brief The object models the interest rate curve.  
   *
   * A interest rate curve is a representation of the relationship of rates in the swap or bond markets and their maturity and is used for the valuations of bonds or swap-related instruments. 
   * It is usually constructed with benchmark instruments and certain related contracts: market instruments that represent the most liquid and dominant instruments for their respective time horizons.
   * More information see \cite tuckman \cite duffy4 \cite LemBrosSwapCurve  \cite hull  and \cite BankOfCanadaSwapCurve.  
   *
   * The InterpolatedCurve is defined by:
   * * set of pairs (dates, discount factor) - these represents the concept of time value of money.
   * * interpolation method - enables to calculate DF for any moment, not just those explicitly given in date grid (see InterestRateCurveInterpolator ).
   *
   * Additionally, the curve class contains InterestRate object encapsulating the year fraction and compounding convention. 
   * The curve is also equipped with calendar and FX rate. Calendar enables to calculate DF, ZCR and Forward Rate on the given tenor. 
   * Fx Rate helps in calculating NPV of fx instruments (like FxForward).
   *
   * It is recommended to build curve by interest rate curve builder ( BuildInterestRateCurve ). 
   * This class implements the builder design pattern and enables to build curve on the basis of adequate instruments or directly given discount factors/ zero coupon rates/ forward rates. 
   * 
   */
  class InterpolatedCurve: public Curve {
  public:
    InterpolatedCurve();
    InterpolatedCurve(Date today,std::vector<Date> dates,std::vector<double> dfs, InterestRate rate_,
		      SmartPointer<Interpolator> interpolator,SmartPointer<Extrapolator> extrapolator,Calendar calendar,double fx_spot);
    InterpolatedCurve(CurveSettings settings, std::vector<Date> dates, std::vector<double> df);
      
    double DF(Date) const override;
    double DF(Date,Date) const override;
    double DF(Tenor) const override;
    double DF(Tenor,Tenor) const override;
      
    double capitalization(Date) const override;
    double capitalization(Tenor) const override;
    double capitalization(Date,Date) const override;
    double capitalization(Tenor,Tenor) const override;   
  
    double coupon(Date) const override;
    double coupon(Tenor) const override;
    double coupon(Date,Date) const override;
    double coupon(Tenor,Tenor) const override; 
  
    double rate(Date) const override;
    double rate(Tenor) const override;
    double rate(Date,InterestRate) const override;
    double rate(Tenor,InterestRate) const override;
  
    double fwdRate(Date,Date) const override;
    double fwdRate(Tenor,Tenor) const override;
    double fwdRate(Date,Tenor) const override;
    double fwdRate(Date,Date,InterestRate) const override;
    double fwdRate(Tenor,Tenor,InterestRate) const override;
    double fwdRate(Date,Tenor,InterestRate) const override;
  
    std::vector<double> getDFs() const;
    std::vector<double> getDFs(std::vector<Date>) const;
    std::vector<double> getRates() const;
    std::vector<double> getRates(InterestRate) const;
    std::vector<double> getFwdRates() const;
    std::vector<double> getFwdRates(InterestRate) const;
    std::vector<Date>   getDates() const;
  
    Calendar getCalendar() const;
    SmartPointer<Interpolator> getInterpolator() const;
    SmartPointer<Extrapolator> getExtrapolator() const;
    InterestRate getInterestRate() const;
    CurveSettings getSettings() const;
    Date getValuationDate() const override;
    Date getSpotDate() const;
    int getSize() const;
    double getFxSpot() const;
      
    void setDates(std::vector<Date>);
    void setDates(Tenor);
    void setDFs(std::vector<double>);
    void setRates(std::vector<double>);
    void setFwdRates(std::vector<double>);
    void setFxSpot(double);

    double calculateYF(Date,Date) const;  
    virtual InterpolatedCurve* clone() const override;
      
    friend std::ostream& operator<<(std::ostream&, InterpolatedCurve&);
    friend class boost::serialization::access;
  private:
    template<class Archive>
    void serialize(Archive & ar, const unsigned int);
    Date today_;                                  /*!< @brief Today represent the date on which the curve is valid.*/
    std::vector<Date> dates_;                     /*!< @brief This vector represents grid dates of the curve. */
    std::vector<double> dfs_;                     /*!< @brief InterpolatedCurve is represented by values of discount factors for each date.*/
    InterestRate rate_;                           /*!< @brief The rate encapsulates the concept interest rate (year fraction and compounding). */
    SmartPointer<Interpolator> interpolator_;     /*!< @brief The interpolator encapsulates the concept of interpolation - getting the DF for dates that are not nodes of the time grid.*/
    SmartPointer<Extrapolator> extrapolator_;     /*!< @brief The extrapolator encapsulates the concept of extrapolating the curve outside the interval defined by last date of time grid.*/
    Calendar calendar_;                           /*!< @brief Thanks to calendar outputs of the curve (DFs, ZCRs, etc) can be calculated only on the basis of provided tenor.*/  
    double fx_spot_;                              /*!< @brief Fx Spots allows to calculate two-currency instruments (Fx Forwards and CIRS).*/ 
  };

  /** \brief interface used by Boost serialization library
   */
  template<class Archive>
  void InterpolatedCurve::serialize(Archive & ar, const unsigned int){
    boost::serialization::base_object<Curve>(*this);
    ar & BOOST_SERIALIZATION_NVP(today_);
    ar & BOOST_SERIALIZATION_NVP(dates_);
    ar & BOOST_SERIALIZATION_NVP(dfs_);
    ar & BOOST_SERIALIZATION_NVP(rate_);
    ar & BOOST_SERIALIZATION_NVP(interpolator_);
    ar & BOOST_SERIALIZATION_NVP(extrapolator_);
    ar & BOOST_SERIALIZATION_NVP(calendar_);
    ar & BOOST_SERIALIZATION_NVP(fx_spot_);
  }
}  // namespace ir
}  // namespace julian 
#endif
