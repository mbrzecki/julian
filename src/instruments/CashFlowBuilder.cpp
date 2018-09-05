#include <instruments/CashFlowBuilder.hpp>

namespace julian {

  /** \brief constructor
   */
  CashFlowBuilder::CashFlowBuilder() {
    notional_ = 1.0;
    fx_rate_ = 1.0;
    additive_margin_ = 0.0;
    multiplicative_margin_ = 1.0;
    exchange_of_notional_ = true;
  }

  /** \brief provides calendar used in calculating dates
   */
  CashFlowBuilder& CashFlowBuilder::usingCalendar(const Calendar& input) {
    calendar_ = input;
    return *this;
  }

  /** \brief provides tenor of last date
   *
   * Used when end date is not provided
   */
  CashFlowBuilder& CashFlowBuilder::withTenor(const Tenor& input) {
    tenor_ = input;
    return *this;
  }

  /** \brief provides starting date
   */
  CashFlowBuilder& CashFlowBuilder::withStartDate(const Date& input) {
    start_date_ = input;
    return *this;
  }

  /** \brief payment of last CF
   *
   * If not provided end date calculated using tenor
   */
  CashFlowBuilder& CashFlowBuilder::withEndDate(const Date& input) {
    end_date_ = input;
    return *this;
  }
  
  /** \brief provide notional
   */
  CashFlowBuilder& CashFlowBuilder::withNotional(const double input) {
    notional_ = input;
    return *this;
  }

  /** \brief provides quote
   */
  CashFlowBuilder& CashFlowBuilder::withQuote(const double input) {
    quote_ = input;
    return *this;
  }

  /** \brief provide Fx Spot
   *
   */
  CashFlowBuilder& CashFlowBuilder::withFxRate(const double input) {
    fx_rate_ = input;
    return *this;
  }

  /** \brief adds margin to floating CFs
   */
  CashFlowBuilder& CashFlowBuilder::withAdditiveMargin(const double input) {
    additive_margin_ = input;
    return *this;
  }

  /** \brief adds multiplicative margin to floating CFs
   */
  CashFlowBuilder& CashFlowBuilder::withMultiplicativeMargin(const double input) {
    multiplicative_margin_ = input;
    return *this;
  }

  /** \brief provides interest rate convention
   */
  CashFlowBuilder& CashFlowBuilder::withInterestRate(const InterestRate& input) {
    rate_ = input;
    return *this;
  }

  /** \brief frequency of payments
   */
  CashFlowBuilder& CashFlowBuilder::withPaymentFrequency(Frequency f) {
    frequency_ = f;
    return *this;
  }

  /** \brief provides fixings, if fixing dates match CF dates, the value CF are set  
   */
  CashFlowBuilder& CashFlowBuilder::withFixing(const std::map<Date, double>& input) {
    fixings_ = input;
    return *this;
  }

  /** \brief builds Floating CFs 
   */
  CashFlowBuilder& CashFlowBuilder::buildFloatingCashFlows() {
    int i = 0;
    notional_ = notional_ * fx_rate_;
    if (not end_date_.isValid()) {
      end_date_ = calendar_.settlementDate(start_date_, tenor_);
    }

    if (exchange_of_notional_) {
      Date date1 = calendar_.getSpot(start_date_);
      cfv_.addCashFlow(FixedCashFlow(date1, date1, date1, 0.0, -notional_, rate_, true));
    }

    while(1) {
       Tenor t1 = i * frequency_ * MONTH;
       Tenor t2 = (i+1) * frequency_ * MONTH;
       Date fix_start = calendar_.expiryDate(start_date_, t1);
       Date acc_start = calendar_.settlementDate(start_date_, t1);
       Date fix_end   = calendar_.expiryDate(start_date_, t2);
       Date acc_end   = calendar_.settlementDate(start_date_, t2);

       if (acc_end > end_date_) {
	 break;
       } else if (acc_end == end_date_) {
	 cfv_.addCashFlow(FloatingCashFlow(acc_start, acc_end, fix_start, fix_end, acc_end, notional_, additive_margin_, multiplicative_margin_, true));
       } else {
	 auto p = fixings_.find(fix_start);
	 if (p == fixings_.end()) {
	   cfv_.addCashFlow(FloatingCashFlow(acc_start, acc_end, fix_start, fix_end, acc_end, notional_, additive_margin_, multiplicative_margin_, false));
	 } else {
	   cfv_.addCashFlow(FixedCashFlow(acc_start, acc_end, acc_end, p->second, notional_, rate_, false ));
	 }
       }
       i++;
    }
    return *this;
  }

  /** \brief builds Fixed CFs
   */
  CashFlowBuilder& CashFlowBuilder::buildFixedCashFlows() {
    if (exchange_of_notional_) {
      fixedCFWithExchangeOfNotional();
    } else {
      fixedCFWithoutExchangeOfNotional();
    }
    
    return *this;
  }
  
  /** \brief If exchange of notional is set to true, notional is added to first and last CF
   */
  CashFlowBuilder& CashFlowBuilder::withExchangeOfNotional(bool input) {
    exchange_of_notional_ = input;
    return *this;
  }
  
  /** \brief Convert CashFlowBuilder to CashFlowVector
   *
   */
  CashFlowBuilder::operator CashFlowVector() {  
    return cfv_;
  }
  /** \brief Constructs the CashFlowVector with fixed cash flows, the first and the last CF contain notional
   */
  void CashFlowBuilder::fixedCFWithExchangeOfNotional() {
    int i = 1;
    notional_ = notional_ * fx_rate_;
    if (not end_date_.isValid()) {
      end_date_ = calendar_.settlementDate(start_date_, tenor_);
    }

    Date date1 = calendar_.getSpot(start_date_); 

    cfv_.addCashFlow(FixedCashFlow(date1, date1, date1, 0.0, -notional_, rate_, true));

    while(1) {
      Tenor t = i * frequency_ * MONTH;
      Date date2 = calendar_.settlementDate(start_date_, t);
      
      if (date2 < end_date_) {
	cfv_.addCashFlow(FixedCashFlow(date1, date2, date2, quote_, notional_, rate_, false));
      } else if (date2 == end_date_) {
	cfv_.addCashFlow(FixedCashFlow(date1, date2, date2, quote_, notional_, rate_, true));
      } else if (cfv_[cfv_.size()-1]->getDate() != end_date_ ) {
	cfv_.addCashFlow(FixedCashFlow(date1, date2, end_date_, quote_, notional_, rate_, true));
	break;
      } else  {
	break;
      }
      
      i++;
      date1 = date2;
      
    }
    
  }

  /** \brief Constructs the CashFlowVector with fixed cash flows,
   */ 
  void CashFlowBuilder::fixedCFWithoutExchangeOfNotional() {
    int i = 0;
    notional_ = notional_ * fx_rate_;
    if (not end_date_.isValid()) {
      end_date_ = calendar_.settlementDate(start_date_, tenor_);
    }

    Tenor t1 = i * frequency_ * MONTH;
    Date date1 = calendar_.settlementDate(start_date_, t1);

    while(1) {
      Tenor t2 = (i+1) * frequency_ * MONTH;
      Date date2 = calendar_.settlementDate(start_date_, t2);

      if (date2 > end_date_)
	break;
      
      cfv_.addCashFlow(FixedCashFlow(date1, date2, date2, quote_, notional_, rate_, false));
      
      i++;
      t1 = t2;
      date1 = date2;
    }
  }
  
} //  namespace julian

