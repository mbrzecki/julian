#ifndef JULIAN_FRACTIONRATE_HPP
#define JULIAN_FRACTIONRATE_HPP

#include <interestRates/compounding.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace julian {
  
  /**
   * @file   fractionRate.hpp
   * @brief  File contains definition of FractionRate class.
   */
  
  /** \ingroup interestRate
   *  \brief The class encapsulates the fraction rate compounding method.
   *
   * Object of this class implements simple interest rate compounding. Using simple compounding the future value and interest rate are calculated according to formulae:
   * \f[\textrm{Future Value} = (1 + \frac{\textrm{Interest Rate}}{ \textrm{frequency}} )^{\textrm{frequency} \times \textrm{Accrual Time}}\f] 
   * \f[\textrm{Interest Rate} = (\sqrt[\textrm{frequency}]{\textrm{Future Value}}-1) \times frequency\f]
   *
   */
  
  class FractionRate: public Compounding {
  public:
    /** \brief Constructor
     */
    FractionRate(double input = 1.0): frequency_(input){};
    
    virtual double getCapitalization(double interest_rate, double accrual_time) const;
    virtual double getRate(double future_value,double accrual_time) const;
    virtual std::string info() const;
    
    virtual FractionRate* clone() const;
    virtual ~FractionRate(){};
    
    friend std::ostream& operator<<(std::ostream& s, FractionRate& c);
    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & ar, const unsigned int){
      boost::serialization::base_object<Compounding>(*this);
      ar & BOOST_SERIALIZATION_NVP(frequency_); 
    }

    double frequency_; /*!< \brief Compounding frequency used by interest rate */
  };
}
#endif
