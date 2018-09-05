#include <pricingEngines/BlackScholesCalculator.hpp>
#include <mathematics/distributions/normalDistribution.hpp>
#include <mathematics/numericalAlgorithms/derivativeRootFinder.hpp>
#include <mathematics/numericalAlgorithms/bracketingRootFinder.hpp>
#include <cmath>

namespace julian {

  /** \ingroup pricing_engines
   * 
   * \fn double prizeBlackScholes(double S,double K, double DFr,double DFq, double vol, double t, CallPut icp)
   * \brief Function calculates prize of European option using Black-Scholes formula
   *
   * Function uses BS formula:
   * \f[ \begin{aligned} C & = i_{cp}  (S \times DFq \times N(i_{cp} d_{1}) - K \times DFr \times N(i_{cp}d_{2})) \\
     d_{1} & = \frac{ln(\frac{S\frac{DFq}{DFr}}{K}) +  \frac{var}{2}  t}{\sqrt{var}}  \\
     d_{2} & = \frac{ln(\frac{S\frac{DFq}{DFr}}{K}) -  \frac{var}{2}  t}{\sqrt{var}}  \\
     var & = vol^2 t
     \end{aligned}\f]

   * \param S asset prize
   * \param K strike
   * \param DFr discount factor
   * \param DFq capitalization of asset prize
   * \param vol volatility of asset prize
   * \param t time in years 
   * \param icp Call/Put, equals 1 for Call and -1 for Put
   * \return prize of European Option paying \f$max(icp(S-K),0) \f$ at time T
   */
  double prizeBlackScholes(double S,double K, double DFr,double DFq, double vol, double t, CallPut icp) {
    NormalDistribution n(0,1);
    double variance = vol * vol * t;
    double d1 = (log(S * DFq / K / DFr) + 0.5*variance) / sqrt(variance);
    double d2 = d1 - sqrt(variance);
    return icp * (DFq * S * n.CDF(icp * d1) - DFr * K * n.CDF(icp * d2));
  }

  /** \ingroup pricing_engines
   * 
   * \fn double calculateImpliedVolatility(double S,double K, double DFr,double DFq, double prize, double t, CallPut icp)
   * \brief Function calculates implied volatility
   *
   * Function uses BracketingRootFinder::BRENT_DEKKER algorithm to find the value of volatility that match Black-Scholes prize with market prize.
   * Function uses julian::prizeBlackScholes function
   *
   * \param S asset prize
   * \param K strike
   * \param DFr discount factor
   * \param DFq capitalization of asset prize
   * \param prize option's prize
   * \param t time in years 
   * \param icp Call/Put, equals 1 for Call and -1 for Put
   * \return implied volatility
   */
  double calculateImpliedVolatility(double S,double K, double DFr,double DFq, double prize, double t, CallPut icp) {
    auto f = [&](double vol)->double {
      return prize - prizeBlackScholes(S,K,DFr,DFq,vol,t,icp);
    };
    return bracketingRootFinder<decltype(f)>(f,0.0000001,10.0,BracketingRootFinder::BRENT_DEKKER,1e-13,10000);
  }

  /** \ingroup pricing_engines
   * 
   * \fn double calculateBlackScholesDelta(double S,double K, double DFr,double DFq, double vol, double t, CallPut icp)
   * \brief Function calculates delta parameter of European option 
   *
   * Function uses BS formula:
   * \f[ \begin{aligned} C & = i_{cp}  \times S \times DFq \times N(i_{cp} d_{1}) \\
     d_{1} & = \frac{ln(\frac{S\frac{DFq}{DFr}}{K}) +  \frac{var}{2}  t}{\sqrt{var}}  \\
     var & = vol^2 t
     \end{aligned}\f]

   * \param S asset prize
   * \param K strike
   * \param DFr discount factor
   * \param DFq capitalization of asset prize
   * \param vol volatility of asset prize
   * \param t time in years 
   * \param icp Call/Put, equals 1 for Call and -1 for Put
   * \return delta of European Option paying \f$max(icp(S-K),0) \f$ at time T
   */
  double calculateBlackScholesDelta(double S,double K, double DFr,double DFq, double vol, double t, CallPut icp) {
    NormalDistribution n(0,1);

    double variance = vol * vol * t;
    double d1 = (log(S * DFq / K / DFr) + 0.5*variance) / sqrt(variance);
    
    return icp *  DFq * n.CDF(icp * d1);
  }

  /** \ingroup pricing_engines
   * 
   * \fn double calculateStrikeFromCallDelta(double spot,double DFr,double DFq,double vol,double t,double delta)
   * \brief Function calculates delta parameter of European option 
   *
   * Function uses BS formula:
   * \f[ \frac{DFq}{DFr} \times spot * exp^{ N^{-1}( delta / DFq) \times vol \times sqrt(t) - 0.5 \times vol \times vol \times t}\f]
   * where \f$N^{-1}\f$ is inverse CDF of normal distribution
   * \param spot asset prize
   * \param DFr discount factor
   * \param DFq capitalization of asset prize
   * \param vol volatility of asset prize
   * \param t time in years 
   * \param delta delta of call
   * \return strike of European option
   */
  double calculateStrikeFromCallDelta(double spot,double DFr,double DFq,double vol,double t,double delta) {
    NormalDistribution N(0.0, 1.0);
    double fwd = DFq * spot / DFr;
    double temp =  N.invCDF( delta / DFq) * vol * sqrt(t) - 0.5 * vol * vol * t;
    double strike = fwd * exp(- temp);
    return strike;
  }

  /** \ingroup pricing_engines
   * 
   * \fn double calculateStrikeFromPutDelta(double spot,double DFr,double DFq,double vol,double t,double delta)
   * \brief Function calculates delta parameter of European option 
   *
   * Function uses BS formula:
   * \f[ \frac{DFq}{DFr} \times spot * exp^{-( N^{-1}( -delta / DFq) \times vol \times sqrt(t) - 0.5 \times vol \times vol \times t)}\f]
   * where \f$N^{-1}\f$ is inverse CDF of normal distribution
   * \param spot asset prize
   * \param DFr discount factor
   * \param DFq capitalization of asset prize
   * \param vol volatility of asset prize
   * \param t time in years 
   * \param delta delta of call
   * \return strike of European option
   */
  double calculateStrikeFromPutDelta(double spot,double DFr,double DFq,double vol,double t,double delta) {
    NormalDistribution N(0.0, 1.0);
    double fwd = DFq * spot / DFr;
    double temp = - N.invCDF(- delta / DFq) * vol * sqrt(t) - 0.5 * vol * vol * t;
    double strike = fwd * exp(- temp);
    return strike;
  }
}  // namespace julian
