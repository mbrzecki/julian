#include <mathematics/stochasticProcesses/geometricBrownianMotion.hpp>
#include <mathematics/distributions/gaussianRandomVariable.hpp>
#include <cmath>

namespace julian {

  /** \brief constructor
   */
  GeometricBrownianMotion::GeometricBrownianMotion(double drift, double volatility) {
    drift_ = drift;
    volatility_ = volatility;
  }
  

  /** \brief sets drift
   */
  void GeometricBrownianMotion::setDrift(double drift) {
    drift_ = drift;
  }


  /** \brief sets volatility
   */
  void GeometricBrownianMotion::setVolatility(double volatility) {
    volatility_ = volatility;
  }

  /** \brief Virtual copy constructor
  */
  GeometricBrownianMotion* GeometricBrownianMotion::clone() const {
    return new GeometricBrownianMotion(*this);
  }

  /**
   * \brief generates path  
   * \param x0 Value of the process for t = 0;
   * \param tg in time for which the value of process is generated   
   * \param rng random number generator that will be used to generate stochastic process
   * \return path representing time series 
   *
   */
  Path GeometricBrownianMotion::getPath(double x0, const TimeGrid& tg, SmartPointer<UniformRNG>& rng) const {
    auto t = tg.getGrid();
    GaussianRandomVariable norm(rng);
    return getPath(x0, tg, norm.getRandoms(t.size()-1));
  }

  /**
   * \brief generates path 
   * \param x0 Value of the process for t = 0;
   * \param tg in time for which the value of process is generated   
   * \param rnds random number that will be used to generate the path
   * \return path representing time series 
   *
   */
  Path GeometricBrownianMotion::getPath(double x0,const TimeGrid& tg, const std::vector<double>& rnds) const {
    auto t = tg.getGrid();
    std::vector<double> res {x0};
    auto vol2 = 0.5 * volatility_ * volatility_;
    for ( unsigned int i = 1; i < t.size() ; i++) {
      double dt = t.at(i) - t.at(i-1);
      double x = res.back() * exp(drift_ * dt - vol2 * dt) * exp(volatility_ * sqrt(dt) * rnds.at(i-1));
      res.push_back(x);
    }
    return Path(tg, res);
  }
}  // namespace julian
