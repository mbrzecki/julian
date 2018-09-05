#ifndef JULIAN_TAUSWORTHE_HPP
#define JULIAN_TAUSWORTHE_HPP

#include <mathematics/RNGs/uniformRNG.hpp>
#include <gsl/gsl_rng.h>

namespace julian {

  /**
   * @file   Tausworthe.hpp
   * @brief  File contains implementation of Tausworthe generator.
   */
  
  
  /** \ingroup rngs
   *  \brief Class implements Tausworthe RNG
   *
   * Class implements refined Tausworthe RNG refined by L'Ecuyer. 
   * See \cite LEcuyer \cite Tausworthe 
   *
   * \remarks Class uses algorithms implemented in GSL
   */

  
  class Tausworthe: public UniformRNG {
  public:
    Tausworthe();
    Tausworthe(const Tausworthe&);
    Tausworthe& operator=(Tausworthe);
    
    virtual double getRandom();
    virtual std::vector<double> getRandoms(int);
    virtual void setSeed(unsigned int);
    virtual Tausworthe* clone() const;
    virtual ~Tausworthe();
  private:
    gsl_rng * rnd_; /*!< \brief GSL random number generator */
  };

}



#endif /* TAUSWORTHE_HPP */
