#ifndef JULIAN_US30360_HPP
#define JULIAN_US30360_HPP

#include <dates/yearFractions/yearFraction.hpp>

namespace julian {

  /**
   * @file   US30360.hpp
   * @brief  File contains definition of US30360 year fraction.
   */
  
  /** \ingroup yearfraction
   *  \brief The class encapsulates the 30/360 US year fraction convention.
   *
   * According to 30/360 US convention the year fraction is calculated using following formula:
   * \f[YearFraction(dates_1,date_2)  = \frac{360(Y_2 - Y_1)+30(M_2-M_1)+(D_2-D_1)}{360}\f] 
   * where:
   * * \f$Y_i\f$ is number of years in \f$date_i\f$,
   * * \f$M_i\f$ is number of months in \f$date_i\f$,
   * * \f$D_i\f$ is number of days in \f$date_i\f$. 
   *
   * Additionally the following adjustment is applied:
   * * If D_1 is 31, then change D_1 to 30.
   * * If D_2 is 31 and D_1 is 30 or 31, then change D_2 to 30
   */
  
  class US30360: public YearFraction {
  public:
    US30360(){};
    virtual double operator()(const Date&,const Date&) const;
    virtual US30360* clone() const;
    virtual ~US30360(){};
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
