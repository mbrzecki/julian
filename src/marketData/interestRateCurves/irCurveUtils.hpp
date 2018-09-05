#ifndef IRCURVEUTILS_HPP
#define IRCURVEUTILS_HPP

#include <utils/dataFrame.hpp>
#include <instruments/linear/_all_linear.hpp>
#include <marketData/interestRateCurves/irCurve.hpp>
#include <utils/smartPointer.hpp>

namespace julian {
namespace ir {
  /**
   * @file   irCurveUtils.hpp
   * @brief  File contains small programming tools used to handle interest curve
   */
  DataFrame getCurves(SmartPointer<Curve> c, Tenor step, Tenor end,std::string id);

  DataFrame getCalibration(const SmartPointer<ir::Curve>& ,
			   const std::vector<SmartPointer<ir::BuildingBlock> >& ,
			   const std::string id);
    
  std::vector<Deposit> readDeposit(DataFrame df, Date d, Calendar calendar);
  std::vector<FRA> readFRA(DataFrame df, Date d, Calendar calendar);
  std::vector<IRS> readIRS(DataFrame df, Date d, Calendar calendar);

  
  
}  // namespace ir
}  // namespace julian

#endif 
