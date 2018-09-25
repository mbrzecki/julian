#ifndef JULIAN_CORPUSCHRISTI_HPP
#define JULIAN_CORPUSCHRISTI_HPP

#include <dates/calendars/holiday.hpp>
#include <dates/calendars/easter.hpp>

namespace julian {

  /**
   * @file   corpusChristi.hpp
   * @brief  File contains CorpusChristi class.
   */
  
  /** \ingroup calendar_holidays
   *  \brief Corpus Christi
   *
   * Corpus Christi is a moveable feast, celebrated on the Thursday, 60 days after Easter.
   *
   */
 
  class CorpusChristi: public Holiday {
  public:
    virtual bool operator()(Date) const;
    virtual CorpusChristi* clone() const;
    virtual std::string info() const;
    virtual ~CorpusChristi(){};
    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int){
      boost::serialization::base_object<Holiday>(*this);
    }
  };
} // namespace julian
#endif
