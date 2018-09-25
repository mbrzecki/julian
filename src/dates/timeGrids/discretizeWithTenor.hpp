#ifndef JULIAN_DISCRETIZEWITHTENOR_HPP
#define JULIAN_DISCRETIZEWITHTENOR_HPP

#include <dates/timeGrids/timeDiscretization.hpp>
#include <dates/tenor.hpp>

namespace julian {

  
  /**
   * @file   discretizeWithTenor.hpp
   * @brief  File contains definition of DiscretizeWithTenor class.
   */

  /** \ingroup timegrids
   *  \brief Discretize the time interval in such way that distance between each nodes is equal to tenor provided.
   *
   * Class discretize the time interval in such way that distance between each nodes is equal to tenor provided.
   */
  
  class DiscretizeWithTenor: public TimeDiscretization {
  public:
    /** \brief Constructor
     */
    explicit DiscretizeWithTenor(Tenor tenor): tenor_(tenor){};
    virtual std::vector<double> operator()(Date start_date, Date end_date, SmartPointer<YearFraction> yf) const;
    virtual DiscretizeWithTenor* clone() const;
    virtual ~DiscretizeWithTenor(){};
  private:
    Tenor tenor_;  /*!< \brief Discretization tenor */
  };
} // namespace julian
#endif
