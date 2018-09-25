#ifndef JULIAN_ACTACTAFB_HPP
#define JULIAN_ACTACTAFB_HPP

#include <dates/yearFractions/yearFraction.hpp>

namespace julian {

  /**
   * @file   ActActAFB.hpp
   * @brief  File contains definition of ACTACT AFB year fraction.
   */
  
  /** \ingroup yearfraction
   * \brief 
   * The class encapsulates the ACTACT AFB year fraction convention.
   *
   * In case of AFB (Association Francaise des Banques) convention the year fraction is calculated with formula:
   * \f[YearFraction(date_1,date_2) = \frac{\textrm{Actual number of days}}{\textrm{Denominator}}\f]
   * Denominator is equal 366 if period \f$(date_1,date_2)\f$ contains 29th of February and 365 otherwise.
   * \see \cite OGguide
   *
   */

  
  class ActActAFB: public YearFraction {
  public:
    ActActAFB(){};
    virtual double operator()(const Date&,const Date&) const;
    virtual ActActAFB* clone() const;
    virtual std::string info() const;
    virtual ~ActActAFB(){};
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
