#include <marketData/marketDataUtils.hpp>

namespace julian {

  
  /** \ingroup marketdata 
   * \brief Function implies interest rate curve basing on discounting curve, forward curve and current asset price
   *
   * For each grid date of discounting_curve discount factor is calculated using to formula:
   * \f[DF(date) = \frac{DF_{disc}(date) * Fwd(date)}{S}\f]
   *
   * Function can be useful to calculate dividend curve basing on discount curve and forward prices of asset.
   *
   * \param discounting_curve discounting curve used to calculate DF
   * \param forward_curve forward curve used to calculate Fwd 
   * \param asset_price actual asset price
   * \return interest rate curves with settings copied from discounting_curve
   */
  ir::InterpolatedCurve calculateYieldCurve(ir::InterpolatedCurve discounting_curve, ForwardCurve forward_curve, double asset_price) {
    auto dates = forward_curve.getDates();
    std::vector<double> dfs;
    for (auto d : dates) {
      double df = discounting_curve.DF(d) * forward_curve.getForwardPrice(d) / asset_price;
      dfs.push_back(df);
    }
    auto settings = discounting_curve.getSettings();
    return ir::InterpolatedCurve(settings, dates, dfs);
  }

}
