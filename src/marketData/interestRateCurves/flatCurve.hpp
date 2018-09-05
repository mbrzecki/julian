#ifndef JULIAN_FLATCURVE_HPP
#define JULIAN_FLATCURVE_HPP

#include <dates/date.hpp>
#include <marketData/interestRateCurves/irCurve.hpp>
#include <interestRates/interestRate.hpp>


namespace julian {
  namespace ir {

    /**
     * @file   flatCurve.hpp
     * @brief  File contains definition of flat interest rate curve.
     */
    
    /** \ingroup irCurve
     *
     * \brief The class defines the flat interest rate curve.
     *
     * Flat interest rate curve is a curve which Zero Coupon rate is the same for all tenors. 
     *  
     */    
    class FlatCurve: public Curve {
    public:
      FlatCurve();
      FlatCurve(InterestRate&,double, Date, Calendar&);

      virtual double DF(Date) const;
      virtual double DF(Date,Date) const;
      virtual double DF(Tenor) const;
      virtual double DF(Tenor,Tenor) const;

      virtual double capitalization(Date) const;
      virtual double capitalization(Tenor) const;
      virtual double capitalization(Date,Date) const;
      virtual double capitalization(Tenor,Tenor) const;  
  
      virtual double coupon(Date) const;
      virtual double coupon(Tenor) const;
      virtual double coupon(Date,Date) const;
      virtual double coupon(Tenor,Tenor) const; 
  
      virtual double rate(Date) const;
      virtual double rate(Tenor) const;
      virtual double rate(Date,InterestRate) const;
      virtual double rate(Tenor,InterestRate) const;
  
      virtual double fwdRate(Date,Date) const;
      virtual double fwdRate(Tenor,Tenor) const;
      virtual double fwdRate(Date,Tenor) const;
      virtual double fwdRate(Date,Date,InterestRate) const;
      virtual double fwdRate(Tenor,Tenor,InterestRate) const;
      virtual double fwdRate(Date,Tenor,InterestRate) const;
      
      virtual Date getValuationDate() const;
      
      virtual ~FlatCurve(){};
      FlatCurve* clone() const;
      
      friend std::ostream& operator<<(std::ostream&, FlatCurve&);
      friend class boost::serialization::access;
  private:

      /** \brief interface used by Boost serialization library
       */
      template<class Archive>
      void serialize(Archive & ar, const unsigned int);

      InterestRate rate_; /*!< @brief Interest rate convention*/
      double zero_coupon_rate_; /*!< @brief Value of zero coupon rate*/
      Date curve_date_; /*!< @brief Today represent the date on which the curve is valid.*/
      Calendar calendar_; /*!< @brief Thanks to calendar outputs of the curve (DFs, forward rates etc) can be calculated only on the basis of provided tenor.*/
    };

    template<class Archive>
    void FlatCurve::serialize(Archive & ar, const unsigned int) {
      boost::serialization::base_object<Curve>(*this);
      ar & BOOST_SERIALIZATION_NVP(rate_);
      ar & BOOST_SERIALIZATION_NVP(zero_coupon_rate_);
      ar & BOOST_SERIALIZATION_NVP(curve_date_);
      ar & BOOST_SERIALIZATION_NVP(calendar_);
    }
}  // namespace ir
}  // namespace julian

#endif /* FLATCURVE_HPP */
