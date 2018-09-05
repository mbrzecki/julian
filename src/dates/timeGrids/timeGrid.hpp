#ifndef JULIAN_TIMEGRID_HPP
#define JULIAN_TIMEGRID_HPP

#include <dates/date.hpp>
#include <vector>

namespace julian {

  /**
   * @file   timeGrid.hpp
   * @brief  File contains definition of TimeGrid class.
   */

  /** \ingroup timegrids
   *  \brief Class implements a TimeGrid object.
   *
   *  Time grid is used as an element of Path class. Path class is representing discretize stochastic process and it is used in Monte Carlo simulations. 
   *
   */
  
  class TimeGrid {
  public:
    TimeGrid(){};
    TimeGrid(Date start_date, Date end_date, std::vector<double> time);
    double get(int i) const;
    double getDiff(int i) const;
    unsigned int getSize() const;
    std::vector<double> getGrid() const;
  
  private:
    Date start_date_;           /*!< \brief Date determining beginning of the interval. */
    Date end_date_;             /*!< \brief Date determining ending of the interval.*/
    std::vector<double> time_;  /*!< \brief Real numbers representing nodes of time greed.*/    
  };
} // julian

#endif
