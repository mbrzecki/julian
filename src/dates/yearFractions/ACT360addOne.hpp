#ifndef JULIAN_ACT360ADDONE_HPP
#define JULIAN_ACT360ADDONE_HPP

#include <dates/yearFractions/yearFraction.hpp>

namespace julian {
  
  /**
   * @file   ACT360addOne.hpp
   * @brief  File contains definition of ACT360addOne year fraction.
   */
  
  /** \ingroup yearfraction
   *  \brief 
   *  The class encapsulates the ACT360addOne year fraction convention.
   *
   * According to Act365 convention the year fraction is calculated using following formula:
   * \f[YearFraction(dates_1,date_2)  = \frac{\textrm{Actual number of days between } date_1 \textrm{ and } date_2 + 1 \textrm{ day}}{360}\f] 
   *
   */
  
  class ACT360addOne: public YearFraction {
  public:
    ACT360addOne(){};
    virtual double operator()(const Date&,const Date&) const;
    virtual ACT360addOne* clone() const;
    virtual std::string info() const;
    virtual ~ACT360addOne(){};
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
