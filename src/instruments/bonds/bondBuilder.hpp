#ifndef JULIAN_BONDBUILDER_HPP
#define JULIAN_BONDBUILDER_HPP

#include <instruments/bonds/FixedIncomeBond.hpp>
#include <instruments/bonds/FloatingRateBond.hpp>
#include <instruments/bonds/ZeroCouponBond.hpp>
namespace julian {
  /**
   * @file   bondBuilder.hpp
   * @brief  File contains  implementation  of bond builder.
   */
  /**  \ingroup bonds
   *   \brief Class implements \a builder \a design \a pattern supporting construction of bonds.
   *
   * The builder class is an implementation of creational design pattern called Builder. 
   * The aim of creating this class was to provide robust, readable and flexible 
   * method of constructing object representing bonds.
   *
   * The class contains setting methods that provides inputs to the construction process, 
   * and casting operator that transform builder into required bond. 
   * 
   * Trade date must be provided. Other dates of the contract may not be defined 
   * if the calendar and adequate tenors are given. If notional is not provided it is set to 100.0.
   *
   */
  class BuildBond {
  public:
    BuildBond();
  
    BuildBond& withNotional(const double&);
  
    BuildBond& usingCalendar(const Calendar&);
    BuildBond& withStartDate(const Date&);
    BuildBond& withCommenceOfTradingDate(const Date&);
    BuildBond& withMaturityDate(const Date&);
    BuildBond& withTenor(const Tenor&);
  
    BuildBond& withFrequencyOfPayment(const Frequency&);
    BuildBond& withCoupon(const double&);
    BuildBond& withMargin(const double&);
    BuildBond& withFaceValue(const double&);
    BuildBond& withInterestRate(const InterestRate&);

    operator FixedIncomeBond();
    operator FloatingRateBond();
    operator ZeroCouponBond();
    
  private:

    void reset();
    void datesCalculation();
  
    double notional_;     /*!< \brief Notional of the bond*/
    double coupon_;       /*!< \brief Coupon paid by bond */
    double margin_;       /*!< \brief Margin of floating rate bond*/
    double face_amount_;  /*!< \brief Face amount of Zero coupon bond*/
    Calendar calendar_;   /*!< \brief Calendar used to construct the bond*/
    Date start_date_;     /*!< \brief Date from which bond starts to accrue value*/
    Date commence_of_trading_date_;  /*!< \brief Bond issue date  */
    Date maturity_date_;  /*!< \brief Calendar used by a curve*/

    Tenor maturity_;  /*!< \brief Maturity of the bond*/
    
    InterestRate rate_;           /*!< \brief Interest rate convention*/
    Frequency payment_frequency_; /*!< \brief Frequency of payment*/
  };
}

#endif
