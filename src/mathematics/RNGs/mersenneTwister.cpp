#include <mathematics/RNGs/mersenneTwister.hpp>
#include <iostream>
#include <vector>
namespace julian {

  /** \brief Constructor
   *
   * in constructor we create the GSL MersenneTwister algorithm
   */
  MersenneTwister::MersenneTwister() {
    const gsl_rng_type * T;
    T = gsl_rng_mt19937;
    rnd_ = gsl_rng_alloc(T);
  }

  /** \brief Copy constructor
   *
   * One need to explicitly define copy constructor to avoid memory-leak.
   */
  MersenneTwister::MersenneTwister(const MersenneTwister& orig) {
    rnd_ = gsl_rng_clone(orig.rnd_); 
  }

  /** \brief Copy assignment operator
   *
   * One need to explicitly define Copy constructor to avoid memory-leak.
   */
  MersenneTwister& MersenneTwister::operator=(MersenneTwister orig) {
    rnd_ = gsl_rng_clone(orig.rnd_);
    return *this;
  }

  /**
   * \brief generate one random variable from uniform distribution.
   *
   */
  double MersenneTwister::getRandom() {
    return gsl_rng_uniform (rnd_);
  }

  /**
   * \brief generate n random variables from uniform distribution.
   *
   */  
  std::vector<double> MersenneTwister::getRandoms(int n) {
    std::vector<double> vec(n);
    for (int i = 0; i < n; i++) {
      vec.at(i) = gsl_rng_uniform(rnd_);
    }
    return vec;
  }

  /** \brief Virtual copy constructor
	
      Method is an implementation of virtual copy constructor.
  */
  MersenneTwister* MersenneTwister::clone() const {
    return new MersenneTwister(*this);
  }

  /**
   * \brief sets seed of RNG
   *
   */
  void MersenneTwister::setSeed(unsigned int seed) {
    gsl_rng_set(rnd_, seed);
  }

  /** \brief destructor
   *
   * One need to explicitly define destructor to avoid memory-leak.
   */
  MersenneTwister::~MersenneTwister() {
    gsl_rng_free(rnd_);
  }
}  // namespace julian
