#ifndef JULIAN_ONEYF_HPP
#define JULIAN_ONEYF_HPP

#include <dates/yearFractions/yearFraction.hpp>

namespace julian {

  /**
   * @file   OneYF.hpp
   * @brief  File contains definition of 1/1 year fraction.
   */
  
  /** \ingroup yearfraction
   *  \brief The class encapsulates the 1/1 year fraction convention.
   *
   * According to 1/1 convention the year fraction is always 1.
   */


  
  class OneYF: public YearFraction {
  public:
    OneYF(){};
    virtual double operator()(const Date&,const Date&) const;
    virtual OneYF* clone() const;
    virtual ~OneYF(){};
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
