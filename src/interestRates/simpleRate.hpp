#ifndef JULIAN_SIMPLERATE_HPP
#define JULIAN_SIMPLERATE_HPP

#include <interestRates/compounding.hpp>

namespace julian {

/**
 * @file   simpleRate.hpp
 * @brief  File contains definition of SimpleRate class.
 */

/** \ingroup interestRate
 *  \brief The class encapsulates the simple rate compounding method.
 *
 * Object of this class implements simple interest rate compounding. Using simple compounding the future value and interest rate are calculated according to formulae:
 * \f[\textrm{Future Value} = 1 + \textrm{Interest Rate} \times \textrm{Accrual Period}\f] 
 * \f[\textrm{Interest Rate} = \frac{\textrm{Future Value}-1}{\textrm{Accrual Period}}\f]  
 */
  class SimpleRate: public Compounding {
  public:
    SimpleRate(){};
    
    virtual double getCapitalization(double interest_rate,double accrual_time) const;
    virtual double getRate(double future_value,double accrual_time) const;
    virtual std::string info() const;
    
    virtual SimpleRate* clone() const;
    virtual ~SimpleRate(){};
    
    friend std::ostream& operator<<(std::ostream& s, SimpleRate& c);
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
