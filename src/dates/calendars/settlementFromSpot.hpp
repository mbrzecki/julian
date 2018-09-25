#ifndef JULIAN_SETTLEMENTFROMSPOT_HPP
#define JULIAN_SETTLEMENTFROMSPOT_HPP

#include <dates/calendars/calendar.hpp>
#include <dates/calendars/settlementDateConvention.hpp>
#include <dates/date.hpp>
#include <dates/tenor.hpp>

namespace julian {

  /**
   * @file   settlementFromSpot.hpp
   * @brief  File contains definition of SettlementFromSpot class. 
   */
    
  /** \ingroup calendar_holidays
   *  \brief Class calculating settlement date from expiry date
   *
   * A transactions are settled on settlement date, but price at which the settlement takes place is determined on expiry date.
   * Settlement date and expiry date for a give tenor can be calculate in different way. This class implements calculating the settlement and expiry in following way:
   * * Add tenor to spot date and roll the resulting date to appropriate business day. The resulting date would be settlement date.
   * * Calculate the date for which settlement date is spot date. This would be expiry date.
   */

  
  class SettlementFromSpot: public SettlementDateConvention {
  public:
    /** \brief Constructor
	
	Default constructor.
    */
    SettlementFromSpot(){};
    
    
    virtual Date calculateSettlementDate(Date,Tenor,const Calendar&) const;
    virtual Date calculateExpiryDate(Date,Tenor,const Calendar&) const;
    /** \brief Virtual copy constructor 
	
	Method is an implementation of virtual copy constructor.
    */
    virtual SettlementFromSpot* clone() const;
    
    /** \brief Info about class
	
	Method returns string that containing information about class. 
    */
    virtual std::string info() const;
    /** \brief destructor
	
	Default destructor.
    */
    virtual ~SettlementFromSpot(){};
    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int){
      boost::serialization::base_object<SettlementDateConvention>(*this);
    }
  };
}
#endif
