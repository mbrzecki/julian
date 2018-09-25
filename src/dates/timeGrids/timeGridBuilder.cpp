#include <dates/timeGrids/timeGridBuilder.hpp>

namespace julian {

  /** \brief builds TimeGrid
   *
   * The method builds TimeGrid on the basis of provided inputs.
   */
  BuildTimeGrid::operator TimeGrid() {
    std::vector<double> t = discretizer_->operator()(start_date_, end_date_,yf_);
    return TimeGrid(start_date_, end_date_, t);
  }

  /** \brief provides start date
   * 
   */
  BuildTimeGrid& BuildTimeGrid::setStartDate(const Date& date) {
    start_date_ = date;
    return *this;
  }

  /** \brief provides end date
   * 
   */
  BuildTimeGrid& BuildTimeGrid::setEndDate(const Date& date) {
    end_date_ = date;
    return *this;
  }

  /** \brief provides year fraction
   * 
   */
  BuildTimeGrid& BuildTimeGrid::setYearFraction(const SmartPointer<YearFraction> yf) {
    yf_ = yf;
    return *this;
  }

  /** \brief provides discretization algorithm
   * 
   */
  BuildTimeGrid& BuildTimeGrid::setDiscretization(const SmartPointer<TimeDiscretization>& discretizer) {
    discretizer_ = discretizer;
    return *this;
  }
}  // namespace julian
