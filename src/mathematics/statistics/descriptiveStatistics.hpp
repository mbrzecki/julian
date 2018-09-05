#ifndef JULIAN_DESCRIPTIVESTATISTICS_HPP
#define JULIAN_DESCRIPTIVESTATISTICS_HPP

#include <vector>
#include <algorithm>
#include <boost/assert.hpp>
#include <gsl/gsl_statistics.h>

namespace julian {
  namespace stats {

  /**
   * @file   descriptiveStatistics.hpp
   * @brief  File contains statistical tools.
   */

    void descriptiveStatistics(const std::vector<double>&);

    /** \ingroup statistics
     * 
     * \fn double mean(const std::vector<double>& data)
     * \brief Function calculates mean
     *
     * Function calculates mean:
     * \f[\mu = {1 \over N} \sum x_i\f]
     *
     * \param data Vector of doubles representing data.
     * \return mean \f$\mu\f$
     */
    inline double mean(const std::vector<double>& data) {
      return gsl_stats_mean(&data.front(), 1, data.size());
    }

    /** \ingroup statistics
     * 
     * \fn double variance(const std::vector<double>& data)
     * \brief Function calculates variance
     *
     * Function calculates :
     * \f[{\sigma}^2 = {1 \over (N-1)} \sum (x_i - {\mu})^2\f]
     * where
     * \f[\mu = {1 \over N} \sum x_i\f]
     *
     * \param data Vector of doubles representing data.
     * \return variance \f${\sigma}^2\f$
     */
    inline double variance(const std::vector<double>& data) {
      return gsl_stats_variance(&data.front(), 1, data.size());
    }

    /** \ingroup statistics
     * 
     * \fn double variance(const std::vector<double>& data,const double mean) 
     * \brief Function calculates variance using the provided mean 
     *
     * Function calculates variance using the provided mean: 
     * \f[{\sigma}^2 = {1 \over (N)} \sum (x_i - mean)^2\f]
     * 
     * \param data Vector of doubles representing data.
	 * \param mean Mean of the population	
     * \return variance \f${\sigma}^2\f$
     */
    inline double variance(const std::vector<double>& data,const double mean) {
      return gsl_stats_variance_with_fixed_mean(&data.front(), 1, data.size(), mean);
    }

    /** \ingroup statistics
     * 
     * \fn double stdDev(const std::vector<double>& data)
     * \brief Function calculates standard deviation
     *
     * Function calculates standard deviation :
     * \f[{\sigma} = \sqrt{{1 \over (N-1)} \sum (x_i - {\mu})^2}\f]
     * where
     * \f[\mu = {1 \over N} \sum x_i\f]
     *
     * \param data Vector of doubles representing data.
     * \return Standard deviation \f${\sigma}\f$
     */
    inline double stdDev(const std::vector<double>& data) {
      return gsl_stats_sd(&data.front(), 1, data.size());
    }

    /** \ingroup statistics
     * 
     * \fn double stdDev(const std::vector<double>& data,const double mean)
     * \brief Function calculates standard deviation using the provided mean 
     *
     * Function calculates standard deviation using the provided mean: 
     * \f[{\sigma} = \sqrt{{1 \over (N)} \sum (x_i - {\mu})^2}\f]
     *
     * \param data Vector of doubles representing data.
	 * \param mean Mean of the population	
     * \return Standard deviation \f${\sigma}\f$
     */
    inline double stdDev(const std::vector<double>& data,const double mean) {
      return gsl_stats_sd_with_fixed_mean(&data.front(), 1, data.size(), mean);
    }

    /** \ingroup statistics
     * 
     * \fn  double absDev(const std::vector<double>& data)
     * \brief Function calculates absolute deviation
     *
     * Function calculates absolute deviation :
     * 
     * \f[absdev  = {1 \over N} \sum |x_i - {\mu}|\f]
     * where
     * \f[\mu = {1 \over N} \sum x_i\f]
     * \param data Vector of doubles representing data.
     * \return Absolute deviation
     */
    inline double absDev(const std::vector<double>& data) {
      return gsl_stats_absdev(&data.front(), 1, data.size());
    }

    /** \ingroup statistics
     * 
     * \fn  double absDev(const std::vector<double>& data, const double mean)
     * \brief Function calculates absolute deviation using the provided mean 
     *
     * Function calculates absolute deviation :
     * 
     * \f[absdev  = {1 \over N} \sum |x_i - {mean}|\f]
     *
     * \param data Vector of doubles representing data.
	 * \param mean Mean of the population	
     * \return Absolute deviation
     */
    inline double absDev(const std::vector<double>& data, const double mean) {
      return gsl_stats_absdev_m(&data.front(), 1, data.size(), mean);
    }

    /** \ingroup statistics
     * 
     * \fn double skew(const std::vector<double>& data)
     * \brief Function calculates skew
     *
     * Function calculates skew :
     * \f[skew = {1 \over N} \sum {\left( x_i - {\mu} \over {\sigma} \right)}^3\f]
     *
     * \param data Vector of doubles representing data.
     * \return Skew
     */
    inline double skew(const std::vector<double>& data) {
      return gsl_stats_skew(&data.front(), 1, data.size());
    }

