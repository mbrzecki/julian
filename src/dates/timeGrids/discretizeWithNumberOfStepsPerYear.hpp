#ifndef JULIAN_DISCRETIZEWITHNUMBEROFSTEPSPERYEAR_HPP
#define JULIAN_DISCRETIZEWITHNUMBEROFSTEPSPERYEAR_HPP

#include <dates/timeGrids/timeDiscretization.hpp>
#include <dates/tenor.hpp>

namespace julian {

  /**
   * @file   discretizeWithNumberOfStepsPerYear.hpp
   * @brief  File contains definition of DiscretizeWithNumberOfStepsPerYear class.
   */

  /** \ingroup timegrids
   *  \brief Discretize the time interval in a way that each year have the same number of time steps .
   *
   * Discretize the time interval in a way that each year have the same number of time steps 
   */

  
  class DiscretizeWithNumberOfStepsPerYear: public TimeDiscretization {
  public:
    /** \brief Constructor
     */
    explicit DiscretizeWithNumberOfStepsPerYear(int n): n_(n){};
    virtual std::vector<double> operator()(Date start_date, Date end_date, SmartPointer<YearFraction> yf) const;
    virtual DiscretizeWithNumberOfStepsPerYear* clone() const;
    virtual ~DiscretizeWithNumberOfStepsPerYear(){};
  private:
    int n_; /*!< \brief Number of grid nodes per year. */  
  };
}
#endif
