#ifndef JULIAN_PROBABILITYDISTRIBUTION_HPP
#define JULIAN_PROBABILITYDISTRIBUTION_HPP

#include <vector>

namespace julian {

  /**
   * @file   probabilityDistribution.hpp
   * @brief  File contains interface of random variables.
   */
  
  /** \ingroup distributions
   *  
   * \brief Class implements an interface of random number distribution.
   *
   *
   * To define probability distribution we will use:
   *
   * 1) Cumulative distribution function of random variable X 
   *
   *   \f[CDF_{X}(t) = Pr(X < t)\f]
   *
   * 2) Probability distribution function of random variable X 
   * 
   *  \f[PDF_{X}(t) = \frac{d CDF_{X}(t)}{dt}\f]
   *
   */ 
  class ProbabilityDistribution  {
  public:
    /** \brief calculates value of Cumulative Distribution Function
    */
    virtual double CDF(double) = 0;

    /** \brief calculates value of Probability Distribution Function
    */
    virtual double PDF(double) = 0;

    /**  \brief calculates quantile
    */
    virtual double invCDF(double) = 0;

    /**  \brief estimates parameters of random variables 
    */
    virtual void estimate(std::vector<double>) = 0;

    /**  \brief returns mean 
     */
    virtual double mean() = 0;

    /**  \brief returns variance 
     */
    virtual double variance() = 0;
    
    /** \brief virtual copy constructor
    */
    virtual ProbabilityDistribution* clone() const;

    /** \brief destructor
    */
    virtual ~ProbabilityDistribution(){};
  private:
    
  };
}

#endif
