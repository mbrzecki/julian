
#ifndef JULIAN_TIMEGRIDBUILDER_HPP
#define JULIAN_TIMEGRIDBUILDER_HPP

#include <dates/timeGrids/timeGrid.hpp>
#include <dates/date.hpp>
#include <dates/tenor.hpp>
#include <dates/timeGrids/timeDiscretization.hpp>

namespace julian {

  /**
   * @file   timeGridBuilder.hpp
   * @brief  File contains definition of BuildTimeGrid class.
   */

  /** \ingroup timegrids
   *  \brief Class implements a builder of TimeGrid object.
   *
   *  Class implements the builder pattern that encapsulates the process of construction of time grid. Time grid is build basing on dates provided using the algorithm implemented in TimeDiscretization. 
   *
   */

  class BuildTimeGrid {
  public:
    BuildTimeGrid(){};

    BuildTimeGrid& setStartDate(const Date&);
    BuildTimeGrid& setEndDate(const Date&);
    BuildTimeGrid& setYearFraction(const SmartPointer<YearFraction> yf_);
    BuildTimeGrid& setDiscretization(const SmartPointer<TimeDiscretization>& d_);
  
    operator TimeGrid();
  private:
    Date start_date_;           /*!< \brief Date determining beginning of the interval. */
    Date end_date_;             /*!< \brief Date determining ending of the interval.*/
    SmartPointer<YearFraction> yf_; /*!< \brief Year Fraction converting time interval into real number interval.*/ 
    SmartPointer<TimeDiscretization> discretizer_; /*!< \brief Interface of discretization algorithm.*/
  };
}
#endif
