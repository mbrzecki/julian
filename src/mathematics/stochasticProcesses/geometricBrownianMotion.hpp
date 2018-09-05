#ifndef JULIAN_GEOMETRICBROWNIANMOTION_HPP
#define JULIAN_GEOMETRICBROWNIANMOTION_HPP

#include <mathematics/stochasticProcesses/stochasticProcess.hpp>

namespace julian {

  /**
   * @file   geometricBrownianMotion.hpp
   * @brief  File contains function EasterForAGivenYear.
   */
  /** \ingroup stochasticProcesses
   * \brief Class is implements geometric Brownian motion.
   * 
   * Arithmetic Geometric Motion (ABM) is a stochastic process governed by following SDE:
   * \f[\frac{dX_{t}}{X_{t}} = \mu dt + \sigma dW_{t}\f]
   * where:
   * * \f$ \mu \f$ is drift
   * * \f$ \sigma \f$ is volatility
   * * \f$ dW \f$ is Wiener Process
   */
  class GeometricBrownianMotion: public StochasticProcess {
  public:
    GeometricBrownianMotion(){};
    GeometricBrownianMotion(double drift, double volatility);
    void setDrift(double);
    void setVolatility(double);  

    Path getPath(double, const TimeGrid&, SmartPointer<UniformRNG>& rng) const;
    Path getPath(double, const TimeGrid&, const std::vector<double>&) const; 

    virtual GeometricBrownianMotion* clone() const;
    virtual ~GeometricBrownianMotion(){};
  private:
    double drift_;  /*!< \brief Drift of the Geometric Brownian Motion*/
    double volatility_; /*!< \brief Volatility of the Geometric Brownian Motion*/
  };
}
#endif
