#include <mathematics/distributions/uniformDistribution.hpp>
#include <mathematics/statistics/descriptiveStatistics.hpp>
#include <cmath>
namespace julian {

  /** \brief Constructor
   *
   * Constructor requires parametrization of random variables
   */
  UniformDistribution::UniformDistribution(double A, double B): A_(A), B_(B) {}

  /** \brief calculates value of Cumulative Distribution Function
   * 
   * \f[CDF_{X}(x) =   \begin{cases} 0 & \quad \text{if } x < A \\ \frac{x-A}{B-A}  & \quad \text{if } x \in [A,B) \\ 1 & \quad \text{if } x > B  \end{cases} \f]
   */
  double UniformDistribution::CDF(double x) {
    if (x > A_ && x < B_) {
      return (x - A_) / (B_ - A_);
    } else if (x < A_) {
      return 0.0;
    }
    return 1.0;
  }

  /** \brief calculates value of Probability Distribution Function
   * 
   * \f[CDF_{X}(x) =   \begin{cases} 0 & \quad \text{if } x < A \\ \frac{x-A}{B-A}  & \quad \text{if } x \in [A,B) \\ 1 & \quad \text{if } x > B  \end{cases} \f]
   */
  double UniformDistribution::PDF(double x) {
    if (x > A_ && x < B_) {
      return 1.0 / (B_ - A_);
    }
    return 0.0;
  }

  /**  \brief calculates quantile
   */
  double UniformDistribution::invCDF(double p) {
    return A_ + p * (B_ - A_);
  }

  /**  \brief estimates parameters  using Moment Matching Estimation
   *
   * \f[\begin{array}{rcr} a &  = \hat{\mu} - \sqrt{3}*\hat{\sigma} \\ 
   *    b &  = \hat{\mu} + \sqrt{3}*\hat{\sigma} \end{array}\f]
   *
   */
  void UniformDistribution::estimate(std::vector<double> data) {
    auto m = stats::mean(data);
    auto s = stats::stdDev(data);

    A_ = m - sqrt(3) * s;
    B_ = m + sqrt(3) * s;    
  }

  /** \brief sets location
   *
   * Parameter **A** is location of uniform distribution
   */
  void UniformDistribution::setLocation(double l) {
    auto scale = B_ - A_;
    A_ = l;
    B_ = A_ + scale;
  }
  void UniformDistribution::setScale(double s) {
    B_ = A_ + s;
  }

  /** \brief This method does nothing 
   *
   * uniform distribution is not parametrized by shape parameter
   */
  void UniformDistribution::setShape(double) {
  }
  /** \brief Virtual copy constructor
   */
  UniformDistribution* UniformDistribution::clone() const {
    return new UniformDistribution(*this);
  }

  /**  \brief returns mean 
   */
  double UniformDistribution::mean() {
    return (A_ + B_) * 0.5;
  }

  /**  \brief returns variance
   */
  double UniformDistribution::variance() {
    return std::pow(B_ - A_, 2)/ 12.0;
  }

  /**  \brief returns location
   */ 
  double UniformDistribution::getLocation() {
    return A_;
  }
  /**  \brief returns location
   */ 
  double UniformDistribution::getScale() {
    return B_ - A_;
  }
  /**  \brief returns shape
   *
   * Method returns NAN as uniform distribution is not parametrized with shape
   */ 
  double UniformDistribution::getShape() {
    return NAN;
  }
  
} // namespace julian
