#include <marketData/interestRateCurves/interpolatedCurve.hpp>
#include <iomanip>
#include <string>
#include <interestRates/simpleRate.hpp>
#include <dates/yearFractions/ACT365.hpp>
#include <mathematics/interpolation/linearInterpolation.hpp>
#include <marketData/interestRateCurves/interpolators/interpolateZCRate.hpp>
#include <marketData/interestRateCurves/interpolators/irCurveCompoundedInterpolator.hpp>
#include <marketData/interestRateCurves/interpolators/extrapolateFlatZCR.hpp>


namespace julian {
namespace ir {
  /*! \name Constructors
   */
  //@{

  /** \brief Default constructor
   * 
   */
  InterpolatedCurve::InterpolatedCurve(){}

  /** \brief Constructor
   *
   */
  InterpolatedCurve::InterpolatedCurve(Date today,std::vector<Date> dates,std::vector<double> dfs, InterestRate rate,
				       SmartPointer<Interpolator> interpolator, SmartPointer<Extrapolator> extrapolator,
				       Calendar calendar,double fx_spot){
    today_ = today;
    calendar_ = calendar;
    rate_ = rate;

    interpolator_ = interpolator;
    extrapolator_ = extrapolator;

    fx_spot_ = fx_spot;

    dates_ = dates;
    dfs_ = dfs;
  }

  /** \brief Constructor
   *
   * Constructor creates curve basing on the CurveSettings provided
   */
  InterpolatedCurve::InterpolatedCurve(CurveSettings settings, std::vector<Date> dates, std::vector<double> DFs) {
    today_ = settings.today_;
    calendar_ = settings.calendar_;
    rate_ = settings.rate_;

    interpolator_ = settings.interpolator_;
    extrapolator_ = settings.extrapolator_;

    fx_spot_ = settings.fx_spot_;

    dates_ = dates;
    dfs_ = DFs;
  }

  //@}

  /*! \name Output getters
   */
  //@{

  /** \brief get DF
   *
   * This method calculate discount factor for a given date.
   */
  double InterpolatedCurve::DF(Date date) const {
    Date firstDate = dates_.front();
    Date lastDate  = dates_.back();
    
    if (date < today_ ) return 0.0;
    if (date == today_) return 1.0;

    if (firstDate <= date && date <= lastDate)
      return (*interpolator_)(calendar_, rate_, today_, dates_, dfs_, date);
    else
      return (*extrapolator_)(calendar_, rate_, today_, dates_, dfs_, date);
  }

  /** \brief get forward DF
   *
   * This method calculate forward discount factor for a period defined by two dates.
   */
  double InterpolatedCurve::DF(Date d1, Date d2) const {
    return  DF(d2) / DF(d1);
  }

  /** \brief get DF
   *
   * This method calculate discount factor for a given tenor.
   */
  double InterpolatedCurve::DF(Tenor t) const {
    Date d = calendar_.settlementDate(today_, t);
    return DF(d);
  }

  /** \brief get forward DF
   *
   * This method calculate discount factor for a period defined by two tenors.
   */
  double InterpolatedCurve::DF(Tenor t1, Tenor t2) const {
    Date d1 = calendar_.settlementDate(today_, t1);
    Date d2 = calendar_.settlementDate(today_, t2);
    return DF(d1, d2);
  }

  /** \brief get capitalization
   *
   * This method calculate the value of 1 monetary unit invested today and received on date d.
   */
  double InterpolatedCurve::capitalization(Date d) const {
    return 1 / DF(d);
  }

  /** \brief get capitalization
   *
   * This method calculate the value of 1 monetary unit invested today and received on date calculated on the basis of given tenor.
   */
  double InterpolatedCurve::capitalization(Tenor t) const {
    return 1 / DF(t);
  }

  /** \brief get forward capitalization
   *
   * This method calculate the value of 1 monetary unit invested on date d1 and received on date d2.
   */
  double InterpolatedCurve::capitalization(Date d1,Date d2) const { 
    return 1 / DF(d1, d2);
  }

  /** \brief get forward capitalization
   *
   * This method calculate the value of 1 monetary unit invested on date d1 (calculated on the basis of tenor t1)  and received on date d2 (calculated on the basis of tenor t2).
   */
  double InterpolatedCurve::capitalization(Tenor t1, Tenor t2) const {
    return 1 / DF(t1, t2);
  }

  /** \brief get coupon
   *
   * This method calculate the revenue on 1 monetary unit invested today and received on date d.
   */ 
  double InterpolatedCurve::coupon(Date d) const {
    return capitalization(d) - 1;
  }

