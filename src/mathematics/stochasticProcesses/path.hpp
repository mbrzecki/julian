#ifndef JULIAN_PATH_HPP
#define JULIAN_PATH_HPP

#include <vector>
#include <dates/timeGrids/timeGrid.hpp>

namespace julian {  /**
   * @file   path.hpp
   * @brief  File contains implementation of Path object.
   */
  /** \ingroup stochasticProcesses
      \brief Path is a series of real numbers indexed with time. In general, it is identical with a series of time.
      
      Path consists of two components: TimeGrid and vector of doubles corresponding to time grid.  

  */
  
  class Path {
  public:
    Path(){};
    Path(TimeGrid , std::vector<double> );
    std::vector<double> getValues();
  private:
    std::vector<double> values_; /*!< \brief Vector holding data points*/
    TimeGrid time_; /*!< \brief Time points indexing the values hold in values_ vector.*/
  };
}  // namespace julian

#endif
