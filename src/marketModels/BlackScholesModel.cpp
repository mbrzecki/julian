#include <marketModels/BlackScholesModel.hpp>
#include <instruments/options/europeanOpt.hpp>
#include <mathematics/distributions/normalDistribution.hpp>
#include <interestRates/exponentialRate.hpp>
#include <dates/yearFractions/OneYF.hpp>
#include <dates/TimeGrids/DiscretizeWithTenor.hpp>
#include <mathematics/RNGs/Tausworthe.hpp>

namespace julian {

  /** \brief returns the date on which market data are actual
   */
  Date BlackScholesModel::getDate() const {
    return date_;
  }

  /** \brief returns the prize of asset
   */
  double BlackScholesModel::getAssetPrize() const {
    return asset_prize_;
  }

  /** \brief returns discounting curve
   */
  SmartPointer<ir::Curve> BlackScholesModel::getDiscountingCurve() const {
    return discounting_curve_;
  }

  /** \brief returns dividend curve
   */
  SmartPointer<ir::Curve> BlackScholesModel::getDividendCurve() const {
    return dividend_curve_;
  }

  /** \brief sets the market date
   *
   * \param date New market date
   */
  void BlackScholesModel::setDate(Date& date) {
    date_ = date;
  }
  
  /** \brief sets asset prize
   *
   *  \param input new asset prize
   */
  void BlackScholesModel::setAssetPrize(double input) {
    asset_prize_ = input;
  }

  /** \brief bump asset prize additively 
   *
   * \param h bump size
   */
  void BlackScholesModel::bumpAssetPrize(double h) {
    asset_prize_ += h;
  }

  /** \brief bump volatility additively 
   *
   *  \param h bump size
   *  \note Depending on the implementation of  volatility bumping may have different mechanism
   */
  void BlackScholesModel::bumpVolatility(double h) {
    volatility_->bumpVolatility(h);
  }

  /** \brief basing on discounting and dividend curve exponential drift is calculated
   *
   */
  double BlackScholesModel::calculateDrift(Date date) const {
    double exponens_of_drift = discounting_curve_->DF(date) / dividend_curve_->DF(date);
    ExponentialRate comp;
    OneYF yf;
    InterestRate rate(comp, yf);
    auto t = volatility_->getYearFraction(date_, date);
    return rate.zcRate(date_, date, exponens_of_drift) / t;
  }

  /** \brief method calculates the prize of European vanilla option 
   *
   * 
   * \f[ \begin{aligned} C & = i_{cp}  (S e^{-q T_{today,maturity} }N(i_{cp} d_{1}) - K e^{-r T_{today,maturity}} N(i_{cp}d_{2})) \\ 
     d_{1} & = \frac{ln(\frac{S}{K}) + (r - q) T_{today,maturity} + \frac{var}{2} }{\sqrt{var}} \\
     d_{2} & = \frac{ln(\frac{S}{K}) + (r - q) T_{today,maturity} - \frac{var}{2} }{\sqrt{var}} \\
     var & = \sigma^2(K, expiry) T_{today, expiry}
     \end{aligned}\f]
   * where:
   * * \f$S\f$ asset prize
   * * \f$K\f$ strike
   * * \f$\sigma\f$ volatility
   * * \f$r,q\f$ discounting rate, return on asset
   * * \f$i_{cp}\f$ 1 for Call option; -1 for put option
   * * \f$N()\f$ standard normal distribution
   */
  double BlackScholesModel::prizeAnalytically(const EuropeanOpt& opt) const {
    Date expiry;
    Date settlement;
    double strike;
    double notional;
    CallPut icp;

    std::tie(expiry, settlement, strike, notional, icp) = opt.getSettings();

    if (date_  >= expiry)
      return 0.0;
    
    auto var = volatility_->getVariance(strike, expiry);
    auto dfr = discounting_curve_->DF(settlement);
    auto dfq = dividend_curve_->DF(settlement);

    auto fwd = dfq * asset_prize_ / dfr;

    NormalDistribution N(0.0, 1.0);

    auto d1 = (log(fwd / strike) + 0.5*var) / sqrt(var);
    auto d2 = d1 - sqrt(var);
    return notional * icp * ( dfr * (fwd * N.CDF(icp * d1) - strike * N.CDF(icp * d2)));
  }
}  // namespace julian
