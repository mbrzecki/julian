#ifndef JULIAN_UNIFORMRNG_HPP
#define JULIAN_UNIFORMRNG_HPP

#include <vector>

namespace julian {

  /**
   * @file   uniformRNG.hpp
   * @brief  File contains implementation of RNG generating random variables from uniform distribution.
   */
  
  /** \ingroup rngs
   *
   * \brief Class implements interface for uniform number generators.
   *
   * Uniform RNG generates random number from continuous uniform distribution.
   * PDF of continuous uniform distribution is \f$\phi(x) = 1 \f$ for \f$ x \in [0,1) \f$ and \f$\phi(x) = 0\f$ otherwise. 
   */
   
  class UniformRNG {
  public:

    /**
     * \brief generate one random variable from uniform distribution.
     *
     */
    virtual double getRandom() = 0;

    
    /**
     * \brief generate n random variables from uniform distribution.
     *
     */
    virtual std::vector<double> getRandoms(int n) = 0;

    /**
     * \brief sets seed of RNG
     *
     */
    virtual void setSeed(unsigned int) = 0;

    /** \brief Virtual copy constructor
	
	Method is an implementation of virtual copy constructor.
    */
    virtual UniformRNG* clone() const;

    /** \brief destructor
    */
    virtual ~UniformRNG(){};
  private:
  };
  
}

#endif
