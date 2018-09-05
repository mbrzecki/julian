#ifndef JULIAN_ACTACTISDA_HPP
#define JULIAN_ACTACTISDA_HPP

#include <dates/yearFractions/yearFraction.hpp>

namespace julian {

  /**
   * @file   ActActISDA.hpp
   * @brief  File contains definition of ACTACT ISDA year fraction.
   */
  
  /** \ingroup yearfraction
   * \brief 
   * The class encapsulates the ActAct USDAyear fraction convention.
   *
   * With ISDA convention (International Swaps and Derivative Association) the year fraction is calculated according to the formula:
   * \f[YearFraction(date_1,date_2) = \frac{\textrm{Number of days in non-leap year}}{365} + \frac{\textrm{Number of days in leap year}}{366}\f]
   */

  class ActActISDA: public YearFraction {
  public:
    ActActISDA(){};
    virtual double operator()(const Date&,const Date&) const;
    virtual ActActISDA* clone() const;
    virtual std::string info() const;
    virtual ~ActActISDA(){};
    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int){
      boost::serialization::base_object<YearFraction>(*this);
    }
  };
}
#endif
