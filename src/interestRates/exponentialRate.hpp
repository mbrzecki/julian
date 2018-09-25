#ifndef JULIAN_EXPONENTIALRATE_HPP
#define JULIAN_EXPONENTIALRATE_HPP

#include <interestRates/compounding.hpp>

namespace julian {

  /**
   * @file   exponentialRate.hpp
   * @brief  File contains definition of ExponentialRate class.
   */
  
  /** \ingroup  interestRate
   *  \brief 
   *  The class encapsulates the exponential rate compounding method.
   *
   * Object of this class implements exponential interest rate compounding. Using exponential compounding the future value and interest rate are calculated according to formulae:
   * \f[\textrm{Future Value} = e^{\textrm{Interest Rate} \times \textrm{Accrual Time}}\f] 
   * \f[\textrm{Interest Rate} = \frac{ln(\textrm{Future Value})}{\textrm{Accrual Time}}\f] 
   *
   */

  class ExponentialRate: public Compounding {
  public:
    ExponentialRate(){};
    
    virtual double getCapitalization(double interest_rate, double accrual_time) const;
    virtual double getRate(double future_value, double accrual_time) const;
    virtual std::string info() const;
    
    virtual ExponentialRate* clone() const;
    virtual ~ExponentialRate(){};
    
    friend std::ostream& operator<<(std::ostream& s, ExponentialRate& c);
    friend class boost::serialization::access;
  private:
    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int){
      boost::serialization::base_object<Compounding>(*this);
    }
  };
}
#endif
