#include <instruments/linear/linearInstrumentBuilder.hpp>
#include <boost/assert.hpp>
#include <instruments/CashFlowBuilder.hpp>

namespace julian {

  /*! \name Constructors
   */

  //@{
  /** \brief Default constructor
   *
   * Default constructor calls the method reset() to initialize itself. 
   */
  BuildLinearInstrument::BuildLinearInstrument() {
    reset();
  }

  //@}

  /*! \name Date and calendar issues
   */
  //@{

  /** \brief provides calendar
   *
   * This method sets up the calendar that is need if user wants to create object with tenors provided.
   */
  BuildLinearInstrument& BuildLinearInstrument::usingCalendar(const Calendar& input) {
    calendar_ = input;
    return *this;
  }

  /** \brief provides the trade date
   *
   * This method must be called for every instrument. It defines the trade date of contract.
   */
  BuildLinearInstrument& BuildLinearInstrument::withTradeDate(int y,int m,int d) {
    trade_date_ = Date(y,m,d);
    return *this;
  }

  /** \brief provides the start date
   *
   * Start date represents the commence date of the contract. It is usually two business day from trade date (so called spot date). If start date is not provided, it is calculated by calendar (the spot date of trade date).
   */
  BuildLinearInstrument& BuildLinearInstrument::withStartDate(int y,int m,int d) {
    start_date_ = Date(y,m,d);
    return *this;
  }


  /** \brief provides fixing date
   *
   * The fixing date is required by FRA contract. It defines the start date of accrual period. If not provided, it will be calculated by calendar on the basis of forward tenors.
   */
  BuildLinearInstrument& BuildLinearInstrument::withFixingDate(int y,int m,int d) {
    fixing_date_ = Date(y,m,d);
    return *this;
  }


  /** \brief provides maturity date
   *
   * Maturity is the day on which contract is settle. End date is required by all contracts. It can be directly provided by this method, or by passing calendar and tenor.
   */
  BuildLinearInstrument& BuildLinearInstrument::withMaturityDate(int y,int m,int d) {
    maturity_date_ = Date(y,m,d);
    return *this;
  }

  /** \brief provides maturity Tenor
   *
   * This method method defines maturity of tenor. The maturity date is calculated using: calendar (working days, settlement convention), trade date and tenor. 
   */
  BuildLinearInstrument& BuildLinearInstrument::withTenor(const Tenor& input) {
    maturity_tenor_ = input;
    return *this;
  }

  /** \brief provides TimeUnit
   *
   * On the basis of time unit tenor is constructed. This method is defined to handle pseudo-tenors (see TimeUnit description)
   */
  BuildLinearInstrument& BuildLinearInstrument::withTenor(const TimeUnit& input) {
    maturity_tenor_ = 1 * input;
    return *this;
  }

  /** \brief provides two tenors for FRA
   *
   * This method provides tenors for FRA calculation. To correctly construct FRA instrument two tenors should be provide:the fixing tenor and maturity tenor.
   */
  BuildLinearInstrument& BuildLinearInstrument::withForwardTenors(const Tenor& input1 , const Tenor& input2) {
    fixing_tenor_ = input1;
    maturity_tenor_ = input2;
    return *this;
  }

  /** \brief provides trade date
   *
   * The trade date is always required. It informs at which date the contract was concluded. 
   */
  BuildLinearInstrument& BuildLinearInstrument::withTradeDate(const Date& input) {
    trade_date_ = input;
    return *this;
  }

  /** \brief provides start date
   *
   * Start date represents the commence date of the contract. It is usually two business day from trade date (so called spot date). If start date is not provided, it is calculated by calendar (the spot date of trade date).
   */
  BuildLinearInstrument& BuildLinearInstrument::withStartDate(const Date& input) {
    start_date_ = input;
    return *this;
  }

  /** \brief provides fixing date
   *
   * The fixing date is required by FRA contract. It defines the start date of accrual period. If not provided, it will be calculated by calendar on the basis of forward tenors.
   */
  BuildLinearInstrument& BuildLinearInstrument::withFixingDate(const Date& input) {
    fixing_date_ = input;
    return *this;
  }

  /** \brief provides maturity date
   *
   * Day when FRA underlying loan becomes effective
   */
  BuildLinearInstrument& BuildLinearInstrument::withFraSettlementDate(const Date& input) {
    fra_value_date_ = input;
    return *this;
  }
  
  /** \brief provides maturity date
   *
   * Maturity is the day on which contract is settle. End date is required by all contracts. It can be directly provided by this method, or by passing calendar and tenor.
   */
  BuildLinearInstrument& BuildLinearInstrument::withMaturityDate(const Date& input) {
    maturity_date_ = input;
    return *this;
  }

