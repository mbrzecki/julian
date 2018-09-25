#ifndef JULIAN_NORMALDISTRIBUTION_HPP
#define JULIAN_NORMALDISTRIBUTION_HPP

#include <mathematics/distributions/scaleLocationDistribution.hpp>
namespace julian {

  /**
   * @file   normalDistribution.hpp
   * @brief  File contains implementation of normal distribution.
   */
  
  /** \ingroup distributions
   *
   * \brief Class implements Normal Distribution
   *
   * Normal distribution is defined by:
   *
   *1) Cumulative distribution function of normal random variable X 
   *
   *  \f[CDF_{X}(t) = \int^{t}_{-\infty} \frac{1}{\sqrt{2\pi \sigma^{2}}}e^{-\frac{(x-\mu )^{2}}{2\sigma ^{2}}} dx \f]
   *
   *2) Probability distribution function of normal random variable X 
   *
   *  \f[PDF_{X}(t) = \frac{1}{\sqrt{2\pi \sigma^{2}}}e^{-\frac{(x-\mu )^{2}}{2\sigma ^{2}}} \f]
   *
   *3) Parameters
   *
   * **Location**
   *      
   *  Mean or expectation of the distribution
   *
   *  **Scale**
   *
   *  Standard deviation of the distribution
   *
   */ 

  
  class NormalDistribution: public ScaleLocationDistribution {
  public:
    NormalDistribution(): m_(0.0), s_(1.0) {}
    NormalDistribution(double m, double s);
    /*! \name Probability Distribution Interface
     */
    //@{
    double CDF(double);
    double PDF(double);
    double invCDF(double);
    
    double mean();
    double variance();
    void estimate(std::vector<double>);
    //@}
    /*! \name Scale Location Interface
     */
    //@{
    double getLocation();
    double getScale();
    double getShape();
    

    void setLocation(double);
    void setScale(double);
    void setShape(double);
    //@}
    
    NormalDistribution* clone() const;
    
    ~NormalDistribution();
  private:
    double m_; /*!< \brief Mean (location parameter)*/
    double s_; /*!< \brief Standard deviation  (scale parameter)*/
  };
}
#endif
