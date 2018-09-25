#ifndef JULIAN_COMPOUNDEDRATE_HPP
#define JULIAN_COMPOUNDEDRATE_HPP

#include <interestRates/compounding.hpp>

namespace julian {

  /**
   * @file   compoundedRate.hpp
   * @brief  File contains definition of CompoundedRate class.
   */
  
  /** \ingroup  interestRate
   *  \brief The class encapsulates the compounded rate compounding method.
   *
   * Object of this class implements compounded interest rate compounding. Using compounded convention the future value and interest rate are calculated according to formulae:
   * \f[\textrm{Future Value} = (1 + \textrm{Interest Rate})^{\textrm{Accrual Time}}\f] 
   * \f[\textrm{Interest Rate} = \sqrt[\textrm{Accrual Period}]{\textrm{Future Value}}-1\f]
   *
   */
   
   
  class CompoundedRate: public Compounding {
  public:
    CompoundedRate(){};
    
    virtual double getCapitalization(double interest_rate,double accrual_time) const;
    virtual double getRate(double future_value,double accrual_time) const;
    virtual std::string info() const;
    
    virtual CompoundedRate* clone() const;
    virtual ~CompoundedRate(){};
    
    friend std::ostream& operator<<(std::ostream& , CompoundedRate& );
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
