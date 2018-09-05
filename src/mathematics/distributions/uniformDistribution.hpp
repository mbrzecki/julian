#ifndef JULIAN_UNIFORMDISTRIBUTION_HPP
#define JULIAN_UNIFORMDISTRIBUTION_HPP

#include <mathematics/distributions/scaleLocationDistribution.hpp>

namespace julian {
  /**
   * @file   uniformDistribution.hpp
   * @brief  File contains implementation of uniform distribution.
   */
  
  /** \ingroup distributions
   *
   * \brief Class implements Uniform Distribution
   *
   * Uniform probability distribution is defined by the two parameters, **A** and **B**, which are its minimum and maximum values.
   *
   * 1) Cumulative distribution function of normal random variable X 
   *
   *  \f[CDF_{X}(x) =   \begin{cases} 0 & \quad \text{if } x < A \\ \frac{x-A}{B-A}  & \quad \text{if } x \in [A,B) \\ 1 & \quad \text{if } x > B  \end{cases} \f]
   *
   *2) Probability distribution function of normal random variable X 
   *
   *  \f[PDF_{X}(t) = \begin{cases} \frac{1}{B-A}  \quad \text{if } x \in [A,B] \\ 0 \quad \text{ otherwise} \end{cases}\f]
   *
   *3) Parameters
   *
   * **A** is minimum value
   *
   * **B** is maximum value
   * 
   *  **Location**
   *
   *  **A** is a location parameter. 
   *
   *  **Scale**
   *
   *  Scale is difference of **B** and **A**
   *
   */ 

  
  class UniformDistribution: public ScaleLocationDistribution {
  public:
   /** \brief Constructor
   *
   * Set location to 0 and scale to 1
   */   
    UniformDistribution(): A_(0.0), B_(1.0) {}
    UniformDistribution(double A,double B);   
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
    
    UniformDistribution* clone() const;
    
    ~UniformDistribution(){};
  private:
    double A_; /*!< \brief Minimum value (location parameter) */
    double B_; /*!< \brief Maximum value (scale parameter)*/
  };
} // namespace julian
#endif
