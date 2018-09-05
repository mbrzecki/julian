#include <mathematics/distributions/gaussianRandomVariable.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>

namespace julian {

  /** \brief constructor
   *
   * Tausworthe RNG is set by default. Standard normal distribution is used.
   */
  GaussianRandomVariable::GaussianRandomVariable()  {
      urng_ = Tausworthe();
    }

  /** \brief Constructor
   *
   * Standard normal distribution is used
   */
  GaussianRandomVariable::GaussianRandomVariable(SmartPointer<UniformRNG> urng):
    urng_(urng), dist_(0.0, 1.0)  {}

  /** \brief Constructor
   *
   * Creates normal random number using mean and standard deviation provided 
   */
  GaussianRandomVariable::GaussianRandomVariable(SmartPointer<UniformRNG> urng,double mean, double stddev):
    urng_(urng),dist_(mean, stddev) {}

  /** \brief Constructor
   *
   */
  GaussianRandomVariable::GaussianRandomVariable(SmartPointer<UniformRNG> urng, NormalDistribution dist):
    urng_(urng), dist_(dist) {}

  /** \brief Generates random variable
   * 
   * Methods uses inverse of CDF to generate random variable from specified distribution (see Chapter 10.4 \cite intphys)
   */
  double GaussianRandomVariable::getRandom() {
    return dist_.invCDF(urng_->getRandom());
  }

  /** \brief Generates set of random variable
   * 
   * Methods uses inverse of CDF to generate random variable from specified distribution (see Chapter 10.4 \cite intphys)
   */
  std::vector<double> GaussianRandomVariable::getRandoms(int n) {
    std::vector<double> ret = urng_->getRandoms(n);
    std::transform(ret.begin(), ret.end(), ret.begin(),[&](double d) -> double { return dist_.invCDF(d);});
    return ret;
  }

  /** \brief Generates correlated normal random numbers
   */
  std::pair<std::vector<double>,std::vector<double> > GaussianRandomVariable::getCorrelatedRandoms(int n,double corr) {
    auto vec1 = getRandoms(n);
    auto vec2 = getRandoms(n);
    for (unsigned int i = 0; i < vec1.size(); i++) {
      vec2.at(i) = corr * vec1.at(i) + sqrt( 1 - corr * corr) * vec2.at(i);
    }
    return std::make_pair(vec1, vec2);
  }

  /** \brief Set seed of pseudo-random number generator
   */  
  void GaussianRandomVariable::setSeed(unsigned int seed) {
    urng_->setSeed(seed);
  }

  /** \brief Virtual copy constructor
   */
  GaussianRandomVariable* GaussianRandomVariable::clone() const {
    return new GaussianRandomVariable(*this);
  }
}  // namespace julian
