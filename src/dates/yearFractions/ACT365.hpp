#ifndef JULIAN_ACT365_HPP
#define JULIAN_ACT365_HPP

#include <dates/yearFractions/yearFraction.hpp>

namespace julian {
  
  /**
   * @file   ACT365.hpp
   * @brief  File contains definition of ACT365 year fraction.
   */
  
  /** \ingroup yearfraction
   *  \brief The class encapsulates the ACT365 year fraction convention.
   *
   * According to ACT365 convention the year fraction is calculated using following formula:
   * \f[YearFraction(dates_1,date_2)  = \frac{\textrm{Actual number of days between } date_1 \textrm{ and } date_2}{365}\f] 
   * */
  
  class ACT365: public YearFraction {
  public:
    ACT365(){};
    virtual double operator()(const Date&,const Date&) const;
    virtual ACT365* clone() const;
    virtual ~ACT365(){};
    virtual std::string info() const;
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