  /** \brief provides starting date to futures
   *
   * Futures starts on 3rd Wednesday of March, June,September and December. To correctly establish the starting day of futures, one need to provide the year and the quarter in which futures starts.
   */
  BuildLinearInstrument& BuildLinearInstrument::startingInQuarter(const int& quarter,const int& year) {
    futures_quarter_start_ = quarter;
    futures_year_start_ = year;
    return *this;
  }

  /** \brief sets futures dates 
   *
   * This method calculates upcoming futures starting dates (counting from today). If 0 is provided the builder will generate futures for the nearest futures date.

   */
  BuildLinearInstrument& BuildLinearInstrument::nextFuturesDate(const int& input) {
    next_futures_date_ = input;
    return *this;
  }

  //@}

  /*! \name Mechanics of instrument
   */
  //@{

  /** \brief provides interest rate
   *
   * Most of contracts are quoted by the number representing annualized interest rate. The convention of compounding and calculating year fraction must be provided.
   * Some contracts (like swaps) require two interest rate conventions: for first and second leg. 
   * If those interest rate are not provided separately it is assumed that both are equal to interest rate provided by this method.
   */
  BuildLinearInstrument& BuildLinearInstrument::withInterestRate(const InterestRate& input) {
    rate_for_main_leg_ = input;
    rate_for_second_leg_ = input;
    return *this;
  }

  /** \brief 
   *
   * If exchange of notional is off, the first and last cashflow of instrument will not include notional.
   */
  BuildLinearInstrument& BuildLinearInstrument::isExchangeOfNotional(bool input) {
    is_notional_exchanged_ = input;
    return *this;
  }

  /** \brief provides interest rate for fixed leg of IRS
   *
   * This method provides interest rate convention (compounding and year fraction) for fixed leg of IRS.
   */
  BuildLinearInstrument& BuildLinearInstrument::withInterestRateForFixedLeg(const InterestRate& input) {
    rate_for_main_leg_ = input;
    return *this;
  }

  /** \brief provides interest rate for floating leg of IRS
   *
   * This method provides interest rate convention (compounding and year fraction) for floating leg of IRS.
   */
  BuildLinearInstrument& BuildLinearInstrument::withInterestRateForFloatingLeg(const InterestRate& input) {
    rate_for_second_leg_ = input;
    return *this;
  }

  /** \brief provides fixed leg frequency
   *
   * On the basis of this input, the builder will generate the correct schedule for fixed leg.
   */
  BuildLinearInstrument& BuildLinearInstrument::withFixedLegFrequency(const Frequency& input) {
    main_leg_frequency_ = input;
    return *this;
  }
  
  /** \brief provides floating leg frequency
   *
   * On the basis of this input, the builder will generate the correct schedule for floating leg.
   */
  BuildLinearInstrument& BuildLinearInstrument::withFloatingLegFrequency(const Frequency& input) {
    second_leg_frequency_ = input;
    return *this;
  }

  /** \brief provides interest rate for main leg
   *
   * This method provides the interest rate convention (year fraction and compounding) for main leg of basis swap and CIRS. This leg is received if contract is long.
   */
  BuildLinearInstrument& BuildLinearInstrument::withInterestRateForMainLeg(const InterestRate& input) {
    rate_for_main_leg_ = input;
    return *this;
  }

  /** \brief provides interest rate for spread leg
   *
   * This method provides the interest rate convention (year fraction and compounding) for spread leg of basis swap and CIRS. This leg is received if contract is short. 
   */
  BuildLinearInstrument& BuildLinearInstrument::withInterestRateForSpreadLeg(const InterestRate& input) {
    rate_for_second_leg_ = input;
    return *this;
  }

  /** \brief provides main leg frequency
   *
   * On the basis of this input, the builder will generate the correct schedule for main leg.
   */
  BuildLinearInstrument& BuildLinearInstrument::withMainLegFrequency(const Frequency& input) {
    main_leg_frequency_ = input;
    return *this;
  }

  /** \brief provides spread leg frequency 
   *
   * On the basis of this input, the builder will generate the correct schedule for spread leg.
   */
  BuildLinearInstrument& BuildLinearInstrument::withSpreadLegFrequency(const Frequency& input) {
    second_leg_frequency_ = input;
    return *this;
  }

  //@}


  /*! \name Quoting
   */
  //@{
  /** \brief provides bond
   *
   * By this method bond needed to construct repo agreement is provided. 
   */
  BuildLinearInstrument& BuildLinearInstrument::withBond(const SmartPointer<Bond>& input) {
    bond_ = input;
    return *this;
  }
  
  /** \brief provides convexity
   *
   * By this method convexity of futures contract is provided.
 */
  BuildLinearInstrument& BuildLinearInstrument::withConvexityAdjustment(const double input) {
    convexity_ = input;
    return *this;
  }

