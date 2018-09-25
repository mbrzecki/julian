#include <mathematics/distributions/customRandomVariable.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>

namespace julian {
  /** \brief constructor
   */
  CustomRandomVariable::CustomRandomVariable(SmartPointer<ProbabilityDistribution> dist,SmartPointer<UniformRNG> urng):
    dist_(dist), urng_(urng) {}

  /** \brief Generates random variable
   * 
   * Methods uses inverse of CDF to generate random variable from specified distribution (see Chapter 10.4 \cite intphys)
   */
  double CustomRandomVariable::getRandom() {
    return dist_->invCDF(urng_->getRandom());
  }

  /** \brief Generates set of random variable
   * 
   * Methods uses inverse of CDF to generate random variable from specified distribution (see Chapter 10.4 \cite intphys)
   */
  std::vector<double> CustomRandomVariable::getRandoms(int n) {
    std::vector<double> ret = urng_->getRandoms(n);
    std::transform(ret.begin(), ret.end(), ret.begin(),[&](double d) -> double { return dist_->invCDF(d);});
    return ret;
  }

  /** \brief Changes seed of RNG
   */
  void CustomRandomVariable::setSeed(unsigned int seed) {
    urng_->setSeed(seed);
  }
  /** \brief Virtual copy constructor
   */
  CustomRandomVariable* CustomRandomVariable::clone() const {
    return new CustomRandomVariable(*this);
  }
} // namespace julian
