#ifndef JULIAN_LINEARINSTRUMENTBUILDER_HPP
#define JULIAN_LINEARINSTRUMENTBUILDER_HPP

#include <dates/_all_dates.hpp>
#include <instruments/linear/deposit.hpp>
#include <instruments/linear/FRA.hpp>
#include <instruments/linear/IRS.hpp>
#include <instruments/bonds/_all_bonds.hpp>
#include <map>

namespace julian {
  
  /**
   * @file   linearInstrumentBuilder.hpp
   * @brief  File contains definition of linear instrument builder class.
   */
  
  /** \ingroup linearInstruments
   * \brief Class implements \a builder \a design \a pattern supporting construction of linear instruments.
   *
   * The builder class is an implementation of creational design pattern called Builder. 
   * The aim of creating this class was to provide robust, readable and flexible method of constructing object representing linear instruments.  
   * The class contains setting methods  that provides inputs to the construction process, and casting operator that transform builder into required instrument. 
   *
   * The class establishes some default inputs, that will be used if their are not provided by the user. These are:
   * * Notional = 100.00;
   * * additive margin = 0.0, multiplicative margin = 1.0
   * * haircut = 0.00 (for repo's bond), convexity = 0.0 (for futures), established fixing = 0.0 (for FRAs), Swap points = 0.0 (for fxForward), basis points (for Basis swaps).
   * 
   * Trade date must be provided. Other dates of the contract may not be defined if the calendar and adequate tenors are given. 
   */

  class BuildLinearInstrument {
  public:
    BuildLinearInstrument();
    BuildLinearInstrument& usingCalendar(const Calendar&);
    
    BuildLinearInstrument& withTenor(const Tenor&);
    BuildLinearInstrument& withTenor(const TimeUnit&);
    
    BuildLinearInstrument& withForwardTenors(const Tenor&,const Tenor&);
    
    BuildLinearInstrument& startingInQuarter(const int&,const int&);
    BuildLinearInstrument& nextFuturesDate(const int&);
    
    BuildLinearInstrument& withTradeDate(const Date&);
    BuildLinearInstrument& withStartDate(const Date&);
    BuildLinearInstrument& withFixingDate(const Date&);
    BuildLinearInstrument& withFraSettlementDate(const Date&);
    BuildLinearInstrument& withMaturityDate(const Date&);
    
    BuildLinearInstrument& withTradeDate(int y,int m,int d);
    BuildLinearInstrument& withStartDate(int y,int m,int d);
    BuildLinearInstrument& withFixingDate(int y,int m,int d);
    BuildLinearInstrument& withMaturityDate(int y,int m,int d);
    
    BuildLinearInstrument& withFixedLegFrequency(const Frequency&);
    BuildLinearInstrument& withFloatingLegFrequency(const Frequency&);
    BuildLinearInstrument& withMainLegFrequency(const Frequency&);
    BuildLinearInstrument& withSpreadLegFrequency(const Frequency&);
    
    BuildLinearInstrument& withInterestRate(const InterestRate&);
    BuildLinearInstrument& withInterestRateForFixedLeg(const InterestRate&);
    BuildLinearInstrument& withInterestRateForFloatingLeg(const InterestRate&);
    BuildLinearInstrument& withInterestRateForMainLeg(const InterestRate&);
    BuildLinearInstrument& withInterestRateForSpreadLeg(const InterestRate&);
    
    BuildLinearInstrument& withNotional(const double);
    BuildLinearInstrument& withQuote(const double);
    BuildLinearInstrument& withAdditiveMargin(const double);
    BuildLinearInstrument& withMultiplicativeMargin(const double);
    BuildLinearInstrument& withHaircut(const double);
    BuildLinearInstrument& withBasisPoints(const double);
    BuildLinearInstrument& withFixing(const double, const Date ); 
    BuildLinearInstrument& withConvexityAdjustment(const double);

    BuildLinearInstrument& withFxSpot(const double);
    BuildLinearInstrument& withSwapPoints(const double);
    
    BuildLinearInstrument& withBond(const SmartPointer<Bond>&);

    BuildLinearInstrument& isExchangeOfNotional(bool);
    
    operator Deposit();
    operator FRA();
    operator IRS();
    
  private:
    void reset();
    void datesCalculation();

    /*! \name Time and date settings
     */
    //@{
    
    Calendar calendar_;                   /*!< @brief The calendar is needed to calculate properly dates of contract.*/

    Tenor fixing_tenor_;                  /*!< @brief Fixing tenor is needed by FRA argument. It defines start date of accrual period. If fixing tenor is provided, builder must have calendar defined.*/
    Tenor maturity_tenor_;                /*!< @brief Maturity tenor defines the end date of the contract. If maturity tenor is provided, builder must have defined calendar*/

    Date trade_date_;                     /*!< @brief Trade date is the date when agreement was set. It must be provided.*/
    Date start_date_;                     /*!< @brief The start date is usually defined as spot lag of the contract.*/
    Date fixing_date_;                    /*!< @brief Fixing date is required by FRA contracts. It defines moment of fixing .*/
    Date fra_value_date_;                 /*!< @brief The date on which the FRA notional loan become effective.*/
    Date maturity_date_;                  /*!< @brief The end date defines the settlement of the contract.*/

    int next_futures_date_;                /*!< @brief This integer gives which in turn futures dates must be calculated (starting form trade date). */
    int futures_quarter_start_;            /*!< @brief This number is passed to futures. Informs in which quarter of the year futures starts.*/
    int futures_year_start_;               /*!< @brief This number is passed to futures. Informs in which year futures starts */
    //@}

    /*! \name Mechanics of instrument
     */
    //@{
    InterestRate rate_for_main_leg_;      /*!< @brief Interest rate convention for main leg.This rate convention will be passed to instrument requiring only one interest rate (depos, FRAs, etc.).*/
    InterestRate rate_for_second_leg_;    /*!< @brief Interest rate convention for secondary leg.*/
    
    Frequency main_leg_frequency_;        /*!< @brief This variable represents the payment frequency of fixed leg (in IRS) or main leg (in other swaps). */
    Frequency second_leg_frequency_;      /*!< @brief This variable represents the payment frequency of floating leg (in IRS) or spread leg (in other swaps). */
    bool is_notional_exchanged_;          /*!< @brief If this variable was initialized by the builder ( withoutExchangeOfNotional() ) the swaps will not exchange notional on start date and maturity date.*/
    //@}

    /*! \name Quoting of instrument
     */
    //@{
    double notional_;                     /*!< @brief Number represents notional of the contract. It is passed to all instruments. It is equal to 100.00, unless user provides other input.*/
    double quote_;                        /*!< @brief Number represents the quoting of the contract.*/
    double convexity_;                    /*!< @brief Convexity is passed to Futures contract. For more information see convexity adjustment for futures in \cite LemBrosSwapCurve \cite hull .*/
    double additive_margin_;              /*!< @brief Additive margin added to fixing. */
    double multiplicative_margin_;        /*!< @brief Multiplicative margin multiplying fixing.*/
    std::map<Date,double> fixings_;
    

    double fx_spot_;                      /*!< @brief fx_spot_ as of trade date must be given to properly construct FxForward. */
    double swap_points_;                  /*!< @brief Swap points are quotings of FxForward.*/
    double haircut_;                      /*!< @brief This value is needed to properly construct repo agreement. It is the haircut of fixed income bond.*/
    SmartPointer<Bond> bond_;             /*!< @brief The bond will be passed to repo agreement*/
    //@}
  };
}
#endif
