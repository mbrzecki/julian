#include <marketData/interestRateCurves/irCurveUtils.hpp>



namespace julian {
namespace ir {

  /** \ingroup irCurve
   * 
   * \fn  DataFrame getCurves(SmartPointer<Curve> c, Tenor step, Tenor end,std::string id)
   * \brief Function saves curve in DataFrame
   *
   * Function calculates and saves curve using following representation:
   * * Discount Factors
   * * Zero coupon rates
   * * 1 day fwd rates approximating instantaneous rate
   * * forward rates with basis: 1W, 2W, 1M, 2M, 3M, 6M
   *
   * \param c Interest rate curve 
   * \param step Time steps used to generate the dates grid 
   * \param end Tenor of last date
   * \param id Id copied to all rows of data frame
   * \return Returns data frame
   */

  DataFrame getCurves(SmartPointer<Curve> c, Tenor step, Tenor end,std::string id) {
    DataFrame df;
    Date today = c->getValuationDate();
    for (Date d = today + step; d <= today + end; d = d + step) {
      DataEntryClerk input;
      input.add("Id", id);
      input.add("Date", d);
      input.add("DF", c->DF(d));
      input.add("ZCR", c->rate(d));
      input.add("FWD1D", c->fwdRate(d, 1*DAY));
      input.add("FWD1W", c->fwdRate(d, 1*WEEK));
      input.add("FWD2W", c->fwdRate(d, 2*WEEK));
      input.add("FWD1M", c->fwdRate(d, 1*MONTH));
      input.add("FWD2M", c->fwdRate(d, 2*MONTH));
      input.add("FWD3M", c->fwdRate(d, 3*MONTH));
      input.add("FWD6M", c->fwdRate(d, 6*MONTH));

      df.append(input);
    }
    return df;
  }

  /** \ingroup irCurve
   * 
   * \fn std::vector<Deposit> readDeposit(DataFrame df,Date today, Calendar calendar)
   * \brief Function construct deposit using data stored in DataFrame 
   *
   * Data Frame must contain column:
   * * YF1: Year fraction for deposit rate 
   * * RateConvention: Compounding convention of deposit rate
   * * Rate: Quoting
   * * Tenor: Tenor of deposit
   *
   * \param df DataFrame 
   * \param today Start day of deposits  
   * \param calendar Calendar used to calculate dates of deposits
   * \return Vector of deposits
   */
  std::vector<Deposit> readDeposit(DataFrame df,Date today, Calendar calendar) {
    std::vector<Deposit> deposits;
    for (int row = 1; row <= df.getNumberOfRows(); row++) {
      auto yf    = df.getObject<YearFraction>("YF1", row);
      auto comp  = df.getObject<Compounding>("RateConvention", row); 
      auto quote = df.getDouble("Rate", row);
      Tenor tenor(df("Tenor", row));
      InterestRate rate(comp, yf);

      Deposit depo = BuildLinearInstrument()
	.usingCalendar(calendar)
	.withTradeDate(today)
	.withTenor(tenor)
	.withQuote(quote)
	.withInterestRate(rate);
      deposits.push_back(depo);
    }
    return deposits;
  }
  /** \ingroup irCurve
   * 
   * \fn  std::vector<FRA> readFRA(DataFrame df, Date today, Calendar calendar)
   * \brief Function construct FRA using data stored in DataFrame 
   *
   * Data Frame must contain column:
   * * YF1: Year fraction for FRA rate 
   * * RateConvention: Compounding convention of FRA rate
   * * Rate: Quoting
   * * FRAstart: starting tenor of FRA
   * * Tenor: Maturity of FRA
   *
   * \param df DataFrame 
   * \param today Start day of FRAs  
   * \param calendar Calendar used to calculate dates of FRAs
   * \return Vector of FRAs
   */

  
  std::vector<FRA> readFRA(DataFrame df, Date today, Calendar calendar) {
    std::vector<FRA> fras;
    for (int row = 1; row <= df.getNumberOfRows(); row++) {
      auto yf    = df.getObject<YearFraction>("YF1", row);
      auto comp  = df.getObject<Compounding>("RateConvention", row);
      auto quote = df.getDouble("Rate", row);
      auto tenor(df("Tenor", row));
      Tenor fra_tenor(df("FRAstart", row));
      InterestRate rate(comp, yf);

      FRA fra = BuildLinearInstrument()
	.usingCalendar(calendar)
	.withTradeDate(today)
	.withForwardTenors(fra_tenor, tenor)
	.withQuote(quote)
	.withInterestRate(rate);
      fras.push_back(fra);

      
    }
    return fras;
  }
  /** \ingroup irCurve
   * 
   * \fn  std::vector<IRS> readIRS(DataFrame df, Date today, Calendar calendar)
   * \brief Function construct IRS using data stored in DataFrame  
   *
   * Data Frame must contain column:
   * * YF1: Year fraction for fixed leg rate 
   * * YF2: Year fraction for floating leg rate 
   * * RateConvention: Compounding convention of swap rates
   * * Rate: Quoting
   * * FRAstart: starting tenor of FRA
   * * FreqFix: Frequency of fixed leg
   * * FreqFlo: Frequency of floating leg
   * * Tenor: Maturity of FRA
   *
   * \param df DataFrame 
   * \param today Start day of swaps  
   * \param calendar Calendar used to calculate dates of swaps
   * \return Vector of swaps
   */

