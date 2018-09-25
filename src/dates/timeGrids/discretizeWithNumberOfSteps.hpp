#ifndef JULIAN_DISCRETIZEWITHNUMBEROFSTEPS_HPP
#define JULIAN_DISCRETIZEWITHNUMBEROFSTEPS_HPP

#include <dates/timeGrids/timeDiscretization.hpp>
#include <dates/tenor.hpp>

namespace julian {

  /**
   * @file   discretizeWithNumberOfSteps.hpp
   * @brief  File contains definition of DiscretizeWithNumberOfSteps class.
   */

  /** \ingroup timegrids
   *  \brief Discretizes the time interval into predefined number of periods .
   *
   * Class discretizes the time interval into predefined number of periods
   */

  class DiscretizeWithNumberOfSteps: public TimeDiscretization {
  public:
    /** \brief Constructor
     */
    explicit DiscretizeWithNumberOfSteps(int n): n_(n){}
    virtual std::vector<double> operator()(Date , Date, SmartPointer<YearFraction>) const;
    virtual DiscretizeWithNumberOfSteps* clone() const;
    virtual ~DiscretizeWithNumberOfSteps(){};
  private:
    int n_; /*!< \brief Number of grid nodes. */   
  };
  
}  // namespace julian
#endif
