#ifndef JULIAN_HOLIDAY_HPP
#define JULIAN_HOLIDAY_HPP

#include <dates/date.hpp>
#include <utils/smartPointer.hpp>
#include <utils/utils.hpp>

namespace julian {

  /**
   * @file   holiday.hpp
   * @brief  File contains definition of Holiday class.
   */
  
  /** \ingroup calendar_holidays
   * \brief  Class is an abstract class expressing the concept of holiday calendar for different currencies and stock exchange.
   *  
   * This class is a interface for classes representing various holidays and holiday sets. 
   *
   */

  class Holiday {
  public:
    /** \brief Constructor
	
	Default constructor.
    */
    Holiday(){};
    
    /** \brief Check holiday
	
	Method returns true if a given date is a holiday or false otherwise.
    */
    virtual bool operator()(Date) const = 0;
    
    /** \brief Virtual copy constructor 
	
	Method is an implementation of virtual copy constructor.
    */
    virtual Holiday* clone() const = 0;
    
    /** \brief Info about class
	
	Method returns string that containing information about class. 
    */
    virtual std::string info() const =0;
    /** \brief deconstructor
	
	Default deconstructor.
    */
    virtual ~Holiday(){};
    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int){
    }
  };
}
#endif