  std::vector<IRS> readIRS(DataFrame df, Date today, Calendar calendar) {
    std::vector<IRS> swaps;
    for (int row = 1; row <= df.getNumberOfRows(); row++) {
      auto yf       = df.getObject<YearFraction>("YF1", row);
      auto yf2      = df.getObject<YearFraction>("YF2", row);
      auto quote    = df.getDouble("Rate", row);
      auto comp  = df.getObject<Compounding>("RateConvention", row); 
      auto freq_fix = df.getValue<Frequency>("FreqFix", row);
      auto freq_flo = df.getValue<Frequency>("FreqFlo", row);
    
      Tenor tenor(df("Tenor", row));
      InterestRate rate(comp, yf);
      InterestRate rate2(comp, yf2);
    
      IRS irs = BuildLinearInstrument()
	.usingCalendar(calendar)
	.withTradeDate(today)
	.withTenor(tenor)
	.withNotional(1000000.0)
	.withQuote(quote)
	.withInterestRateForFixedLeg(rate)
	.withInterestRateForFloatingLeg(rate2)
	.withFixedLegFrequency(freq_fix)
	.withFloatingLegFrequency(freq_flo);
      swaps.push_back(irs);
    }
    return swaps;
  }
  
  /** \ingroup irCurve
   * 
   * \fn DataFrame getCalibration(const SmartPointer<ir::Curve>& c, const std::vector<SmartPointer<ir::BuildingBlock> >& instruments, std::string id)
   * \brief Function calculates the par rate and price of provided instruments, what allows assessing calibration
   *
   * \param c Interest rate curve 
   * \param instruments Benchmark instruments used to assess calibration
   * \param id Id copied to all rows of data frame
   * \return Returns data frame
   */
  DataFrame getCalibration(const SmartPointer<ir::Curve>& c,
			   const std::vector<SmartPointer<ir::BuildingBlock> >& instruments,
			   const std::string id) {
    DataFrame df;
    for (auto i : instruments) {
      auto calib    = i->calibrate(c, c, c);
      auto par_rate = i->getParRate(c, c, c);
      auto quote    = i->getQuoting();
      DataEntryClerk input;
      input.add("Id", id);
      input.add("Date", i->getDate());
      input.add("Type", i->info());
      input.add("Quote", quote);
      input.add("ParRate", par_rate);
      input.add("Calibration", calib);
      df.append(input);
    }
    return df;
  }
}  // namespace ir
}  // namespace julian