  /** \brief get coupon
   *
   * This method calculate the revenue on 1 monetary unit invested today and received on date d calculated on basis of tenor t.
   */
  double InterpolatedCurve::coupon(Tenor t) const {
    return capitalization(t) - 1;
  }

  /** \brief get coupon
   *
   * This method calculate the revenue on 1 monetary unit invested on date d1 and received on date d2.
   */
  double InterpolatedCurve::coupon(Date d1, Date d2) const {
    return capitalization(d1, d2) - 1;
  }

  /** \brief get coupon
   *
   * This method calculate the revenue on 1 monetary unit invested on date d1 calculated on the basis teno1 and received on date d2 calculated on the basis of tenor t2.
   */
  double InterpolatedCurve::coupon(Tenor t1, Tenor t2) const {
    return capitalization(t1, t2) - 1;
  }

  /** \brief get zero coupon rate
   *
   * The zero coupon rate for date d is the yield of zero coupon bond which matures on date d. The rate returned by this method is given in curve's interest rate convention.
   */
  double InterpolatedCurve::rate(Date d) const {
    return rate_.zcRate(today_, d, DF(d));
  }

  /** \brief get zero coupon rate
   *
   * The zero coupon rate for tenor t is the yield of zero coupon bond which matures at t. The rate returned by this method is given in curve's interest rate convention.
   */
  double InterpolatedCurve::rate(Tenor t) const {
    return rate(calendar_.settlementDate(today_, t));
  }

  /** \brief get zero coupon rate
   *
   * The zero coupon rate for date d is the yield of zero coupon bond which matures on date d. The rate returned by this method is given in provided interest rate convention.
   */
  double InterpolatedCurve::rate(Date d, InterestRate rate_given) const {
    return rate_given.zcRate(today_, d, DF(d));
  }

  /** \brief get zero coupon rate
   *
   * The zero coupon rate for tenor t is the yield of zero coupon bond which matures at t. The rate returned by this method is given in provided interest rate convention.
   */
  double InterpolatedCurve::rate(Tenor t, InterestRate rate_given) const {
    return rate(calendar_.settlementDate(today_, t), rate_given);
  }

  /** \brief get forward rate
   *
   * The forward rate between d1 and d2 is the yield of zero coupon bond that will commence at date d1 and matures at date d2.  The rate returned by this method is given in curve's interest rate convention.
   */
  double InterpolatedCurve::fwdRate(Date d1, Date d2) const {
    return rate_.fwdRate(d1, d2, DF(d1), DF(d2));
  }

  /** \brief get forward rate
   *
   * The forward rate between d1 and d2 ( date calculated on the basis of provided tenors) is the yield of zero coupon bond that will commence at date d1 and matures at date d2.  The rate returned by this method is given in curve's interest rate convention.
   */
  double InterpolatedCurve::fwdRate(Tenor t1, Tenor t2) const {
    return fwdRate(calendar_.settlementDate(today_, t1), calendar_.settlementDate(today_, t2));
  }

  /** \brief get forward rate
   *
   * The forward rate between d1 and d2 ( date d2 calculated on the basis of provided tenor t) is the yield of zero coupon bond 
   * that will commence at date d1 and matures at date d2.  The rate returned by this method is given in curve's interest rate convention.
   */
  double InterpolatedCurve::fwdRate(Date d, Tenor t) const {
    return fwdRate(d, calendar_.settlementDate(today_, t));
  }

  /** \brief get forward rate
   *
   * The forward rate between d1 and d2 is the yield of zero coupon bond that will commence at date d1 and matures at date d2 (convention of this interest rate is provided as argument of method).
   */
  double InterpolatedCurve::fwdRate(Date d1, Date d2, InterestRate rate) const {
    return rate.fwdRate(d1, d2, DF(d1), DF(d2));
  }

  /** \brief get forward rate
   *
   * The forward rate between d1 and d2 ( date calculated on the basis of provided tenors) is the yield of zero coupon bond that will commence at date d1 and matures at date d2. (convention of this interest rate is provided as argument of method).
   */
  double InterpolatedCurve::fwdRate(Tenor t1, Tenor t2, InterestRate rate) const{
    Date d1 = calendar_.settlementDate(today_, t1);
    Date d2 = calendar_.settlementDate(today_, t2);
    return fwdRate(d1, d2, rate);
  }

  /** \brief get forward rate
   *
   * The forward rate between d1 and d2 ( date d2 calculated on the basis of provided tenor) is the yield of zero coupon bond that will commence at date d1 and matures at date d2. (convention of this interest rate is provided as argument of method).
   */
  double InterpolatedCurve::fwdRate(Date d, Tenor t, InterestRate rate) const {
    Date d2 = calendar_.settlementDate(today_, t);
    return fwdRate(d, d2, rate);
  }

