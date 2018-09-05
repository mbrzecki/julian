#ifndef JULIAN_CASHFLOW_HPP
#define JULIAN_CASHFLOW_HPP

#include <marketData/interestRateCurves/irCurve.hpp>
#include <dates/date.hpp>
#include <interestRates/interestRate.hpp>
namespace julian {

  
  /**
   * @file   CashFlow.hpp
   * @brief  File contains definition of cash flow class.
   */

  
  /** \ingroup instruments
   * \brief Class implements the general concept of CF understand as certain amount paid on predefined date
   *
   * Class implements the general concept of CF understand as certain amount paid on predefined date. Class is a building block of all linear instruments. 
   */
  
  class CashFlow {
  public:
    /** \brief discounts the cashflow
     *
     *  Method discount the cashflow on the curve valuation date.  
     */
    virtual double price(const SmartPointer<ir::Curve>& disc) = 0;

    /** \brief prints and returns the value discounted the cashflow
     *
     *  Method calculates discounted cashflow on the curve valuation date and then prints it 
     */
    virtual double value(const SmartPointer<ir::Curve>& disc) = 0;

    /** \brief returns payment date
     */
    virtual Date getDate() const = 0;

    /** \brief returns notional
     */
    virtual double getNotional() const = 0;

    /** \brief returns CF
     */
    virtual double getCF() const = 0;

    /** \brief sets new CF value
     */
    virtual void setCashFlow(double amount) = 0;

    /** \brief calculates new CF value basing on quoting and interest rate provided
     */    
    virtual void setCashFlow(double quote, const InterestRate& rate) = 0;

    /** \brief sets new CF value basing on interest rate curve
     */
    virtual void setCashFlow(const SmartPointer<ir::Curve>&) = 0;

    /** \brief virtual copy constructor 
     */
    virtual CashFlow* clone() const = 0;

    /** \brief destructor 
     */
    virtual ~CashFlow(){};

    friend class boost::serialization::access;
  private:
    template<class Archive>
    /**\brief interface of Boost serialization library
     */
    void serialize(Archive & , const unsigned int) {
    }
  };
  
}  // namespace julian

#endif /* CASHFLOW_HPP */
