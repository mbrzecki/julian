#include <dates/calendars/corpusChristi.hpp>
#include <string>

namespace julian {

  /** \brief Checks if date is Corpus Christi holiday 
   * 
   * Method returns true if a date is a Corpus Christi holiday and false otherwise.
   */
  bool CorpusChristi::operator()(Date date) const {
    Date easter = EasterForAGivenYear(date.getYear());
    Date corpus_christi = easter +  60 * DAY;
    return (date == corpus_christi);
  }

  /** \brief Virtual copy constructor 
   *
   * Method is an implementation of virtual copy constructor.
   */
  CorpusChristi* CorpusChristi::clone() const {
    return new CorpusChristi(*this);
  }

  /** \brief Informations about class 
   *
   * Method returns string that containing information about class. 
   */
  std::string CorpusChristi::info() const {
    return "CorpusChristi ";
  }
}  // namespace julian