  /** \brief get discount factors for given dates
   *
   * This method calculates discount factor for dates provided as STL vector.
   */
  std::vector<double> InterpolatedCurve::getDFs(std::vector<Date> dates) const {
    std::vector<double> result;
    for (auto d : dates)
      result.push_back(DF(d));
    return result;	       
  }

  /** \brief get discount factors
   *
   * This method returns discount factors that defines swap curve
   */
  std::vector<double> InterpolatedCurve::getDFs() const {
    return dfs_;
  }
  
  /** \brief get zero coupon rates
   *
   * This method returns vector of zero coupon rates calculated for grid dates of the curve.
   */
  std::vector<double> InterpolatedCurve::getRates() const {
    std::vector<double> zcr;
    for (auto d : dates_)
      zcr.push_back(rate(d));
    return zcr;
  }

  /** \brief get zero coupon rates
   *
   * This method returns vector of zero coupon rates calculated for grid dates of the curve. The convention of the rates is given as argument of the method.
   */
  std::vector<double> InterpolatedCurve::getRates(InterestRate r) const {
    std::vector<double> zcr;
    for(auto d : dates_)
      zcr.push_back(r.zcRate(today_, d, DF(d)));
    return zcr;
  }

  /** \brief get forward rates
   *
   * Method returns forward rates. The first forward rate is the rate between today and first date node. The rest are calculated as rates between nodal points of swap curve.
   */
  std::vector<double> InterpolatedCurve::getFwdRates() const {  
    std::vector<double> fwds;
    if (dates_.front() == today_) {
      for (unsigned int i = 0; i < dates_.size()-1; i++) {
	double aux = fwdRate(dates_.at(i), dates_.at(i+1));
	fwds.push_back(aux);    
      }
    } else  {
      double aux = fwdRate(today_, dates_.at(0));
      fwds.push_back(aux);	  
      for(unsigned int i = 0; i < dates_.size()-1; i++) {
	aux = fwdRate(dates_.at(i), dates_.at(i+1));
	fwds.push_back(aux);	    
      }
    }
    return fwds;
  }

  /** \brief get forward rates
   *
   * Method returns forward rates. The first forward rate is the rate between today and first date node. 
   * The rest are calculated as rates between nodal points of swap curve. 
   * The convention of the rates is given as argument of the method.
   */
  std::vector<double> InterpolatedCurve::getFwdRates(InterestRate r) const {
    std::vector<double> fwd;
    if (dates_.at(0) == today_) {
      for(unsigned int i = 0; i < dates_.size() - 1; i++) {
	double df1 = DF(dates_.at(i));
	double df2 = DF(dates_.at(i+1));
	double calc = r.fwdRate(dates_.at(i), dates_.at(i+1), df1, df2); 
	fwd.push_back(calc);
      }
    } else {
      double calc = r.fwdRate(today_,dates_.at(0) ,1.0, dfs_.at(0));
      fwd.push_back(calc);

      for (unsigned int i = 0; i <dates_.size()-1; i++) {
	double df1 = DF(dates_.at(i));
	double df2 = DF(dates_.at(i+1));
	double calc = r.fwdRate(dates_.at(i), dates_.at(i+1), df1, df2); 
	fwd.push_back(calc);
      }
    }
    return fwd;
  }

  /** \brief get calendar
   *
   * Method returns the calendar defined for the curve.
   */
  Calendar InterpolatedCurve::getCalendar() const {
    return calendar_;
  }

  /** \brief get interpolator
   *
   * Method returns the interpolator defined for the curve.
   */
  SmartPointer<ir::Interpolator> InterpolatedCurve::getInterpolator() const {
    return interpolator_;
  }

  /** \brief get extrapolator
   *
   * Method returns the extrapolator defined for the curve.
   */
  SmartPointer<ir::Extrapolator> InterpolatedCurve::getExtrapolator() const {
    return extrapolator_;
  }

  /** \brief get interest rate convention
   *
   * Method returns the convention of interest rate.
   */
  InterestRate InterpolatedCurve::getInterestRate() const {
    return rate_;
  }

  //@}

  /*! \name Getters
   */
  //@{

  /** \brief get today dates
   *
   * The method returns the date for which curve was defined.
   */
  Date InterpolatedCurve::getValuationDate() const {
    return today_;
  }

  /** \brief get spot date
   *
   * The method returns the spot date of the curve.
   */
  Date InterpolatedCurve::getSpotDate() const {
    return calendar_.getSpot(today_);
  }

  /** \brief get dates vector
   *
   * The method returns the node points of the curve.
   */
  std::vector<Date> InterpolatedCurve::getDates() const {
    return dates_;
  }

