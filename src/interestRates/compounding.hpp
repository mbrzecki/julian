#ifndef JULIAN_COMPOUNDING_HPP
#define JULIAN_COMPOUNDING_HPP

#include <string>
#include <utils/smartPointer.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
namespace julian {
  
  /**
   * @file   compounding.hpp
   * @brief  File contains interface of interest rate compounding concept.
   */
  
  /** \ingroup interestRate
   *  \brief Class is an abstract class expressing the concept of compounding interest rate.
   *  
   *  This class is a interface of all interest rate compounding conventions.
   */  

  class Compounding {
  public:
    /**
       \brief Default constructor
       
       Default constructor
    */
    Compounding(){};
    
    /**
       \brief Calculates future value
       
       Method calculates the future value of 1 currency unit on the basis of annualized interest rate and interest accrual period.
    */
    virtual double getCapitalization(double interest_rate, double accrual_time) const= 0;
    /**
       \brief Calculates interest rate
       
       Method calculates the annualized interest rate on the basis of future value of interest rate value and interest accrual period.
    */
    virtual double getRate(double future_value,double accrual_time) const = 0;
    
    /** \brief Virtual copy constructor
	
	Method is an implementation of virtual copy constructor.
    */
    
    virtual Compounding* clone() const = 0;
    
    /**\brief Destructor
       
       Default destructor.
    */
    virtual ~Compounding(){};
    
    /** \brief Info about class
	
	Method returns string that containing information about class. 
    */
    virtual std::string info() const = 0;

    
    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int) {
    }
  };
}
#endif
