#ifndef JULIAN_HESTONPROCESS_HPP
#define JULIAN_HESTONPROCESS_HPP

#include <mathematics/stochasticProcesses/stochasticProcess.hpp>

namespace julian {

   /**
   * @file   hestonProcess.hpp
   * @brief  Implementation of Heston stochastic process
   */
  /** \ingroup stochasticProcesses
   * \brief Class is implements Heston process.
   * 
   *Heston process is a stochastic process governed by following SDE:
   * \f[dX_{t} = \mu X_{t} dt + \sqrt{Y_{t}} X_{t} dW^{X}_{t}\f]
   * \f[dY_{t} = \alpha (\theta - Y_{t}) dt + \sqrt{Y_{t}} \sigma dW^{Y}_{t}\f]
   * \f[\langle dW^{X}_{t}, dW^{Y}_{t}\rangle = \rho \f]
   * where:
   * * \f$ \mu \f$ is drift
   * * \f$ \alpha \f$ is mean reversion speed
   * * \f$ \theta \f$ is long-term volatility
   * * \f$ \sigma \f$ is volatility of volatility
   * * \f$ \rho \f$ is correlation
   * * \f$ dW^{X},dW^{Y} \f$ are Wiener Processes
   *
   * As we see the process \f$X\f$ is Geometric Brownian Motion with stochastic volatility governed by CIR process. More information see \cite Heston
   */
    
  class HestonProcess : public StochasticProcess {
  public:
    HestonProcess(){};

    
    /** \brief constructor
	\param drift Drift of the X process
	\param mean_rev Mean reversion speed of Y process
	\param curr_var Initial value of Y process of Y process
	\param lt_var Long term value of Y process
	\param vov Volatility of Y process
	\param corr Correlation between X process and Y process
     */
    HestonProcess(double drift, double mean_rev, double curr_var, double lt_var,  double vov, double corr):
      drift_(drift), mean_rev_(mean_rev), curr_var_(curr_var), lt_var_(lt_var), vov_(vov), corr_(corr) {};
    virtual Path getPath(double, const TimeGrid&, SmartPointer<UniformRNG>& rng) const;
    virtual Path getPath(double, const TimeGrid&, const std::vector<double>& rnds) const;
    virtual HestonProcess* clone() const;
    virtual ~HestonProcess(){};
    
  private:
    double drift_; /*!< \brief Drift of the X process*/
    double mean_rev_; /*!< \brief Mean reversion speed of Y process*/
    double curr_var_ ; /*!< \brief Initial value of Y process of Y process*/
    double lt_var_; /*!< \brief Long term value of Y process*/
    double vov_; /*!< \brief Volatility of Y process*/
    double corr_; /*!< \brief Correlation between X process and Y process*/
  };
}  // namespace julian



#endif
