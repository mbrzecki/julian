#include <dates/calendars/settlementFromSpot.hpp>

namespace julian {

  Date SettlementFromSpot::calculateSettlementDate(Date d, Tenor t, const Calendar& calendar) const {
    Date settlement = calendar.getSpot(d);
    settlement += t;
    settlement = calendar.adjust(settlement);

    return settlement;
  }

  Date SettlementFromSpot::calculateExpiryDate(Date d, Tenor t, const Calendar& calendar) const {
    Date settlement = calendar.getSpot(d);
    settlement += t;
    settlement = calendar.adjust(settlement);
    return calendar.workingDays(settlement, -calendar.getSpotLag());
  }

  SettlementFromSpot* SettlementFromSpot::clone() const {
    return new SettlementFromSpot(*this);
  }

  /** \brief informations about class
   * 
   * Method returns string that containing information about class. 
   */
  std::string SettlementFromSpot::info() const {
    std::string s = "SettlementFromSpot ";
    return s;
  }
}  // namespace julian
