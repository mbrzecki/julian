#include <dates/calendars/easterMonday.hpp>
#include <string>

namespace julian {

  /** \brief Checks if date is an Easter Monday 
   * 
   * Method returns true if a date is a Easter Monday feast and false otherwise.
   */
  bool EasterMonday::operator()(Date date) const {
    Date easter = EasterForAGivenYear(date.getYear());
    Date easter_monday = easter +  1 * DAY;
    return (date == easter_monday);
  }

  /** \brief Virtual copy constructor 
   *
   * Method is an implementation of virtual copy constructor.
   */
  EasterMonday* EasterMonday::clone() const {
    return new EasterMonday(*this);
  }

  /** \brief Informations about class 
   * 
   *Method returns string that containing information about class. 
   */
  std::string EasterMonday::info() const {
    return "EasterMonday ";
  }
}  // namespace julian
