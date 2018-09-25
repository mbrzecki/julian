#include <mathematics/numericalAlgorithms/SimulatedAnnealing.hpp>
#include <mathematics/distributions/normalDistribution.hpp>

namespace julian {

  /** \brief Set cooling schedule
   */  
  void SimulatedAnnealing::setCoolingSchedule(const std::vector<double>& cooling_schedule) {
    cooling_schedule_ = cooling_schedule;
  }
  
  /** \brief Calculates linear cooling schedule
   *
   * Cooling schedule is calculating basing on Tstart, Tend and step provided by an user.
   * The Schedule is \f$[T_{start}, T_{start} - \text{step}, T_{start} - 2\text{step}, T_{start}-3\text{step},..., T_{end} ]\f$
   * 
   */  
  void SimulatedAnnealing::setLinearCooling(double Tstart, double Tend, double step) {
    cooling_schedule_.clear();
    for (double t = Tstart; t >= Tend; t = t - step) {
      cooling_schedule_.push_back(t);
    }
  }

  /** \brief Calculates exponential cooling schedule
   *
   * Cooling schedule is calculating basing on Tstart, Tend and step provided by an user.
* The Schedule is \f$[T_{start}, \frac{T_{start}}{\text{step}}, \frac{T_{start}}{\text{step}^2}, \frac{T_{start}}{\text{step}^3},..., T_{end} ]\f$
   * 
   */  
  void SimulatedAnnealing::setExponentialCooling(double Tstart, double Tend, double param) {
    cooling_schedule_.clear();
      for (double t = Tstart; t >= Tend; t = t * param) {
	cooling_schedule_.push_back(t);  
      }
  }

  /** \brief Calculate the new state
   */
  double SimulatedAnnealing::takeStep(double x) {
    return x + step_->getRandom();
  }

  /** \brief Calculate the new state
   */
  std::vector<double> SimulatedAnnealing::takeStep(std::vector<double> x) {
    std::vector<double> ret;
    for (auto item : x) {
      ret.push_back(item + step_->getRandom());
    }
    return ret;
  }
}  // namespace julian
