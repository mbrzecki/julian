#ifndef SCALELOCATIONDISTRIBUTION_HPP
#define SCALELOCATIONDISTRIBUTION_HPP

#include <mathematics/distributions/probabilityDistribution.hpp>

namespace julian {

    /**
   * @file   scaleLocationDistribution.hpp
   * @brief  File contains implementation of scale-location family of random distributions
   */
  /** \ingroup distributions
   * 
   *\brief Class implements an interface of location scale distribution.
   *
   * In probability theory, especially in mathematical statistics, a location–scale family is a family of probability distributions 
   * parametrized by a location parameter and a non-negative scale parameter. 
   * If X, Y are two random variables whose distribution functions are members of the family, and assuming X has location = 0 and unit scale = 1 ,
   * then Y parametrized with location = \f$\lambda\f$ and scale = \f$\sigma\f$ can be written as Y = \f$\lambda\f$  + \f$\sigma\f$ X.
   *
   * Location Scale Distribution is characterize by following parameters:
   * 
   * **Location**
   *
   * \f[CDF(t - location | location) = CDF(t | 0.0)\f]
   *
   *  **Scale**
   *
   *  \f[CDF(t / scale | scale) = CDF(t | 1.0)\f]
   *
   *  **Shape**
   *
   *  Shape parameter is any parameter of a probability distribution that is neither a location parameter nor a scale parameter 
   *  (nor a function of either or both of these only). Such a parameter must affect the shape of a distribution rather than simply
   *  shifting it (as a location parameter does) or stretching/shrinking it (as a scale parameter does). 
   */
  class ScaleLocationDistribution : public ProbabilityDistribution {
  public:    
    /**  \brief returns location parameter
    */
    virtual double getLocation() = 0;

    /**  \brief returns scale parameter
    */
    virtual double getScale() = 0;

    /**  \brief returns shape parameter
    */
    virtual double getShape() = 0;
    
    /**  \brief sets location parameter
    */
    virtual void setLocation(double) = 0;

    /**  \brief sets scale parameter
    */
    virtual void setScale(double) = 0;

    /**  \brief sets shape parameter
    */
    virtual void setShape(double) = 0;

    /** \brief virtual copy constructor
    */
    virtual ProbabilityDistribution* clone() const;

    /** \brief destructor
    */
    virtual ~ScaleLocationDistribution(){};
  private:
    
  };
  
} // namespace julian

#endif
