#ifndef JULIAN_E30360_HPP
#define JULIAN_E30360_HPP

#include <dates/yearFractions/yearFraction.hpp>

/**
 * @file   E30360.hpp
 * @brief  File contains definition of E30360 year fraction convention.
 */

namespace julian {

  /** \ingroup yearfraction
   *  \brief The class encapsulates the E30360 year fraction convention.
   *
   * An object of E30360 class is derived from YearFraction. It calculates year fraction on the basis of two dates using the formula:
   * \f[YearFraction(date_1,date_2) = \frac{360 \times (Y_{2}-Y_{1}) +30 \times (M_{2}-M_{1})+min(D_{2},30) - min(D_{1},30)}{360}\f] 
   * where: \f$\textrm{Y}_{i}\f$ is a year number of the \f$\textrm{date}_{i}\f$, \f$\textrm{M}_{i}\f$ is a month number of the  \f$\textrm{date}_{i}\f$ and  \f$\textrm{D}_{i}\f$ is a day number of the  \f$\textrm{date}_{i}\f$. 
   *
   * This convention is known as 30E/360, 30/360 ICMA or Eurobond basis.The year fraction is calculated according to the formula:
   */

  class E30360: public YearFraction {
  public:
    E30360(){};
    virtual double operator()(const Date&,const Date&) const;
    virtual E30360* clone() const;
    virtual ~E30360(){};
    virtual std::string info() const;
    friend std::ostream& operator<<(std::ostream& s, E30360& yf);
    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & , const unsigned int){
      boost::serialization::base_object<YearFraction>(*this);
    }
  };
}
#endif
