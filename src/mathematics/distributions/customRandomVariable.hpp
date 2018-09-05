#ifndef JULIAN_CUSTOMRANDOMVARIABLE_HPP
#define JULIAN_CUSTOMRANDOMVARIABLE_HPP

#include <mathematics/RNGs/uniformRNG.hpp>
#include <mathematics/RNGs/Tausworthe.hpp>
#include <mathematics/distributions/probabilityDistribution.hpp>
#include <mathematics/distributions/randomVariable.hpp>
#include <mathematics/distributions/normalDistribution.hpp>
#include <utils/smartPointer.hpp>

namespace julian {

  /**
   * @file   customRandomVariable.hpp
   * @brief  File contains definition of CustomRandomVariable.
   */

  
  /** \ingroup distributions
   * 
   * \brief Class implements the custom random variable
   * 
   * Custom random variable implements a Strategy Design Pattern. It captures the abstraction of random variable composed of Random Number Generator and Probability Distribution.
   * RNG and distribution can be change independently. 
   * 
   */
  
  class CustomRandomVariable : public RandomVariable {
  public:
    /** \brief Default constructor
     *
     * Default inputs are Tausworthe RNG and standard normal distribution.
     */
    CustomRandomVariable(): dist_(NormalDistribution()), urng_(Tausworthe()) {};
    CustomRandomVariable(SmartPointer<ProbabilityDistribution>, SmartPointer<UniformRNG>);
    double getRandom() override;
    std::vector<double> getRandoms(int) override;
    void setSeed(unsigned int) override;

    CustomRandomVariable* clone() const;
  private:
    SmartPointer<ProbabilityDistribution> dist_; /*!< Probability distribution of random variable*/
    SmartPointer<UniformRNG> urng_; /*!<Pseudo-random generator used to generate random numbers.*/
  };
  
}

#endif
