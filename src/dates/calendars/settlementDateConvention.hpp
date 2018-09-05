#ifndef JULIAN_SETTLEMENTDATECONV_HPP
#define JULIAN_SETTLEMENTDATECONV_HPP

#include <dates/calendars/calendar.hpp>
#include <dates/calendars/settlementDateConvention.hpp>
#include <dates/date.hpp>
#include <dates/tenor.hpp>

namespace julian {

  class Calendar;
  /**
   * @file   settlementDateConvention.hpp
   * @brief  File contains interface of settlement convention.
   */
  
  /** \ingroup calendar_holidays
   * \brief  Interface for classes implementing settlement date conventions.
   *  
   * Class implements an interface for object calculating settlement date for a given date and tenor. This class enables to implement different conventions that are used in financial markets.
   * 
   * For more information about establishing expiry and delivery dates see introduction to \cite Iclark
   */
  
  class SettlementDateConvention {
  public:
    /** \brief Constructor
	
	Default constructor.
    */
    SettlementDateConvention(){};
  
    /** \brief Calculates settlement date 
    */  
    virtual Date calculateSettlementDate(Date,Tenor,const Calendar&) const = 0;
	
    /** \brief Calculates expiry date 
    */  	
    virtual Date calculateExpiryDate(Date,Tenor,const Calendar&) const = 0;
    /** \brief Virtual copy constructor 
	
	Method is an implementation of virtual copy constructor.
    */
    virtual SettlementDateConvention* clone() const = 0;
    
    /** \brief Info about class
	
	Method returns string that containing information about class. 
    */
    virtual std::string info() const =0;
    /** \brief destructor
	
	Default destructor.
    */
    virtual ~SettlementDateConvention(){};

    
    friend class boost::serialization::access;
  private:
    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int) {
    }
  };
}  // namespace julian
 
#endif
