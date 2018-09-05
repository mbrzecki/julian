#ifndef JULIAN_IRCURVE_HPP
#define JULIAN_IRCURVE_HPP

#include <dates/date.hpp>
#include <interestRates/interestRate.hpp>

namespace julian {
namespace ir {

  /**
   * @file   irCurve.hpp
   * @brief  File contains interface of interest rate curves.
   */

  /** \ingroup irCurve
   * \brief The class interfaces interest rate curves.  
   *
   * A interest rate curve is a representation of the relationship of rates in the swap or bond markets and their maturity and is used for the valuations of bonds or swap-related instruments. 
   * It is usually constructed with benchmark instruments and certain related contracts: market instruments that represent the most liquid and dominant instruments for their respective time horizons.
   * More information see \cite LemBrosSwapCurve \cite BankOfCanadaSwapCurve \cite hull \cite duffy4 \cite tuckman .  
   */
  class Curve {
  public:

    /** \brief Default constructor
     */
    Curve(){};

    /** \brief get DF
     */
    virtual double DF(Date) const = 0;

    /** \brief get forward DF
     */
    virtual double DF(Date,Date) const = 0;

    /** \brief get DF for a tenor
     */
    virtual double DF(Tenor) const = 0;

    /** \brief get forward DF (between two tenors)
     */
    virtual double DF(Tenor,Tenor) const = 0;

    /** \brief get capitalization
     *
     * This method calculate the value of 1 monetary unit invested today and received on date calculated on the basis of given tenor.
     */
    virtual double capitalization(Date) const = 0;

    /** \brief get capitalization
     *
     * This method calculate the value of 1 monetary unit invested today and received on date calculated on the basis of given tenor.
     */
    virtual double capitalization(Tenor) const = 0;

    /** \brief get forward capitalization
     *
     * This method calculate the value of 1 monetary unit invested on date d1 and received on date d2.
     */
    virtual double capitalization(Date,Date) const = 0;

    /** \brief get forward capitalization
     *
     * This method calculate the value of 1 monetary unit invested on date d1 (calculated on the basis of tenor t1)  and received on date d2 (calculated on the basis of tenor t2).
     */
    virtual double capitalization(Tenor,Tenor) const = 0;  

    /** \brief get coupon
     *
     * This method calculate the revenue on 1 monetary unit invested today and received on date d.
     */ 
    virtual double coupon(Date) const = 0;

    /** \brief get coupon
     *
     * This method calculate the revenue on 1 monetary unit invested today and received on date d calculated on basis of tenor t.
     */
    virtual double coupon(Tenor) const = 0;

    /** \brief get coupon
     *
     * This method calculate the revenue on 1 monetary unit invested on date d1 and received on date d2.
     */
    virtual double coupon(Date,Date) const = 0;

    /** \brief get coupon
     *
     * This method calculate the revenue on 1 monetary unit invested on date d1 calculated on the basis teno1 and received on date d2 calculated on the basis of tenor t2.
     */
    virtual double coupon(Tenor,Tenor) const = 0; 

    /** \brief get zero coupon rate
     *
     * The zero coupon rate for date is the yield of zero coupon bond which matures on date. The rate returned by this method is given in curve's interest rate convention.
     */
    virtual double rate(Date) const = 0;

    /** \brief get zero coupon rate
     *
     * The zero coupon rate for tenor is the yield of zero coupon bond which matures on given tenor. The rate returned by this method is given in curve's interest rate convention.
     */
    virtual double rate(Tenor) const = 0;

    /** \brief get zero coupon rate
     *
     * The zero coupon rate for date is the yield of zero coupon bond which matures on date d. The rate returned by this method is given in provided interest rate convention.
     */
    virtual double rate(Date,InterestRate) const = 0;

    /** \brief get zero coupon rate
     *
     * The zero coupon rate for tenor t is the yield of zero coupon bond which matures at t. The rate returned by this method is given in provided interest rate convention.
     */
    virtual double rate(Tenor,InterestRate) const = 0;

    /** \brief get forward rate
     *
     * The forward rate between d1 and d2 is the yield of zero coupon bond that will commence at date d1 and matures at date d2.  
     The rate returned by this method is given in curve's interest rate convention.
    */
    virtual double fwdRate(Date,Date) const = 0;

    /** \brief get forward rate
     *
     * The forward rate between d1 and d2 ( date calculated on the basis of provided tenors) is the yield of zero coupon bond that will commence at date d1 and matures at date d2.  
     * The rate returned by this method is given in curve's interest rate convention.
     */
    virtual double fwdRate(Tenor,Tenor) const = 0;

    /** \brief get forward rate
     *
     * The forward rate between d1 and d2 ( date d2 calculated on the basis of provided tenor t) is the yield of zero coupon bond 
     * that will commence at date d1 and matures at date d2.  The rate returned by this method is given in curve's interest rate convention.
     */
    virtual double fwdRate(Date,Tenor) const = 0;

    /** \brief get forward rate
     *
     * The forward rate between d1 and d2 is the yield of zero coupon bond that will commence at date d1 and matures at date d2 (convention of this interest rate is provided as argument of method).
     */
    virtual double fwdRate(Date,Date,InterestRate) const = 0;

    /** \brief get forward rate
     *
     * The forward rate between d1 and d2 ( date calculated on the basis of provided tenors) is the yield of zero coupon bond that will commence at date d1 and matures at date d2. 
     * (convention of this interest rate is provided as argument of method).
     */
    virtual double fwdRate(Tenor,Tenor,InterestRate) const = 0;

    /** \brief get forward rate
     *
     * The forward rate between d1 and d2 ( date d2 calculated on the basis of provided tenor) is the yield of zero coupon bond that will commence at date d1 and matures at date d2. 
     * (convention of this interest rate is provided as argument of method).
     */
    virtual double fwdRate(Date,Tenor,InterestRate) const = 0;

    /** \brief get today date
     *
     * The method returns the date for which curve was defined.
     */
    virtual Date getValuationDate() const = 0;

    /** \brief destructor
     */
      
    virtual ~Curve(){};
    /** \brief Virtual copy constructor
     */
    virtual Curve* clone() const;

    friend class boost::serialization::access;
  private:

    /** \brief interface used by Boost serialization library
     */
    template<class Archive>
    void serialize(Archive & ar, const unsigned int){
    }
  };   
}  // namespace ir
}  // namepsace julian
#endif /* JULIAN_IRCURVE_HPP */
