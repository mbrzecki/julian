#ifndef JULIAN_GAUSSIANRANDOMVARIABLE_HPP
#define JULIAN_GAUSSIANRANDOMVARIABLE_HPP

#include <mathematics/RNGs/uniformRNG.hpp>
#include <mathematics/distributions/randomVariable.hpp>
#include <mathematics/distributions/normalDistribution.hpp>
#include <mathematics/RNGs/Tausworthe.hpp>
#include <utils/smartPointer.hpp>

namespace julian {

  /**
   * @file   gaussianRandomVariable.hpp
   * @brief  File contains definition of GaussianRandomVariable.
   */

  
  /** \ingroup distributions
   * 
   * \brief Class implements the Gaussian random variable
   * 
   * Gaussian Random Variable generates pseudo-random numbers from Gaussian distribution. 
   * 
   */
  
  class GaussianRandomVariable : public RandomVariable {
  public:
    GaussianRandomVariable();
    GaussianRandomVariable(SmartPointer<UniformRNG>);
    GaussianRandomVariable(SmartPointer<UniformRNG>,double mean, double stddev);
    GaussianRandomVariable(SmartPointer<UniformRNG>, NormalDistribution dist);
    double getRandom();
    std::vector<double> getRandoms(int);
    std::pair<std::vector<double>,std::vector<double> > getCorrelatedRandoms(int,double);
    void setSeed(unsigned int);

    /** \brief destructor
     */
    ~GaussianRandomVariable(){}
    GaussianRandomVariable* clone() const;
  private:
    SmartPointer<UniformRNG> urng_; /*!<Pseudo-random generator used to generate random numbers.*/
    NormalDistribution dist_;  /*!< Normal distribution*/
 
  };
  
}

#endif
