#ifndef JULIAN_FORWARDCURVE_HPP
#define JULIAN_FORWARDCURVE_HPP

#include <vector>
#include <utils/SmartPointer.hpp>
#include <mathematics/interpolation/interpolation.hpp>
#include <dates/date.hpp>
#include <dates/yearFractions/yearFraction.hpp>
#include <utils/utils.hpp>
#include <boost/serialization/export.hpp>
namespace julian {

  /**
   * @file   ForwardCurve.hpp
   * @brief  File contains definition of forward curve class.
   */

  /** \ingroup marketdata
   * \brief The class implements the forward curve.
   *
   * The forward curve is a function graph in finance that defines the prices at which a contract for future delivery or payment can be concluded today.
   * The forward curve can represent prices of commodity, equity of fx forwards.
   *
   * Object is defined by set of dates and prices. To calculate the forward price on date that is not a grid date, interpolation is applied.
   *
   */
  class ForwardCurve {
  public:
    ForwardCurve();
    ForwardCurve(const Date as_of_date, const SmartPointer<Interpolation>& interpolation,const SmartPointer<YearFraction>& yf, const std::vector<Date>& dates, const std::vector<double>& prices);

    double getForwardPrice(Date d);

    std::vector<Date> getDates();
    
    friend std::ostream& operator<<(std::ostream&, ForwardCurve&);
    friend class boost::serialization::access;
  private:
    template<class Archive>
    void serialize(Archive & ar, const unsigned int);
    
    Date as_of_date_; /*!< @brief  date on which the curve is valid.*/
    SmartPointer<Interpolation> interpolation_; /*!< @brief Interpolation method*/
    SmartPointer<YearFraction> yf_; /*!< @brief  Year fraction convention changes dates into continuous time*/
    std::vector<Date> dates_; /*!< @brief Grid dates*/
    std::vector<double> time_;  /*!< @brief Continuous time calculated on basis of grid dates*/
    std::vector<double> prices_; /*!< @brief Forward prices associated with dates*/ 
  };

  /** \brief interface used by Boost serialization library
   */
  template<class Archive>
  void ForwardCurve::serialize(Archive & ar, const unsigned int){
    ar & BOOST_SERIALIZATION_NVP( as_of_date_);
    ar & BOOST_SERIALIZATION_NVP(interpolation_);
    ar & BOOST_SERIALIZATION_NVP(yf_);
    ar & BOOST_SERIALIZATION_NVP(dates_);
    ar & BOOST_SERIALIZATION_NVP(prices_);
  }
}

#endif /* FORWARDEQUITYCURVE_HPP */
