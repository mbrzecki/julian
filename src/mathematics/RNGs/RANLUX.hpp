#ifndef JULIAN_RANLUX_HPP
#define JULIAN_RANLUX_HPP

#include <mathematics/RNGs/uniformRNG.hpp>
#include <gsl/gsl_rng.h>


namespace julian {
  /**
   * @file   RANLUX.hpp
   * @brief  File contains implementation of RANLUX generator.
   */
  
  
  /** \ingroup rngs
   *  \brief Class implements RANLUX RNG
   *
   * Class implements RANLUX algorithm of Luscher
   * See \cite Luscher
   *
   * \remarks Class uses algorithms implemented in GSL
   */
  
  class RANLUX: public UniformRNG {
  public:
    RANLUX();
    RANLUX(const RANLUX&);
    RANLUX& operator=(RANLUX);
    
    virtual double getRandom();
    virtual std::vector<double> getRandoms(int);
    virtual void setSeed(unsigned int);
    virtual RANLUX* clone() const;
    virtual ~RANLUX();
  private:
    gsl_rng * rnd_; /*!< \brief GSL random number generator */
  };

}


#endif /* RANLUX_HPP */
