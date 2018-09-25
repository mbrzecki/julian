#ifndef JULIAN_ACT360_HPP
#define JULIAN_ACT360_HPP

#include <dates/yearFractions/yearFraction.hpp>

namespace julian {

  /**
   * @file   ACT360.hpp
   * @brief  File contains definition of ACT360 year fraction.
   */
  
  /** \ingroup yearfraction
   *  \brief 
   *  The class encapsulates the ACT360 year fraction convention.
   *
   * According to Act360 convention the year fraction is calculated using following formula:
   * \f[YearFraction(dates_1,date_2) = \frac{\textrm{Actual number of days between } date_1 \textrm{ and } date_2}{360}\f].
   */

  class ACT360: public YearFraction {
  public:
    ACT360(){};
    virtual double operator()(const Date&,const Date&) const;
    virtual ACT360* clone() const;
    virtual std::string info() const;
    virtual ~ACT360(){};
    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int){
      boost::serialization::base_object<YearFraction>(*this);
    }
  };

} // namespace julian

#endif
