#include <mathematics/stochasticProcesses/cirProcess.hpp>
#include <mathematics/distributions/gaussianRandomVariable.hpp>
#include <cmath>
namespace julian {
  
 
  /**
   * \brief generates path  
   * \param x0 Value of the process for t = 0;
   * \param tg points in time for which the value of process is generated   
   * \param rng random number generator that will be used to generate stochastic process
   * \return path representing time series 
   *
   */
  Path CirProcess::getPath(double x0, const TimeGrid& tg, SmartPointer<UniformRNG>& rng) {
    auto t = tg.getGrid();
    GaussianRandomVariable norm(rng);
    return getPath(x0, tg, norm.getRandoms(t.size()-1));
  }

  /**
   * \brief generates path 
   *
   * Milstein discretization is used (see \cite gatheral)
   * \f[v_{t+dt} = v_{t} + \alpha (\theta + v_{t}) + \sigma \sqrt{v_{t}dt}dZ + \frac{1}{4} \sigma^{2} dt (dZ^2-1) \f]
   *
   *
   * \param x0 Value of the process for t = 0;
   * \param tg points in time for which the value of process is generated   
   * \param rnds random number that will be used to generate the path
   * \return path representing time series 
   *
   */
  Path CirProcess::getPath(double x0, const TimeGrid& tg, const std::vector<double>& rnds) const {
    auto t = tg.getGrid();
    std::vector<double> res {x0};
    for ( unsigned int i = 1; i < t.size() ; i++) {
      double dt = t.at(i) - t.at(i-1);
      double dZ = rnds.at(i);
      double x = res.back() + mrs_ * (lt_ - res.back()) * dt
    	+ vol_ * sqrt(res.back() * dt) * dZ
    	+ 0.25 * pow(vol_,2) * dt * (pow(dZ,2) - 1);
      res.push_back(x);
    }
    return Path(tg, res);
  }

  /** \brief Virtual copy constructor
   */
  CirProcess* CirProcess::clone() {
    return new CirProcess(*this);
  }
  
}