  /** \brief provides haircut
   *
   * This method sets up haircut applied to bond that is used in repo construction.
   */
  BuildLinearInstrument& BuildLinearInstrument::withHaircut(const double input) {
    haircut_ = input;
    return *this;
  }

  /** \brief provides basis points
   *
   * This method sets up haircut applied to bond that is used in repo construction.
   */
  BuildLinearInstrument& BuildLinearInstrument::withBasisPoints(const double input) {
    swap_points_ = input;
    return *this;
  }
  
  /** \brief provides notional
   *
   * If notional of the contract is not provided, the default value of 1.0 will be assigned. 
   */
  BuildLinearInstrument& BuildLinearInstrument::withNotional(const double input) {
    notional_ = input;
    return *this;
  }
  
  /** \brief provides quote
   *
   *  All contract (except FxForward) need quoting. The quote represents the price of contract. 
   */
  BuildLinearInstrument& BuildLinearInstrument::withQuote(const double input) {
    quote_ = input;
    return *this;
  }

  /** \brief provides additive margin
   *
   * Additive margin is added to given quote. This method simplify and make more efficient stress testing the curve.
   * To calculate the shift of the curve caused by market quotes movement, one doesn't have to change quoting of all instruments. He or she will need only to provide additive margine to builder.
   */
  BuildLinearInstrument& BuildLinearInstrument::withAdditiveMargin(const double input) {
    additive_margin_ = input;
    return *this;
  }
  
  /** \brief provides multiplicative margin
   *
   * Multiplicative margin allows to change quoting by relative value. This method simplify and make more efficient stress testing the curve. To calculate the shift of the curve caused by market quotes movement, one doesn't have to change quoting of all instruments. He or she will need only to provide multiplicative margine to builder.
   */
  BuildLinearInstrument& BuildLinearInstrument::withMultiplicativeMargin(const double input) {
    multiplicative_margin_ = input;
    return *this;
  }

  /** \brief provides FX spot
   *
   * With this method FX spot from trade date of Fx forward is provided. Fx Spot is required to calculate the future cash flow from fx forward.
   */
  BuildLinearInstrument& BuildLinearInstrument::withFxSpot(const double input) {
    fx_spot_ = input;
    return *this;
  }

  /** \brief provides swap points
   *
   * Swap points are added to Fx spot to obtain the forward price of Fx forward. 
   */
  BuildLinearInstrument& BuildLinearInstrument::withSwapPoints(const double input) {
    swap_points_ = input;
    return *this;
  }

  /** \brief provides fixing
   *
   * Future cash flows of contract may be calculated on the basis of past quoting (for example FRA). This method is used to provided this past quoting to correctly price the instrument.
   */
  BuildLinearInstrument& BuildLinearInstrument::withFixing(const double input1, Date input2 ) {
    fixings_[input2] = input1;
    return *this;
  }

  //@}


  /*! \name Casting operators
   */
  //@{


  /** \brief builds deposit
   *
   * The method builds deposit on the basis of provided inputs.
   */
  BuildLinearInstrument::operator Deposit() {
    datesCalculation();
    quote_ = multiplicative_margin_ * quote_ + additive_margin_;
    Deposit result(trade_date_, start_date_, maturity_date_, rate_for_main_leg_, notional_ , quote_ );
    reset();
    return result;
  }

  /** \brief builds FRA
   *
   * The method builds FRA on the basis of provided inputs.
   */
  BuildLinearInstrument::operator FRA() {
    datesCalculation();
    auto p = fixings_.find(fixing_date_);
    double f = 0.0;
    if (p != fixings_.end()) {
      f = p->second;
    }

    FRA result(trade_date_, fixing_date_, fra_value_date_, maturity_date_, rate_for_main_leg_, notional_, f, quote_);
    reset();
    return result;
  }

  /** \brief builds IRS
   *
   * The method builds IRS on the basis of provided inputs.
   */
  BuildLinearInstrument::operator IRS() {
    datesCalculation();
    CashFlowVector fix = CashFlowBuilder()
      .usingCalendar(calendar_)
      .withNotional(notional_)
      .withInterestRate(rate_for_main_leg_)
      .withStartDate(trade_date_)
      .withEndDate(maturity_date_)
      .withPaymentFrequency(main_leg_frequency_)
      .withQuote(quote_)
      .withExchangeOfNotional(is_notional_exchanged_)
      .buildFixedCashFlows();

    CashFlowVector flo = CashFlowBuilder()
      .usingCalendar(calendar_)
      .withNotional(-notional_)
      .withInterestRate(rate_for_second_leg_)
      .withStartDate(trade_date_)
      .withEndDate(maturity_date_)
      .withPaymentFrequency(second_leg_frequency_)
      .withFixing(fixings_)
      .withAdditiveMargin(additive_margin_)
      .withMultiplicativeMargin(multiplicative_margin_)
      .withExchangeOfNotional(is_notional_exchanged_)
      .buildFloatingCashFlows();

    IRS result(trade_date_, start_date_, maturity_date_, fix, flo ,
	       rate_for_main_leg_, rate_for_second_leg_,
	       notional_, quote_, main_leg_frequency_, second_leg_frequency_);
    reset();
    return result;
  }


