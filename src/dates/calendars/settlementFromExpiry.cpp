#include <string>
#include <dates/calendars/settlementFromExpiry.hpp>

namespace julian {

  /** \brief Constructor
	
      Default constructor.
  */
  
  SettlementFromExpiry::SettlementFromExpiry(){
  }

  /** \brief Constructor
      
      Default constructor.
  */
  
  Date SettlementFromExpiry::calculateSettlementDate(Date d,Tenor t,const Calendar& calendar) const {
    Date settlement = d + t;
    settlement = settlement + 2*DAY;
    Date result = calendar.adjust(settlement);
    return result;
  }
  
  /** \brief Constructor
	
      Default constructor.
  */
  Date SettlementFromExpiry::calculateExpiryDate(Date d,Tenor t,const Calendar& calendar) const {
    Date expiry = d + t;
    return calendar.adjust(expiry);
  }

  /** \brief Virtual copy constructor 
	
      Method is an implementation of virtual copy constructor.
  */
  
  SettlementFromExpiry* SettlementFromExpiry::clone() const {
    return new SettlementFromExpiry(*this);
  }
  
  /** \brief informations about class
   * 
   * Method returns string that containing information about class. 
   */
  std::string SettlementFromExpiry::info() const {
    std::string s = "SettlementFromExpiry ";
    return s;
  }

  /** \brief destructor
	
      Default destructor.
  */
  SettlementFromExpiry::~SettlementFromExpiry() {
  }
}  // namespace julian
