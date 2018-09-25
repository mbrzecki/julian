#include <mathematics/distributions/normalDistribution.hpp>
#include <mathematics/statistics/descriptiveStatistics.hpp>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <vector>
#include <cmath>

namespace julian {


  /** \brief Constructor
   *
   * Constructor requires parametrization of random variables
   */

  NormalDistribution::NormalDistribution(double m, double s) {
    m_ = m;
    s_ = s;
  }

  /** \brief returns mean of distribution
   *
   */
  double NormalDistribution::mean() {
    return m_;
  }

  /** \brief returns variance of distribution
   *
   */
  double NormalDistribution::variance() {
    return s_*s_;
  }

  /** \brief returns location parameter
   *
   */
  double NormalDistribution::getLocation() {
    return m_;
  }

  /** \brief returns scale
   *
   *
   */
  double NormalDistribution::getScale() {
    return s_;
  }

  /** \brief returns shape
   *
   * Method returns nan as the normal distribution is not parametrized with shape parameter
   */
  double NormalDistribution::getShape() {
    return NAN;
  }

  /** \brief sets mean (location parameter)
   *
   */
  void NormalDistribution::setLocation(double input) {
    m_ = input;
  }

  /** \brief sets standard deviation
   *
   */
  void NormalDistribution::setScale(double input) {
    s_ = input;
  }

  /** \brief This method does nothing 
   *
   * normal distribution is not parametrized by shape parameter
   */
  void NormalDistribution::setShape(double) {
  }

  /** \brief calculates value of Probability Distribution Function
  */
  double NormalDistribution::CDF(double x) {
    return gsl_cdf_gaussian_P(x-m_, s_);
  }

  /** \brief calculates value of Probability Distribution Function
   */
  double NormalDistribution::PDF(double x) {
    return gsl_ran_gaussian_pdf(x-m_, s_);
  }

  /**  \brief calculates quantile
   */
  double NormalDistribution::invCDF(double x) {
    return m_ + gsl_cdf_gaussian_Pinv(x, s_);
  }

  /**  \brief estimates mean and standard deviation using Moment Matching Estimation
   */
  void NormalDistribution::estimate(std::vector<double> data) {
    m_ = stats::mean(data);
    s_ = stats::stdDev(data);
  }

  /** \brief virtual copy constructor
   */
  NormalDistribution* NormalDistribution::clone() const {
    return new NormalDistribution(*this);
  }

  /** \brief destructor
   */
  NormalDistribution::~NormalDistribution() {
  }
}  // namespace julian
