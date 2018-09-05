#ifndef JULIAN_ALGEBRAICBOOTSTRAPPER_HPP
#define JULIAN_ALGEBRAICBOOTSTRAPPER_HPP

#include <marketData/interestRateCurves/estimators/irCurveEstimator.hpp>
#include <armadillo>

namespace julian {
namespace ir {
  /**
   * @file   algebraicBootstrapper.hpp
   * @brief  File contains definition of AlgebraicBootstrapper.
   */
    
  /** \ingroup irCurveEstimator
   *  \brief Interest rate curve estimating algorithm solving equation system [CFij] * [DFj] = [PRIZEi].
   *
   * Algebraic bootstrapper creates the matrix of [CFij] which is used to create the system of linear equations.
   * By solving the system the discount factors are estimated. Discount factors are used to  construct the interest rate curve. 
   * 
   *  For example: if we want to build curve using following trades: Deposit 6M, FRA 6x12, IRS 2Y below matrix is constructed
   *
    \f[ CF = \left(\begin{array}{@{}cccc@{}}
            1  & 0 & 0 & 0 \\
            -1 & 1+r_{Depo6M} & 0 & 0 \\
            0 & -1 & 1+r_{FRA 6x12} & 0 \\
	    -1 & 0 & r_{IRS 2Y} & 1+r_{IRS 2Y} \\
    \end{array}\right) \f]
   * where second row represents CF of deposit, third represents CF of FRA and the last one contains CF of IRS. First column contains CF for today, second for 6M and next columns contain CF for 1Y and 2Y.
   * 
   * Then following system of equation is solved:
    \f[ \left(\begin{array}{@{}cccc@{}}
            1  & 0 & 0 & 0 \\
            -1 & 1+r_{Depo6M} & 0 & 0 \\
            0 & -1 & 1+r_{FRA 6x12} & 0 \\
	    -1 & 0 & r_{IRS 2Y} & 1+r_{IRS 2Y} \\
    \end{array}\right) \times \left( \begin{array}{@{}c@{}} DF_{today} \\ DF_{6M} \\ DF_{1Y} \\ DF_{2Y}\end{array}\right)
     = \left( \begin{array}{@{}c@{}} 1 \\0 \\ 0 \\ 0 \end{array}\right)
    \f]
   *
   * To solve the equation number of dates when CF occurs must be equal to number of instruments. Sometimes this condition is not satisfied.
   * Usually there are not quotings for IRS11Y, but IRS12Y generates CF occurring on 11Y. This issue is resolved by creating a IRS with maturity equal to lacking date
   * using linear interpolated IRS quote. 
   *
   * \warning AlgebraicBootstrapper does not have multi-curve functionality.
   *
   * \todo Multi-curve functionality is not implemented
   **/

  class AlgebraicBootstrapper: public Estimator {
  public:
    AlgebraicBootstrapper(){};
    void calculate(const std::vector<SmartPointer<BuildingBlock> >& instruments, const CurveSettings& settings,
		   SmartPointer<Curve>& discountingCurve, SmartPointer<Curve>& projectionCurve);
    std::vector<double> getDF() const;
    std::vector<Date> getDates() const;

    std::string info() const;
      
    AlgebraicBootstrapper* clone() const;
    ~AlgebraicBootstrapper(){};
  private:
    std::vector<Date> getMaturityDates(const std::vector<SmartPointer<ir::BuildingBlock> >& instruments, const Date& today);
    void getGridDates(const std::vector<SmartPointer<ir::BuildingBlock> >& instruments);
    std::vector<Date> getLackingDates(const std::vector<Date>& maturity_dates);
    std::vector<CashFlowVector> createCFsVector(const std::vector<SmartPointer<ir::BuildingBlock> >& instruments, const std::vector<Date>& lacking_dates, Date today);
    arma::mat prepareEquationSystem(const std::vector<CashFlowVector>& cfs_vecs);
    
    std::vector<double> DFs_;  /*!< @brief Vector of discount factors*/
    std::vector<Date> dates_; /*!< @brief Vector of grid dates*/
  };
    
}  // namespace ir
}  // namespace julian

#endif
