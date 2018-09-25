#ifndef JULIAN_TIMEDISCRETIZATION_HPP
#define JULIAN_TIMEDISCRETIZATION_HPP

#include <vector>
#include <dates/date.hpp>
#include <dates/yearFractions/yearFraction.hpp>
#include <utils/smartPointer.hpp>

namespace julian {

  
  /**
   * @file   timeDiscretization.hpp
   * @brief  File contains definition of TimeDiscretization class.
   */

  /** \ingroup timegrids
   *  \brief Class implements a TimeDiscretization object.
   *
   *  Class implements an interface of time discretization algorithms. 
   *
   */
  
  class TimeDiscretization {
  public:
    TimeDiscretization(){};

    /** \brief discretize the time interval
     *
     * Method discretize the time interval determined by two dates. 
     */
    virtual std::vector<double> operator()(Date , Date, SmartPointer<YearFraction>) const = 0;

    /** \brief Virtual copy constructor
     */
    virtual TimeDiscretization* clone() const = 0;

    /** \brief Destructor
     */
    virtual ~TimeDiscretization(){};
  };
}
#endif