    /** \ingroup statistics
     * 
     * \fn double kurtosis(const std::vector<double>& data)
     * \brief Function calculates normalized kurtosis
     *
     * Function calculates normalized kurtosis (kurtosis that of normal distribution is 0):
     * \f[kurtosis = \left( {1 \over N} \sum  {\left(x_i - {\mu} \over {\sigma} \right)}^4  \right) - 3\f]
     *
     * \param data Vector of doubles representing data.
     * \return kurtosis
     */
    inline double kurtosis(const std::vector<double>& data) {
      return gsl_stats_kurtosis(&data.front(), 1, data.size());
    }

    /** \ingroup statistics
     * 
     * \fn double pearsonCorr(const std::vector<double>& data1,const std::vector<double>& data2)
     * \brief Function calculates Pearson correlation 
     *
     * Function calculates Pearson correlation 
     * \f[r = {cov(x, y) \over \sigma_x \sigma_y} = {{1 \over n-1} \sum (x_i -  x) (y_i -  y)
     \over \sqrt{{1 \over n-1} \sum (x_i - { x})^2} \sqrt{{1 \over n-1} \sum (y_i - { y})^2}} \f]
     *
     * \param data1 Vector of doubles representing first data.
     * \param data2 Vector of doubles representing second data.
     * \return Pearson correlation
     */
    inline double pearsonCorr(const std::vector<double>& data1,const std::vector<double>& data2) {
      BOOST_ASSERT_MSG(data1.size() == data2.size(),"Data vectors have different sizes.");
      return gsl_stats_correlation(&data1.front(), 1, &data2.front(), 1, data1.size());
    }

    /** \ingroup statistics
     * 
     * \fn double spearmanCorr(const std::vector<double>& data1,const std::vector<double>& data2)
     * \brief Function calculates Spearman  correlation 
     *
     * Function calculates Spearman correlation 
     * \f[r_{s}=1-\frac{6 \sum d_i^2}{n(n^{2}-1)} \f]
     * where:
     * \f$ d_{i}= (X_{i})- (Y_{i})\f$ is the difference between the two ranks of each observation.
     *
     * \param data1 Vector of doubles representing first data.
     * \param data2 Vector of doubles representing second data.
     * \return Spearman correlation
     */
    inline double spearmanCorr(const std::vector<double>& data1,const std::vector<double>& data2) {
      BOOST_ASSERT_MSG(data1.size() == data2.size(),"Data vectors have different sizes.");
      int n = 2 * data1.size(); 
      double* t = new double[n];
      double corr = gsl_stats_spearman(&data1.front(), 1, &data2.front(), 1, data1.size(),t);
      delete[] t;
      return corr;
    }

    /** \ingroup statistics
     * 
     * \fn double max(const std::vector<double>& data)
     * \brief Function returns the maximum value
     *
     * \param data Vector of doubles representing data.
     * \return Maximum value of numbers in data vector
     */
    inline double max(const std::vector<double>& data) {
      return gsl_stats_max(&data.front(), 1, data.size());
    }

    /** \ingroup statistics
     * 
     * \fn  double min(const std::vector<double>& data)
     * \brief Function returns the minimum value
     *
     * \param data Vector of doubles representing data.
     * \return Minimum value of numbers in data vector
     */
    inline double min(const std::vector<double>& data) {
      return gsl_stats_min(&data.front(), 1, data.size());
    }

    /** \ingroup statistics
     * 
     * \fn double median(const std::vector<double> data)
     * \brief Function returns median
     *
     * When the dataset has an odd number of elements the median is the value of element (n-1)/2. 
     * When the dataset has an even number of elements the median is the mean of the two nearest middle values, elements (n-1)/2 and n/2. 
     * Since the algorithm for computing the median involves interpolation this function always returns a floating-point number, even for integer data types.
     *
     * \param data Vector of doubles representing data.
     * \return returns median
     */
    inline double median(const std::vector<double> data) {
      auto data_(data);
      std::sort(data_.begin(),data_.end());
      return gsl_stats_median_from_sorted_data(&data_.front(), 1, data_.size());
    }

    /** \ingroup statistics
     * 
     * \fn double percentile(const std::vector<double> data,const double& q)
     * \brief Function returns a quantile 
     *
     * The quantile is found by interpolation, using the formula
     * \f[quantile = (1 - \delta) x_i + \delta x_{i+1} \f]
     * where i is \f$floor((n - 1)q)\f$ and \f$\delta = (n-1)q - i\f$.
     * 
     *
     * \param data Vector of doubles representing data.
	 * \param q quantile
     * \return  returns a q-th quantile 
     */
    inline double percentile(const std::vector<double> data,const double& q) {
      auto data_(data);
      std::sort(data_.begin(),data_.end());
      return gsl_stats_quantile_from_sorted_data(&data_.front(), 1, data_.size(), q);
    }

    /** \ingroup statistics
     * 
     * \fn double IQR(const std::vector<double>& data)
     * \brief Returns interquartile range
     *
     * Function calculates the interquartile range (IQR) which is a measure of statistical dispersion, being equal to the difference between 75th and 25th percentiles, 
     *
     * \param data Vector of doubles representing data.
     * \return Returns interquartile range
     */
    inline double IQR(const std::vector<double>& data) {
      return percentile(data, 0.75) - percentile(data, 0.25);
    }
    
  } // stats
}  // namespace julian
#endif
