#include <mathematics/stochasticProcesses/arithmeticBrownianMotion.hpp>
#include <mathematics/distributions/gaussianRandomVariable.hpp>
#include <cmath>

namespace julian {

  /** \brief constructor
   */
  ArithmeticBrownianMotion::ArithmeticBrownianMotion(double drift, double volatility) {
    drift_ = drift;
    volatility_ = volatility;
  }

  /**
   *  \brief Generates path  
   * \param x0 Value of the process for t = 0;
   * \param tg points in time for which the value of process is generated   
   * \param rng random number generator that will be used to generate stochastic process
   * \return path representing time series 
   *
   */
  Path ArithmeticBrownianMotion::getPath(double x0, const TimeGrid& tg, SmartPointer<UniformRNG>& rng) const {
    auto t = tg.getGrid();
    GaussianRandomVariable norm(rng);
    return getPath(x0, tg, norm.getRandoms(t.size()-1));
  }

  /**
   * \brief generates path 
   * \param x0 Value of the process for t = 0;
   * \param tg points in time for which the value of process is generated   
   * \param rnds random number that will be used to generate the path
   * \return path representing time series 
   *
   */
  Path ArithmeticBrownianMotion::getPath(double x0,const TimeGrid& tg,const std::vector<double>& rnds) const {
    auto t = tg.getGrid();
    std::vector<double> res {x0};
    for (unsigned int i = 1; i < t.size() ; i++) {
      double dt = t.at(i) - t.at(i-1);
      double rnd = rnds.at(i);
      double x = res.back() + drift_ * dt +  volatility_ * sqrt(dt) * rnd;
      res.push_back(x);
    }
    return Path(tg, res);
  }

  /** \brief Virtual copy constructor
  */
  ArithmeticBrownianMotion* ArithmeticBrownianMotion::clone() const {
    return new ArithmeticBrownianMotion(*this);
  }

  /** \brief sets drift
   */
  void ArithmeticBrownianMotion::setDrift(double input)  {
    drift_ = input;
  }

  /** \brief sets volatility
   */
  void ArithmeticBrownianMotion::setVolatility(double input) {
    volatility_ = input;
  }
}  // namespace julian
