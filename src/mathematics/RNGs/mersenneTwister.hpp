#ifndef JULIAN_MERSENNETWISTER_HPP
#define JULIAN_MERSENNETWISTER_HPP

#include <mathematics/RNGs/uniformRNG.hpp>
#include <gsl/gsl_rng.h>

namespace julian {

  /**
   * @file   mersenneTwister.hpp
   * @brief  File contains implementation of Mersenne Twister generator.
   */
  
 /** \ingroup rngs
   *  \brief Class implements Mersenne Twister RNG
   *
   * Class implements Mersenne Twister algorithm (known as MT19937). 
   * See \cite MersenneTwist
   *
   * \remarks Class uses algorithms implemented in GSL
   */
  
  class MersenneTwister: public UniformRNG {
  public:
    MersenneTwister();
    MersenneTwister(const MersenneTwister&);
    MersenneTwister& operator=(MersenneTwister);
    
    virtual double getRandom();
    virtual std::vector<double> getRandoms(int);
    virtual void setSeed(unsigned int);
    virtual MersenneTwister* clone() const;
    virtual ~MersenneTwister();
  private:
    gsl_rng * rnd_; /*!< \brief GSL random number generator */
  };

}


#endif /* MERSENNETWISTER_HPP */
