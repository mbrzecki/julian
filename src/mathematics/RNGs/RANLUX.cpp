#include <mathematics/RNGs/RANLUX.hpp>

namespace julian {

  /** \brief Constructor
   *
   * in constructor we create the GSL RANLUX algorithm
   */
  RANLUX::RANLUX() {
    const gsl_rng_type * T;
    T = gsl_rng_ranlxs2;
    rnd_ = gsl_rng_alloc (T);
  }  

  /** \brief Copy constructor
   *
   * One need to explicitly define copy constructor to avoid memory-leak.
   */
  RANLUX::RANLUX(const RANLUX& orig) {
    rnd_ = gsl_rng_clone (orig.rnd_); 
  }

  /** \brief Copy assignment operator
   *
   * One need to explicitly define Copy constructor to avoid memory-leak.
   */
  RANLUX& RANLUX::operator=(RANLUX orig) {
    rnd_ = gsl_rng_clone (orig.rnd_);
    return *this;
  }

  /**
   * \brief generate one random variable from uniform distribution.
   *
   */
  double RANLUX::getRandom() {
    return gsl_rng_uniform (rnd_);
  }

  /**
   * \brief generate one random variable from uniform distribution.
   *
   */
  std::vector<double> RANLUX::getRandoms(int n) {
    std::vector<double> vec(n);
    for (int i = 0; i < n; i++) {
      vec.at(i) = gsl_rng_uniform (rnd_);
    }
    return vec;
  }

  /** \brief Virtual copy constructor
	
      Method is an implementation of virtual copy constructor.
  */
  RANLUX* RANLUX::clone() const {
    return new RANLUX(*this);
  }

  /**
   * \brief sets seed of RNG
   *
   */
  void RANLUX::setSeed(unsigned int seed) {
    gsl_rng_set (rnd_, seed); 
  }

  /** \brief destructor
   *
   * One need to explicitly define destructor to avoid memory-leak.
   */
  RANLUX::~RANLUX() {
    gsl_rng_free (rnd_);
  }
  
}
