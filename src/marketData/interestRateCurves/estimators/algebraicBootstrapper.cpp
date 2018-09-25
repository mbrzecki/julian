#include <marketData/interestRateCurves/estimators/algebraicBootstrapper.hpp>
#include <mathematics/numericalAlgorithms/derivativeRootFinder.hpp>
#include <algorithm>
#include <vector>
#include <set>
#include <mathematics/interpolation/linearInterpolation.hpp>
#include <instruments/fixedCashFlow.hpp>

namespace julian {
namespace ir {

  /** \brief virtual copy constructor
   *
   */
  AlgebraicBootstrapper* AlgebraicBootstrapper::clone() const {
    return new AlgebraicBootstrapper(*this);
  }

  /** \brief returns DFs
   *
   * Method should be called after calling method Estimator::calculate
   */
  std::vector<double> AlgebraicBootstrapper::getDF() const {
    return DFs_;
  }

  std::vector<Date> AlgebraicBootstrapper::getDates() const {
    return dates_;
  }
  /** \brief estimates the curve
   *
   * calculates method estimates the curve and saves the result into the class members
   */
  void AlgebraicBootstrapper::calculate(const std::vector<SmartPointer<BuildingBlock> >& instruments,
					const CurveSettings& settings,
					SmartPointer<Curve>& ,
					SmartPointer<Curve>& ) {
    auto maturity_dates = getMaturityDates(instruments, settings.today_);
    getGridDates(instruments);
    auto lacking_dates = getLackingDates(maturity_dates);

    auto cfs = createCFsVector(instruments, lacking_dates, settings.today_);
    auto cash_flow_matrix = prepareEquationSystem(cfs);
    
    arma::vec prices(dates_.size(), arma::fill::zeros);
    prices(0) = 1.0;

    DFs_ = arma::conv_to<std::vector<double> >::from(arma::solve(cash_flow_matrix, prices));
    dates_.erase(dates_.begin());
    DFs_.erase(DFs_.begin());
  }

  /** \brief Extracts maturity dates from benchmark instruments 
   */
  std::vector<Date> AlgebraicBootstrapper::getMaturityDates(const std::vector<SmartPointer<ir::BuildingBlock> >& instruments,
							    const Date& today) {
    std::vector<Date> maturity_dates;

    maturity_dates.push_back(today);
    for (auto i : instruments) {
      maturity_dates.push_back(i->getDate());
    }
    return maturity_dates;
  }

  /** \brief Extracts grid dates from benchmark instruments 
   *
   * Grid dates are dates of all CFs associated with benchmark instruments
   */
  void AlgebraicBootstrapper::getGridDates(const std::vector<SmartPointer<ir::BuildingBlock> >& instruments) {
    std::set<Date> grid_dates_set;

    for (auto i : instruments) {
      auto cfs = i->getCFs().first;
      for (int j = 0; j < cfs.size(); j++) {
	grid_dates_set.insert(cfs[j]->getDate());
      }
    }
    std::copy(grid_dates_set.begin(), grid_dates_set.end(), std::back_inserter(dates_));
    std::sort(dates_.begin(), dates_.end());
  }
  
  /** \brief Extracts lacking dates from benchmark instruments 
   *
   * Lacking dates are grid dates that are not maturity dates.
   * IRS contracts settled on this dates are created using interpolation of market quotings
   * of swaps. This is done to ensure unique solution of system of linear equations 
   * that are solved in process of estimating the curve,
   *
   */
  std::vector<Date> AlgebraicBootstrapper::getLackingDates(const std::vector<Date>& maturity_dates) {
    std::vector<Date> lacking_dates;
    for (auto date  : dates_) {
      if (std::find(maturity_dates.begin(), maturity_dates.end(), date ) == maturity_dates.end()) {
	lacking_dates.push_back(date);
      }
    }
    return lacking_dates;
  }
  /** \brief Creates IRS contract for lacking dates
   *
   *
   */
  std::vector<CashFlowVector> AlgebraicBootstrapper::createCFsVector(const std::vector<SmartPointer<ir::BuildingBlock> >& instruments,
								     const std::vector<Date>& lacking_dates,
								     Date today) {
    std::vector<CashFlowVector> ret;
    auto swap_rate = instruments.back()->getInterestRate();
    std::vector<Date> dates = instruments.back()->getCFs().first.getDates(); 
    std::vector<double> swaps_quotes;
    std::vector<double> swaps_tenors;

    for (auto i : instruments) {
      ret.push_back(i->getCFs().first);
      if (i->info() == "IRS") {
	swaps_quotes.push_back(i->getQuoting());
	swaps_tenors.push_back(swap_rate.yf(today, i->getDate()));
      }
    }
    LinearInterpolation inter;
    for (auto lacking_date : lacking_dates) {
      CashFlowVector temp;

      FixedCashFlow first_cf(today, dates[0], dates[0], 0.0, -100.0, true);
      temp.addCashFlow(first_cf);
      auto quote = inter(swaps_tenors, swaps_quotes, swap_rate.yf(today, lacking_date));
      for (unsigned int i = 1; i < dates.size(); i++) {
	if (lacking_date > dates[i]) {
	  FixedCashFlow cf(dates[i-1], dates[i], dates[i], quote, 100.0, swap_rate, false);
	  temp.addCashFlow(cf);
	} else if (lacking_date == dates[i]) {
	  FixedCashFlow cf(dates[i-1], dates[i], dates[i], quote, 100.0, swap_rate, true);
	  temp.addCashFlow(cf);
	} else {
	  break;
	}
      }
      ret.push_back(temp);
    }
    auto sorter = [](CashFlowVector a, CashFlowVector b) {
      Date last_date_a = a[a.size()-1]->getDate();
      Date last_date_b = b[b.size()-1]->getDate();
      return  last_date_a < last_date_b;
    };
    std::sort(ret.begin(), ret.end(), sorter);
    return ret;
  }

  /** \brief Creates CF matrix defining system of equation
   *
   * For trades: Deposit 6M, FRA 6x12, IRS 2Y following matrix is constructed
   *

    \f[ \left(\begin{array}{@{}cccc@{}}
            1  & 0 & 0 & 0 \\
            -1 & 1+r_{Depo6M} & 0 & 0 \\
            0 & -1 & 1+r_{FRA 6x12} & 0 \\
	    -1 & 0 & r_{IRS 2Y} & 1+r_{IRS 2Y} \\
    \end{array}\right) \f]
   * where second row represents CF of deposit, thirg represents CG of FRA and the last one contains CF of IRS. First column contains CF for today, second for 6M and next columns contain CF for 1Y and 2Y.
   * 
   */
  arma::mat AlgebraicBootstrapper::prepareEquationSystem(const std::vector<CashFlowVector>& cfs_vecs) {
    arma::mat ret(dates_.size(), dates_.size(), arma::fill::zeros);
    ret(0,0) = 1.0;
  
    for (unsigned int r = 1; r < dates_.size(); r++) {
      for (unsigned int c = 0; c < dates_.size(); c++) {
	Date d = dates_[c];
	auto cfs = cfs_vecs.at(r-1);
	for (int i = 0; i < cfs.size(); i++) {
	  // if CF in row r has the same date as grid date in column c put it to matrix cell A(r,c)  
	  if (cfs[i]->getDate() == d) {
	    ret(r, c) = cfs[i]->getCF();
	  }
	}
      }
    }
    return ret;
  }
  /** \brief returns name of estimator
   *
   */ 
  std::string AlgebraicBootstrapper::info() const {
    return "algebraic_bootstrapper";
  }

}  // namespace ir
}  // namespace julian
