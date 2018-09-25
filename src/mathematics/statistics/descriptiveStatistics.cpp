#include <mathematics/statistics/descriptiveStatistics.hpp>
#include <iostream>

namespace julian {
  namespace stats {

    /** \ingroup statistics
     * 
     * \fn  void descriptiveStatistics(const std::vector<double>& data);
     * \brief Procedure prints the basic statistical measures.
     *
     * \param data Vector of doubles representing data.
     * 
     */
    void descriptiveStatistics(const std::vector<double>& data) {
      std::cout << "Count:\t\t"    << data.size();
      std::cout << "\nMean:\t\t"   << mean(data);
      std::cout << "\nMedian:\t\t" << median(data);
      std::cout << "\nStdDev:\t\t" << stdDev(data);
      std::cout << "\nAbsDev:\t\t" << absDev(data);
      std::cout << "\nSkew:\t\t"   << skew(data);
      std::cout << "\nKurtosis:\t" << kurtosis(data);
      std::cout << "\nMin:\t\t"    << min(data);
      std::cout << "\nMax:\t\t"    << max(data);
      std::cout << "\np1:\t\t"     << percentile(data, 0.01);
      std::cout << "\np5:\t\t"     << percentile(data, 0.05);
      std::cout << "\nQ1:\t\t"     << percentile(data, 0.25);
      std::cout << "\nQ2:\t\t"     << percentile(data, 0.50);
      std::cout << "\nQ3:\t\t"     << percentile(data, 0.75);
      std::cout << "\np95:\t\t"    << percentile(data, 0.95);
      std::cout << "\np99:\t\t"    << percentile(data, 0.99);
    }
    
  }
}
