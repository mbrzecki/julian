#ifndef JULIAN_YEARFRACTION_HPP
#define JULIAN_YEARFRACTION_HPP

#include <dates/date.hpp>
#include <utils/smartPointer.hpp>

#include <iostream>
#include <string>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

namespace julian {

  /**
   * @file   yearFraction.hpp
   * @brief  File contains interface for year fractions 
   */

  /** \ingroup yearfraction
   *  \brief This class is an abstract class expressing the concept of calculating year fraction. 
   *
   * This class is a interface of all year fraction conventions. Year fraction classes assign double value to period defined by two dates.
   */

  
  class YearFraction {
  public:
    
    /** \brief Constructor
	
	Default constructor
    */
    YearFraction(){};
    
    /** \brief Calculates year fraction
	
	Method calculates the year fraction on the basis of two dates. 
    */
    virtual double operator()(const Date& ,const Date&) const = 0;
    
    /** \brief Virtual copy constructor
	
	Method is an implementation of virtual copy constructor.
    */
    virtual YearFraction* clone() const = 0;
    
    /** \brief info about class
	
	Method returns string that containing information about class. 
    */
    virtual std::string info() const = 0;
    
    /** \brief Destructor 
	
	Destructor
    */
    virtual ~YearFraction(){};

    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int) {
    }
  };
} // namespace julian

#endif
