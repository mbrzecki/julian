#ifndef JULIAN_CIRPROCESS_HPP
#define JULIAN_CIRPROCESS_HPP

#include <mathematics/stochasticProcesses/stochasticProcess.hpp>
#include <mathematics/RNGs/uniformRNG.hpp>

namespace julian {
  /**
   * @file   cirProcess.hpp
   * @brief  File contains implementation of CIR Process.
   */
  /** \ingroup stochasticProcesses
   * \brief Class is implements Cox–Ingersoll–Ross (CIR) process.
   * 
   * Cox-Ingersoll-Ross (CIR) is a stochastic process governed by following SDE:
   * \f[dX_{t} = \alpha (\theta - X_{t}) dt + \sigma \sqrt{X_{t}} dW_{t}\f]
   * where:
   * * \f$ \alpha \f$ is mean reversion speed 
   * * \f$ \theta \f$ is long-term mean 
   * * \f$ \sigma \f$ is volatility 
   * * \f$ dW \f$ is Wiener Process
   */
  
  class CirProcess {
  public:
    /** \brief Default constructor
     */
    CirProcess(){};

    /** \brief Constructor
     */
    CirProcess(double mrs, double lt,  double vol):
      mrs_(mrs), lt_(lt), vol_(vol){};

    Path getPath(double, const TimeGrid&, SmartPointer<UniformRNG>& rng) ;
    Path getPath(double, const TimeGrid&, const std::vector<double>&) const; 
    CirProcess* clone();
    ~CirProcess(){};
    
  private:
    double mrs_; /*!< \brief mean reversion speed */
    double lt_;  /*!< \brief long-term mean*/
    double vol_; /*!< \brief volatility*/
  };
}  // namespace julian

#endif /* CIRPROCESS_HPP */
