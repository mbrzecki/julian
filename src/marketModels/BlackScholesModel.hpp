#ifndef JULIAN_BLACKSCHOLESMODEL_HPP
#define JULIAN_BLACKSCHOLESMODEL_HPP

#include <marketModels/marketModel.hpp>
#include <marketData/volatility/volatility.hpp>
#include <marketData/interestRateCurves/irCurve.hpp>
#include <marketData/ForwardCurve.hpp>
#include <dates/date.hpp>
#include <mathematics/stochasticProcesses/geometricBrownianMotion.hpp>


namespace julian {

  /**
   * @file   BlackScholesModel.hpp
   * @brief  File contains implementation of Black Scholes model.
   */

  /** \ingroup marketmodels
   * \brief Class implements Black Scholes model
   *
   * \b PDE
   * \f[{\frac {\partial V}{\partial t}}+{\frac {1}{2}}\sigma ^{2}S^{2}{\frac {\partial ^{2}V}{\partial S^{2}}}+rS{\frac {\partial V}{\partial S}}-rV=0\f]
   *
   * \b SDE
   * \f[dS_t = (r-q) S_t dt + \sigma S_t dW_t^Q\f]
   *
   * For more information see: \cite BlackScholes \cite BlackScholesHoles \cite Hull \cite Iclark
   *
   * and links
   * * *[Wiki](https://en.wikipedia.org/wiki/Black–Scholes_model)*
   * * *[Four Derivations of the Black Scholes PDE](http://www.frouah.com/finance%20notes/Black%20Scholes%20PDE.pdf)* 
   *
   */
  
  class BlackScholesModel: public DeeplyCopyableMarketModel<BlackScholesModel> {
  public:
    /** \brief Default Constructor
     */
    BlackScholesModel(){};
    /** \brief Constructor
     */
    BlackScholesModel(const Date& date, const double& asset_prize,
		      const SmartPointer<ir::Curve>&  discounting_curve,
		      const SmartPointer<ir::Curve>&  dividend_curve,
		      const SmartPointer<Volatility>& volatility):
      date_(date), asset_prize_(asset_prize), discounting_curve_(discounting_curve),
      dividend_curve_(dividend_curve), volatility_(volatility) {};

    virtual Date getDate() const override; 
    virtual double getAssetPrize() const override;
    virtual SmartPointer<ir::Curve> getDiscountingCurve() const override;
    virtual SmartPointer<ir::Curve> getDividendCurve() const override;

    virtual void setDate(Date&) override;
    virtual void setAssetPrize(double) override;
    virtual void bumpAssetPrize(double) override;
    virtual void bumpVolatility(double) override;
    
    double prizeAnalytically(const EuropeanOpt&) const override;
    
    virtual ~BlackScholesModel(){};
    
  private:
    Date date_;                                 /*!< \brief Market date*/
    double asset_prize_;                        /*!< \brief Underlying asset prize*/
    SmartPointer<ir::Curve> discounting_curve_; /*!< \brief Curve used to discount CFs*/
    SmartPointer<ir::Curve> dividend_curve_;    /*!< \brief Curve used to estimate continuous dividend*/
    SmartPointer<Volatility> volatility_;       /*!< \brief Volatility of the asset prize*/

    double calculateDrift(Date) const;
  };
}

#endif /* BLACKSCHOLESMODEL_HPP */