  /** \brief returns the number of nodal dates.
   *
   * The size of the curve is defined as the number of date nodal points. 
   */
  int InterpolatedCurve::getSize() const {
    return dates_.size();
  }
  //@}

  /*! \name Setters
   */
  //@{
  /** \brief set fx spot for the curve
   *
   * Sets fx spot rate for a given curve
   */
  void InterpolatedCurve::setFxSpot(double input) {
    fx_spot_ = input;
  }

  /** \brief change nodal dates of the curve
   *
   * Method gives the STL vector of dates. The DFs for this dates are calculated. Then curve is redefined by changing original date grid by new one and changing the DF vector.
   */
  void InterpolatedCurve::setDates(std::vector<Date> d) {
    dfs_ = getDFs(d);
    dates_ = d;
  }

  /** \brief change nodal dates of the curve
   *
   * Method provides the tenor. On the basis of this tenor grid date is establish and then this new grid date is used to redefine curve. 
   * This method enables to create curve that has fixed inter-space between nodal dates.
   */
  void InterpolatedCurve::setDates(Tenor t) {
     std::vector<Date> dates;
     Date lastDate = dates_.back();

    if (calendar_.getSpot(today_) > calendar_.getON(today_))
      dates.push_back(calendar_.getON(today_));

    if (calendar_.getSpot(today_) > calendar_.getTN(today_))
      dates.push_back(calendar_.getTN(today_));

    Date d_iter = calendar_.getSpot(today_);
    int i = 1;
    while (d_iter <= lastDate) {
      dates.push_back(d_iter);	
      Date d = calendar_.settlementDate(today_, ((i * t.getNumberOfUnits()) * t.getTimeUnit()));
      d = calendar_.adjust(d);
      d_iter = d;
      i++;
     }
    setDates(dates);
  }

  /** \brief set discount factors
   *
   * This method change DF of the curve.
   */
  void InterpolatedCurve::setDFs(std::vector<double> input) {
    dfs_ = input;
  }

  /** \brief set zero coupon rates
   *
   * This method change the discount factor of the curve on the basis of zero coupon rates provided.
   */
  void InterpolatedCurve::setRates(std::vector<double> input) {
    for(unsigned int i = 0; i < input.size(); i++) {
      double df = rate_.DF(today_, dates_.at(i), input.at(i));
      dfs_.at(i) = df;
    }
  }

  /** \brief set forward rate
   *
   * This method change the discount factor of the curve on the basis of forward rates provided.
   */
  void InterpolatedCurve::setFwdRates(std::vector<double> input) {
    double df = rate_.DF(today_, dates_.at(0), input.at(0));
    dfs_.at(0) = df;

    for (unsigned int i = 1; i < input.size(); i++) {
      df  = rate_.DF(dates_.at(i-1), dates_.at(i), input.at(i));
      df *= dfs_.at(i-1); 
      dfs_.at(i) =  df;
    }
  }

  //@}

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, InterpolatedCurve& c) {
    s << "Object: InterpolatedCurve"
      << "\nAsOfDate: " << c.today_
      << "\nInterestRate: " << c.rate_ 
      << "\nInterpolation: " << c.interpolator_->info() 
      << "\nExtrapolation: " << c.extrapolator_->info() 
      << "\nDate \t\tDF \t\tZCR\t\tForwards\n";

    Date temp = c.dates_.back();
    for (auto d : c.dates_) {
      double a = c.DF(d);
      double r = c.rate(d);
      double f = 0.0;
      if (d < c.dates_.back()) {
	f = c.fwdRate(temp, d);
      }
      s << d << "\t"
	<< std::fixed << std::setprecision(10) << a << "\t"
	<< std::setprecision(6) << r*100 << "%" << "\t"
	<< f*100 << "%" << "\t\n";
      temp = d;
    }
    std::setprecision(6);
    return s;
  }

  /** \brief get FxSpot
   *
   * Method returns the value of FxSpot.
   */
  double InterpolatedCurve::getFxSpot() const {
    return fx_spot_;
  }

  /** \brief calculate year fraction
   *
   * By this method one can calculate year fraction between to dates. Convention of year fraction is compliant with convention of year fraction of swap curve interest rate.
   */
  double InterpolatedCurve::calculateYF(Date d1, Date d2) const {
    return rate_.yf(d1, d2);
  }

  /** \brief Returns settings of  curve
   *
   * Settings are passed using julian::CurveSettings structure
   */
  CurveSettings InterpolatedCurve::getSettings() const {
    CurveSettings settings {today_, rate_, interpolator_, extrapolator_, calendar_, fx_spot_};
    return settings;
  }

  InterpolatedCurve* InterpolatedCurve::clone() const {
    return new InterpolatedCurve(*this);
  }

}  // namespace ir
}  // namespace julian
