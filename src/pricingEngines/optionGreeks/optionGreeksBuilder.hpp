#ifndef JULIAN_OPTIONGREEKSBUILDER_HPP
#define JULIAN_OPTIONGREEKSBUILDER_HPP

#include <pricingEngines/optionGreeks/optionGreeks.hpp>
#include <mathematics/mathUtils.hpp>


namespace julian {
/**
   * @file   optionGreeksBuilder.hpp
   * @brief  Class constructing PV and Greeks objects.
   */
   
  /** \ingroup optiongreeks
   * \brief Option Greeks builder
   *
   * Class is used to construct option Greeks decorator.
   */
  class BuildGreeksReport {
  public:
    BuildGreeksReport();

    BuildGreeksReport& withDelta(double h = 1e-4,
				 NumDiffScheme scheme = NumDiffScheme::CNTR,
				 std::string risk_name = "Delta");

    BuildGreeksReport& withGamma(double h = 1e-4,
				 NumDiffScheme scheme = NumDiffScheme::CNTR,
				 std::string risk_name = "Gamma");

    BuildGreeksReport& withVega(double h = 1e-4,
				NumDiffScheme scheme = NumDiffScheme::CNTR,
				std::string risk_name = "Vega");

    BuildGreeksReport& withVanna(double hs = 1e-4, double hv = 1e-4,
				 std::string risk_name = "Vanna");

    BuildGreeksReport& withVolga(double h = 1e-4,
				 NumDiffScheme scheme = NumDiffScheme::CNTR,
				 std::string risk_name = "Volga");

    BuildGreeksReport& withTheta(std::string risk_name = "Theta");
    
    SmartPointer<OptionGreeks> build();
    
    ~BuildGreeksReport(){};
  private:
    SmartPointer<OptionGreeks> greeks_; /*!< \brief Options greeks risk report*/
  };
 
  
}  // namespace julian

#endif /* JULIAN_OPTIONGREEKSBUILDER_HPP */

