#include <instruments/options/europeanOpt.hpp>
#include <utils/formatters.hpp>
#include <mathematics/statistics/descriptiveStatistics.hpp>

namespace julian {

  EuropeanOpt::EuropeanOpt(Date trade_date, Date start_date,
			   Date expiry_date, Date delivery_date ,
			   double notional,double strike, CallPut icp):
    trade_date_(trade_date), start_date_(start_date),
    expiry_date_(expiry_date), delivery_date_(delivery_date),
    notional_(notional), strike_(strike), icp_(icp) {}

  /** \brief Calculates payoff at expiry
   *
   * Pay-off:
   * * In case of Call
   * \f[max(Spot_{T}-K,0)\f]
   * * In case of Call
   * \f[max(K-Spot_{T},0)\f]
   */
  double EuropeanOpt::payoff(double S) const {
    double result = icp_ * ( S - strike_);
    if (result < 0.0)
      return 0.0;
    return notional_ * result;
  }

  /** \brief calculates the option value basing on the paths provided by Monte Carlo Pricer
   *
   * \f[Prize = DF \frac{1}{\#paths} \sum^{n=\#paths}_{n=1} Payoff(S_{n}(T_{expiry}))\f]
   *
   */
  double EuropeanOpt::prizePaths(std::vector<Path> paths,double df) const {
    std::vector<double> prices;
    for (auto p: paths) {
      auto temp = p.getValues();
      prices.push_back(payoff(temp.back()));
    }
    return df * stats::mean(prices);
  }

  /** \brief returns expiry date
   */
  Date EuropeanOpt::getExpiry() const {
    return expiry_date_;
  }

  /** \brief returns maturity date
   */
  Date EuropeanOpt::getMaturity() const {
    return delivery_date_;
  }

  /** \brief returns strike
   *
   */
  double EuropeanOpt::getStrike() const {
    return strike_;
  }

  /** \brief returns option type
   *
   */
  CallPut EuropeanOpt::getType() const {
    return icp_;
  }

  /** \brief Empty method
   */
  void EuropeanOpt::recordFixing(Date,double) {
  }

  /** \brief returns the tuple of option's parameters
   *
   * Method is used by analytical prizing engine
   */
  std::tuple<Date,Date,double,double,CallPut> EuropeanOpt::getSettings() const {
    return std::make_tuple(expiry_date_, delivery_date_, strike_, notional_, icp_);
  }

  /** \brief Virtual copy constructor
   */
  EuropeanOpt* EuropeanOpt::clone() const {
    return new EuropeanOpt(*this);
  }

  /** \brief calculates the price of option using market model provided
   */
  double EuropeanOpt::prizeAnalytically(const SmartPointer<MarketModel>& model) const  {
    return model->prizeAnalytically(*this);
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, EuropeanOpt& opt) {   
    s << "Object: EuropeanOption"
      << "\nTradeDate: " << opt.trade_date_
      << "\nStartDate: " << opt.start_date_ 
      << "\nExpiryDate: " << opt.expiry_date_
      << "\nMaturity: " << opt.delivery_date_
      << "\nNotional: " << formatter::currency(opt.notional_)
      << "\nStrike: " << std::setprecision(5) << opt.strike_ << "\n";
    
    if (opt.icp_ == CALL) {
      std::cout << "Type: Call\n" ;
    } else {
      std::cout << "Type: Put\n" ;
    }
   
    return s;
  }

  
}  // namespace julian
