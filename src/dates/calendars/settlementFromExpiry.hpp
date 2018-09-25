#ifndef JULIAN_SETTLEMENTFROMEXPIRY_HPP
#define JULIAN_SETTLEMENTFROMEXPIRY_HPP

#include <dates/calendars/calendar.hpp>
#include <dates/calendars/settlementDateConvention.hpp>
#include <dates/date.hpp>
#include <dates/tenor.hpp>

namespace julian {

  /**
   * @file   settlementFromExpiry.hpp
   * @brief  File contains implementation of settlement from expiry convention.
   */
  
  /** \ingroup calendar_holidays
   *  \brief Class calculating settlement date from expiry date
   *
   * A transactions are settled on settlement date, but price at which the settlement takes place is determined on expiry date.
   * Settlement date and expiry date for a give tenor can be calculate in different way. This class implements calculating the settlement and expiry in following way:
   * * Add tenor to today date and roll the resulting date to appropriate business day. The resulting date would be expiry date.
   * * Calculate spot date of expiry date. This would be settlement date.
   */

  
  class SettlementFromExpiry: public SettlementDateConvention {
  public:

    SettlementFromExpiry();
    
    virtual Date calculateSettlementDate(Date, Tenor, const Calendar&) const;
    virtual Date calculateExpiryDate(Date, Tenor, const Calendar&) const;
  
    virtual SettlementFromExpiry* clone() const;

    virtual std::string info() const;

    virtual ~SettlementFromExpiry();
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
