#ifndef JULIAN_FIXEDHOLIDAY_HPP
#define JULIAN_FIXEDHOLIDAY_HPP

#include <dates/calendars/holiday.hpp>

namespace julian {

/**
 * @file   fixedHoliday.hpp
 * @brief  File contains definition of fixed holiday class.
 */

  /** \ingroup calendar_holidays
   * \brief Fixed date holiday
   *
   * Fixed date holiday may represent a holiday that occurs every year on the same day and month.
   * 
   */
  
  class FixedHoliday: public Holiday {
  public:
    /** \brief Default constructor
     */
    FixedHoliday(){};
    /** \brief Constructor
     */
    FixedHoliday(int month,int day):month_(month),day_(day){};
    virtual bool operator()(Date) const;
    virtual FixedHoliday* clone() const;
    virtual std::string info() const;
    virtual ~FixedHoliday(){};
    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & ar, const unsigned int){
      boost::serialization::base_object<Holiday>(*this);
      ar & BOOST_SERIALIZATION_NVP(month_);
      ar & BOOST_SERIALIZATION_NVP(day_);
    }
    int month_; //!<@brief month of fixed holiday
    //!< Integer represents the month in which fixed holiday occurs.
    
    int day_; //!<@brief day of fixed holiday
    //!< Integer represents the day on which fixed holiday occurs.
  };
}
#endif
