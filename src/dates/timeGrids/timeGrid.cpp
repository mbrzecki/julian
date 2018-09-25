#include <dates/timeGrids/timeGrid.hpp>
#include <vector>

namespace julian {

  /** \brief Constructor
   * 
   */
  TimeGrid::TimeGrid(Date start_date, Date end_date, std::vector<double> time) {
    start_date_ =  start_date;
    end_date_   = end_date;
    time_ = time;
  }

  /** \brief returns time grid 
   */
  std::vector<double> TimeGrid::getGrid() const {
    return time_;
  }

  /** \brief returns i-th time
   */
  double TimeGrid::get(int i) const {
    return time_.at(i);
  }

  /** \brief returns difference between i-th and (i-1)-th time
   */
  double TimeGrid::getDiff(int i) const {
    return time_.at(i) - time_.at(i-1);
  }
  
  /** \brief returns number of nodes
   * 
   */
  unsigned int TimeGrid::getSize() const {
    return time_.size();
  }
}  // namespace julian
