#ifndef JULIAN_OPTIONVOLGA_HPP
#define JULIAN_OPTIONVOLGA_HPP

#include <pricingEngines/optionGreeks/optionGreeksDecorator.hpp>
#include <mathematics/mathUtils.hpp>

namespace julian {
  /**
   * @file   optionVolga.hpp
   * @brief  File contains implementation of OptionVolga.
   */
  /** \ingroup optiongreeks
   *  \brief Calculates option's Volga.
   *
   * This method calculates Volga. Using the method _prize_ of julian::PricingEngine and _bumpVolatility/bumpSpot_ of julian::MarketModel it calculates the cross-derivative of option prize wrt to spot and volatility.
   *
   * Volga of option is calculated using the finite difference scheme
   * * \f$Volga = \frac{\partial^2 PV}{\partial Vol^2} \approx \frac{PV(Vol+2h) - 2PV(Vol+h) + PV(Vol)}{h^2}\f$ when forward scheme is used,
   * * \f$Volga = \frac{\partial^2 PV}{\partial Vol^2} \approx \frac{PV(Vol) - 2PV(Vol-h) + PV(Vol-2h)}{h^2}\f$ when backward scheme is used,
   * * \f$Volga = \frac{\partial^2 PV}{\partial Vol^2} \approx \frac{PV(Vol+h) - 2PV(Vol) + PV(Vol-h)}{h^2}\f$ when central scheme is used.
   *
   * The result is saved in map.
   * OptionVolga is a concrete decorator in decorator structure. Concrete Decorator is a class that altered alters the behaviour of Concrete Component.
   *
   */
  class OptionVolga: public OptionGreeksDecorator {
  public:
    /** \brief Constructor
     */
    OptionVolga(SmartPointer<OptionGreeks> input, double h, NumDiffScheme scheme, std::string risk_name = "Volga"):
      OptionGreeksDecorator(input), scheme_(scheme), h_(h), risk_name_(risk_name) {}
    std::map<std::string,double> getRisks(const SmartPointer<MarketModel>& model,
					  const SmartPointer<PricingEngine>& prizer,
					  const SmartPointer<Option>& option);
    GreeksIntermediateResults calculateRisks(const SmartPointer<MarketModel>& model,
					     const SmartPointer<PricingEngine>& prizer,
					     const SmartPointer<Option>& option);
    OptionVolga* clone() const;
  
    ~OptionVolga(){};
  private:
    NumDiffScheme scheme_ ; /*!< \brief Scheme used in differencing.*/
    double h_ ; /*!< \brief Increment used in differencing scheme for volatility direction.*/
    std::string risk_name_; /*!< \brief Risk name that will be used as key for result map. Default name is Volga*/
	
    void CntrVolga(GreeksIntermediateResults& rr,
		   const SmartPointer<MarketModel>& model,
		   const SmartPointer<PricingEngine>& prizer,
		   const SmartPointer<Option>& option);
    void FwdVolga(GreeksIntermediateResults& rr,
		  const SmartPointer<MarketModel>& model,
		  const SmartPointer<PricingEngine>& prizer,
		  const SmartPointer<Option>& option);
    void BwdVolga(GreeksIntermediateResults& rr,
		  const SmartPointer<MarketModel>& model,
		  const SmartPointer<PricingEngine>& prizer,
		  const SmartPointer<Option>& option);
  };
}  // namespace julian

#endif
