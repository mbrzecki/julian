#include <mathematics/RNGs/Tausworthe.hpp>

namespace julian {


  /** \brief Constructor
   *
   * in constructor we create the GSL Tausworthe algorithm
   */
  Tausworthe::Tausworthe() {
    const gsl_rng_type * T;
    T = gsl_rng_taus2;
    rnd_ = gsl_rng_alloc (T);
  }  

  /** \brief Copy constructor
   *
   * One need to explicitly define copy constructor to avoid memory-leak.
   */
  Tausworthe::Tausworthe(const Tausworthe& orig) {
    rnd_ = gsl_rng_clone (orig.rnd_); 
  }
  
  /** \brief Copy assignment operator
   *
   * One need to explicitly define Copy constructor to avoid memory-leak.
   */
  Tausworthe& Tausworthe::operator=(Tausworthe orig) {
    rnd_ = gsl_rng_clone (orig.rnd_);
    return *this;
  }

  /**
   * \brief generate one random variable from uniform distribution.
   *
   */
  double Tausworthe::getRandom() {
    return gsl_rng_uniform (rnd_);
  }
  /**
   * \brief generate n random variables from uniform distribution.
   *
   */  
  std::vector<double> Tausworthe::getRandoms(int n) {
    std::vector<double> vec(n);
    for (int i = 0; i < n; i++) {
      vec.at(i) = gsl_rng_uniform (rnd_);
    }
    return vec;
  }

  /** \brief Virtual copy constructor
	
      Method is an implementation of virtual copy constructor.
  */
  Tausworthe* Tausworthe::clone() const {
    return new Tausworthe(*this);
  }

  /**
   * \brief sets seed of RNG
   *
   */
  void Tausworthe::setSeed(unsigned int seed) {
    gsl_rng_set (rnd_, seed); 
  }

  /** \brief destructor
   *
   * One need to explicitly define destructor to avoid memory-leak.
   */
  Tausworthe::~Tausworthe() {
    gsl_rng_free (rnd_);
  }
  
}
