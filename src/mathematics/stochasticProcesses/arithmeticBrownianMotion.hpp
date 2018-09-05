#ifndef JULIAN_ARITHEMTICBROWNIANMOTION_HPP
#define JULIAN_ARITHEMTICBROWNIANMOTION_HPP

#include <mathematics/stochasticProcesses/stochasticProcess.hpp>

namespace julian {
  /**
   * @file   arithmeticBrownianMotion.hpp
   * @brief  File contains implementation arithmeticBrownianMotion.
   */
  /** \ingroup stochasticProcesses
   * \brief Class is implements arithmetic Brownian motion.
   * 
   * Arithmetic Brownian Motion (ABM) is a stochastic process governed by following SDE:
   * \f[dX_{t} = \mu dt + \sigma dW_{t}\f]
   * where:
   * * \f$ \mu \f$ is drift
   * * \f$ \sigma \f$ is volatility
   * * \f$ dW \f$ is Wiener Process
   */
  
  class ArithmeticBrownianMotion: public StochasticProcess {
  public:
    ArithmeticBrownianMotion(double drift, double volatility);
    Path getPath(double,const TimeGrid&,SmartPointer<UniformRNG>&) const;
    Path getPath(double,const TimeGrid&,const std::vector<double>&) const; 
    virtual ArithmeticBrownianMotion* clone() const;
    virtual ~ArithmeticBrownianMotion(){};

    void setDrift(double);
    void setVolatility(double);
  
  private:
    double drift_; /*!< \brief Drift of the Arithmetic Brownian Motion*/
    double volatility_; /*!< \brief Volatility of the Arithmetic Brownian Motion*/
 
  };
}  // namespace julian
#endif
