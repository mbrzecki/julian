#include <mathematics/stochasticProcesses/hestonProcess.hpp>
#include <mathematics/stochasticProcesses/cirProcess.hpp>
#include <mathematics/distributions/gaussianRandomVariable.hpp>
#include <cmath>
#include <vector>
namespace julian {

  /**
   *  \brief Generates path  
   * \param x0 initial_value Value of the process for t = 0;
   * \param tg points in time for which the value of process is generated   
   * \param rng random number generator that will be used to generate stochastic process
   * \return path representing time series 
   *
   */
  Path HestonProcess::getPath(double x0, const TimeGrid& tg, SmartPointer<UniformRNG>& rng) const {
    auto t = tg.getGrid();
    GaussianRandomVariable gaussian_var(rng);
    auto rnds = gaussian_var.getCorrelatedRandoms(t.size(), corr_);
    rnds.first.insert( rnds.first.end(), rnds.second.begin(), rnds.second.end()); 
    return getPath(x0, tg, rnds.first);
  }

  /**
   * \brief Generates path 
   * \param x0 Value of the process for t = 0;
   * \param tg points in time for which the value of process is generated   
   * \param rnds random number that will be used to generate the path
   * \return path representing time series 
   */
  Path HestonProcess::getPath(double x0, const TimeGrid& tg, const std::vector<double>& rnds) const {
    std::size_t const half_size = rnds.size() / 2;
    std::vector<double> x_randoms(rnds.begin(), rnds.begin() + half_size);
    std::vector<double> y_randoms(rnds.begin() + half_size, rnds.end());
    auto t = tg.getGrid();
    CirProcess var_process(mean_rev_, lt_var_, vov_);

    auto var_path = var_process.getPath(curr_var_, tg, y_randoms);
    auto var_vector = var_path.getValues();

    std::vector<double> res {x0};
    for (unsigned int i = 1; i < t.size(); i++) {
      double dt = t.at(i) - t.at(i-1);
      double variance = var_vector.at(i-1);
      double x = res.back() * exp(drift_ * dt - 0.5 * variance * dt) * exp(sqrt(variance * dt) * x_randoms.at(i-1));
      res.push_back(x);
    }
    return Path(tg, res);
  }

  /** \brief Virtual copy constructor
   */
  HestonProcess* HestonProcess::clone() const {
    return new HestonProcess(*this);
  }
}  // namespace julian
