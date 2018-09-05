#include <pricingEngines/optionGreeks/optionGreeksBuilder.hpp>
#include <pricingEngines/optionGreeks/optionPV.hpp>
#include <pricingEngines/optionGreeks/optionDelta.hpp>
#include <pricingEngines/optionGreeks/optionGamma.hpp>
#include <pricingEngines/optionGreeks/optionTheta.hpp>
#include <pricingEngines/optionGreeks/optionVanna.hpp>
#include <pricingEngines/optionGreeks/optionVega.hpp>
#include <pricingEngines/optionGreeks/optionVolga.hpp>

namespace julian {

  /** \brief Default constructor
   */
  BuildGreeksReport::BuildGreeksReport() {
    OptionPV temp;
    greeks_ = temp;

  }

  /** \brief Adds Delta to option risk report
   *
   * \param h Increment used in differencing scheme (1e-4 by default)
   * \param scheme Scheme used in differencing (Central differencing by default).
   * \param risk_name Risk name that will be used as key for result map. Default name is Delta.
   */
  BuildGreeksReport& BuildGreeksReport::withDelta(double h,
						  NumDiffScheme scheme,
						  std::string risk_name) {
    OptionDelta temp(greeks_, h, scheme, risk_name);
    greeks_ = temp;
    return *this;
  }

  /** \brief Adds Gamma to option risk report
   *
   * \param h Increment used in differencing scheme (1e-4 by default)
   * \param scheme Scheme used in differencing (Central differencing by default).
   * \param risk_name Risk name that will be used as key for result map. Default name is Gamma.
   */
  BuildGreeksReport& BuildGreeksReport::withGamma(double h ,
						  NumDiffScheme scheme,
						  std::string risk_name) {
    OptionGamma temp(greeks_,h , scheme, risk_name);
    greeks_ = temp;
    return *this;
  }

  /** \brief Adds Vega to option risk report
   *
   * \param h Increment used in differencing scheme (1e-4 by default)
   * \param scheme Scheme used in differencing (Central differencing by default).
   * \param risk_name Risk name that will be used as key for result map. Default name is Vega.
   */
  BuildGreeksReport& BuildGreeksReport::withVega(double h,
  						 NumDiffScheme scheme,
  						 std::string risk_name)  {
    OptionVega temp(greeks_,h , scheme, risk_name);
    greeks_ = temp;
    return *this;
  }

  /** \brief Adds Vanna to option risk report
   *
   * \param hs Increment used in differencing scheme for spot direction (1e-4 by default)
   * \param hv Increment used in differencing scheme for volatility direction (1e-4 by default)
   * \param risk_name Risk name that will be used as key for result map. Default name is Volga.
   */
  BuildGreeksReport& BuildGreeksReport::withVanna(double hs, double hv,
  						  std::string risk_name)  {
    OptionVanna temp(greeks_, hs, hv, risk_name);
    greeks_ = temp;
    return *this;
  }

  /** \brief Adds Volga to option risk report
   *
   * \param h Increment used in differencing scheme (1e-4 by default)
   * \param scheme Scheme used in differencing (Central differencing by default).
   * \param risk_name Risk name that will be used as key for result map. Default name is Volga.
   */
  BuildGreeksReport& BuildGreeksReport::withVolga(double h,
  						  NumDiffScheme scheme,
  						  std::string risk_name)  {
    OptionVolga temp(greeks_, h, scheme, risk_name);
    greeks_ = temp;
    return *this;
  }

  /** \brief Adds Theta to option risk report
   *
   * \param risk_name Risk name that will be used as key for result map. Default name is Theta.
   */
  BuildGreeksReport& BuildGreeksReport::withTheta(std::string risk_name)  {
    OptionTheta temp(greeks_, risk_name);
    greeks_ = temp;
    return *this;
  }
  /** \brief Creates Option Greeks risk report
   */ 
  SmartPointer<OptionGreeks> BuildGreeksReport::build() {
    return greeks_;
  }
}
