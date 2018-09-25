#ifndef JULIAN_INTERESTRATE_HPP
#define JULIAN_INTERESTRATE_HPP

#include <interestRates/compounding.hpp>
#include <cmath>
#include <dates/_all_dates.hpp>
#include <utils/smartPointer.hpp>
#include <dates/yearFractions/yearFraction.hpp>

namespace julian {

/**
 * @file   interestRate.hpp
 * @brief  File contains definition of InterestRate class.
 */

/** \ingroup  interestRate
 *  \brief The class implements the concept of interest rate. 
 *
 * Class represent the interest rate concept. It encapsulates compounding algebra and year fraction conventions. It allows to calculate capitalization of capital and coupon paid by investment. 
 * It also enables to calculate discount factors, zero coupon rates and forward rates if appropriate data provided.
 *   
 */

  class InterestRate {
  public:
    InterestRate();
    InterestRate(const SmartPointer<Compounding>& compounding,const SmartPointer< YearFraction>& year_fraction);

    double capitalization(Date date1,Date date2, double interest_rate) const;
    double DF(Date date1,Date date2, double interest_rate) const;
    double coupon(Date date1,Date date2,double interest_rate) const;
    double fwdRate(Date date1,Date date2,double df1, double df2) const;
    double zcRate(Date date1,Date date2, double df) const;
    double yf(Date date1,Date date2) const;
  
    InterestRate* clone() const;
    ~InterestRate(){};
  
    friend std::ostream& operator<<(std::ostream& s, InterestRate& r);
    friend class boost::serialization::access;

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & ar,  const unsigned int) {
      ar & BOOST_SERIALIZATION_NVP(year_fraction_);
      ar & BOOST_SERIALIZATION_NVP(compounding_);
    }
  private: 
    SmartPointer<Compounding> compounding_; //!<@brief Attribute maintaining compounding convention
    
    /*!<@details This is the compounding convention used by interest rate class. It is provided during the construction of the object*/
    SmartPointer<YearFraction> year_fraction_; //!<@brief Attribute maintaining year fraction convention
    /*!<@details This is the year fraction convention used by interest rate class. It is provided during the construction of the object*/
};
}
#endif
