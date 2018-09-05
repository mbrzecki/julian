#ifndef JULIAN_CASHFLOWBUILDER_HPP
#define JULIAN_CASHFLOWBUILDER_HPP

#include <interestRates/interestRate.hpp>
#include <dates/date.hpp>
#include <dates/calendars/calendar.hpp>
#include <instruments/instrumentAuxiliaryTypes.hpp>
#include <instruments/CashFlow.hpp>
#include <instruments/FixedCashFlow.hpp>
#include <instruments/FloatingCashFlow.hpp>
#include <instruments/CashFlowVector.hpp>
#include <map>

namespace julian {
  /**
   * @file  CashFlowBuilder.hpp
   * @brief  File contains implementation of  CashFlowBuilder.
   */
  /** \ingroup instruments
   * \brief Class implements Builder that helps to construct vector of cash flows
   *
   */

  class CashFlowBuilder {
  public:
    CashFlowBuilder();

    CashFlowBuilder& usingCalendar(const Calendar&);
    CashFlowBuilder& withTenor(const Tenor&);
    CashFlowBuilder& withStartDate(const Date&);
    CashFlowBuilder& withEndDate(const Date&);
    
    CashFlowBuilder& withNotional(const double);
    CashFlowBuilder& withQuote(const double);
    CashFlowBuilder& withFxRate(const double);
    CashFlowBuilder& withAdditiveMargin(const double);
    CashFlowBuilder& withMultiplicativeMargin(const double);
    CashFlowBuilder& withFixing(const std::map<Date,double>&);

    CashFlowBuilder& withInterestRate(const InterestRate&);
    CashFlowBuilder& withPaymentFrequency(Frequency);

    CashFlowBuilder& withExchangeOfNotional(bool);
    
    CashFlowBuilder& buildFloatingCashFlows();
    CashFlowBuilder& buildFixedCashFlows();

    operator CashFlowVector();
    
  private:
    void fixedCFWithExchangeOfNotional();
    void fixedCFWithoutExchangeOfNotional();
    
    CashFlowVector cfv_; /*!< \brief Cash flow vector*/
    
    double notional_;   /*!< \brief Notional of the cash flows*/
    Tenor tenor_;       /*!< \brief Tenor of the last CF*/
    Calendar calendar_; /*!< \brief Calendar used in construction of CF vector*/
    Frequency frequency_; /*!< \brief Frequency of CFs*/
    Date start_date_; /*!< \brief Start date of first CFs*/
    Date end_date_; /*!< \brief Payment of last CFs*/

    double quote_; /*!< \brief Quote used to calculate the fixed cashflow */
    double additive_margin_; /*!< \brief Additive margin used by floating cashflows*/
    double multiplicative_margin_; /*!< \brief Multiplicative margin used by floating cashflows*/
    double fx_rate_; /*!< \brief FxRate */
    
    std::map<Date,double> fixings_; /*!< \brief Fixing used to determined pasted floating cash flows */
    
    bool exchange_of_notional_; /*!< \brief If exchange of notional is set to true the first and the last CFs contains notional*/
    InterestRate rate_; /*!< \brief Interest rate convention*/
  };

}  // namespace julian
#endif 
