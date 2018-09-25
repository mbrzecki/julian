#ifndef JULIAN_RANDOMVARIABLE_HPP
#define JULIAN_RANDOMVARIABLE_HPP

#include <mathematics/RNGs/uniformRNG.hpp>
#include <mathematics/distributions/probabilityDistribution.hpp>
#include <utils/smartPointer.hpp>

namespace julian {
  /**
   * @file   randomVariable.hpp
   * @brief  File contains definition of RandomVariable.
   */

  
  /** \ingroup distributions
   * 
   * \brief Class implements the interface for Random Variables
   * 
   * This class interface implements the concept of random variable.  Random variable is a variable whose possible values are outcomes of a random phenomenon.
   * It is used to generate the pseudo-random variable from specified distribution. 
   *
   */
  
  
  class RandomVariable {
  public:
    RandomVariable(){};

    /** \brief Generates pseudo-random variable
     */
    virtual double getRandom() = 0;
    /** \brief Generates set of pseudo-random variables
     */
    virtual std::vector<double> getRandoms(int) = 0;
    /** \brief Set seeds of pseudo-random generator
     */
    virtual void setSeed(unsigned int) = 0;
    /** \brief Destructor
     */
    virtual ~RandomVariable(){}
    /** \brief Virtual copy constructor
     */
    virtual RandomVariable* clone() const;
  };
  
}

#endif