  /** \brief resets builder
   *
   * Reset function restores default settings, which are:
   * * notional = 100
   * * multiplicative margin = 1.0
   * * additive margin = 0.0
   * * haircut = 0.0
   * * convexity = 0.0
   * * swap points = 0.0
   * * resetting all dates

   */
  void BuildLinearInstrument::reset() {
    notional_ = 100.0;  
    multiplicative_margin_ = 1.0;
    additive_margin_  = 0.0;
    haircut_ = 0.0;
    is_notional_exchanged_ = true;
    convexity_ = 0.0;
    swap_points_ = 0.0;

    start_date_.setYear(0);
    fixing_date_.setYear(0);
    maturity_date_.setYear(0);
    fixing_tenor_ = 0*YEAR;
    maturity_tenor_ = 0*YEAR;

    next_futures_date_ = -1;
  }

  /** \brief calculates date
   *
   * this method calculates date on the basis of given inputs.
   */
  void BuildLinearInstrument::datesCalculation() {
    BOOST_ASSERT_MSG(trade_date_.isValid(),"Trade date was not declared.");
    
    if (maturity_tenor_.getTimeUnit() == OVERNIGHT) {
      start_date_ = trade_date_;
      maturity_date_   = calendar_.workingDays(trade_date_,1);
      
    } else if (maturity_tenor_.getTimeUnit() == TOMORROWNEXT) {
      start_date_ = calendar_.workingDays(trade_date_,1);
      maturity_date_   = calendar_.workingDays(trade_date_,2);
      
    } else if (maturity_tenor_.getTimeUnit() == SPOTNEXT) {
      start_date_ = calendar_.getSpot(trade_date_);
      maturity_date_   = calendar_.workingDays(start_date_, 1);
      
    } else if (maturity_tenor_.getNumberOfUnits() > 0 ) {
      if (!start_date_.isValid())
	start_date_ = calendar_.getSpot(trade_date_);
      if (!maturity_date_.isValid())
	maturity_date_ = calendar_.settlementDate(trade_date_, maturity_tenor_);
    }

    if (fixing_date_.isValid() && !fra_value_date_.isValid() ) {
      fra_value_date_ = calendar_.getSpot(fixing_date_);
    }

    if (fixing_tenor_.getNumberOfUnits() > 0 && !fixing_date_.isValid()) {
      fixing_date_ = calendar_.expiryDate(trade_date_,fixing_tenor_);  
      fra_value_date_ = calendar_.settlementDate(trade_date_,fixing_tenor_);
    }

    if (!start_date_.isValid()) {
      start_date_ = calendar_.getSpot(trade_date_);
    }

    if (next_futures_date_ != -1) {
      int month = trade_date_.getMonth();
      int year  = trade_date_.getYear();
    
      int quarter = 0;
      if(month == 1  || month == 2  || month == 3) {
    	quarter = 1;
      } else if(month == 4  || month == 5  || month == 6) {
    	quarter = 2; 
      } else if(month == 7  || month == 8  || month == 9) {
    	quarter = 3; 
      } else if (month == 10 || month == 11 || month == 12) {
    	quarter = 4;  
      }

      Date nearest_futures_date(year,3*quarter,15);
      while(nearest_futures_date.getN() % 7 != WED) {
    	nearest_futures_date += 1*DAY;
      }
      
      int next_quarter = 0;
      int next_year = 0;

      if (trade_date_ <= nearest_futures_date ) {
    	next_quarter = quarter;
    	next_year    = year;
      } else {
    	next_quarter = quarter + 1;
    	next_year    = year;
    	if (next_quarter > 4) {
    	  next_quarter = 1;
    	  next_year    = year+1;
    	}
      }
      
      while (next_futures_date_ > 0) {
    	next_quarter += 1;
    	if (next_quarter > 4) {
    	  next_quarter = 1;
    	  next_year    = year+1;
    	}
    	next_futures_date_--;
      }
      futures_quarter_start_ = next_quarter;
      futures_year_start_ =next_year ;
    }
    BOOST_ASSERT_MSG( trade_date_ < maturity_date_,"Trade date later then maturity date.");
  }

}  // namespace julian
