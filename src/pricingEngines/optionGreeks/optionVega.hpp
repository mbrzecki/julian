#ifndef JULIAN_OPTIONVEGA_HPP
#define JULIAN_OPTIONVEGA_HPP

#include <pricingEngines/optionGreeks/optionGreeksDecorator.hpp>
#include <mathematics/mathUtils.hpp>

namespace julian {
  /**
   * @file   optionVega.hpp
   * @brief  File contains implementation of OptionVega.
   */
   /** \ingroup optiongreeks
   *  \brief Calculates option's vega.
   *
   * This method calculates Vega. Using the method _prize_ of julian::PricingEngine and _bumpVolatility_ of julian::MarketModel it calculates the option sensitivity to asset volatility. 
   * Vega of option is can be calculated using the finite difference scheme
   * * \f$Vega = \frac{\partial PV}{\partial Vol} \approx \frac{PV(Vol+h) - PV(Vol)}{h}\f$ when forward differencing is used 
   * * \f$Vega = \frac{\partial PV}{\partial Vol} \approx \frac{PV(Vol) - PV(Vol-h)}{h}\f$ when backward differencing is used 
   * * \f$Vega = \frac{\partial PV}{\partial Vol} \approx \frac{PV(Vol+h) - PV(Vol-h)}{2h}\f$ when central differencing is used 
   *
   * The result is saved in map.
   * OptionVega is a concrete decorator in decorator structure. Concrete Decorator is a class that altered alters the behaviour of Concrete Component.
   */ 
  
  class OptionVega: public OptionGreeksDecorator {
  public:
    /** \brief Constructor
     */
    OptionVega(SmartPointer<OptionGreeks> input,double h, NumDiffScheme scheme, std::string risk_name = "Vega"):
      OptionGreeksDecorator(input), h_(h), scheme_(scheme), risk_name_(risk_name) {}

    GreeksIntermediateResults calculateRisks(const SmartPointer<MarketModel>& model,
					     const SmartPointer<PricingEngine>& prizer,
				     const SmartPointer<Option>& option);
    
    std::map<std::string,double> getRisks(const SmartPointer<MarketModel>& model,
					  const SmartPointer<PricingEngine>& prizer,
					  const SmartPointer<Option>& option);
    OptionVega* clone() const;
  
    ~OptionVega(){};
  private:
    double h_ ; /*!< \brief Increment used in differencing scheme.*/
    NumDiffScheme scheme_ ; /*!< \brief Scheme used in differencing.*/
    std::string risk_name_; /*!< \brief Risk name that will be used as key for result map. Default name is Vega*/

    void CntrVega(GreeksIntermediateResults& rr,
		  const SmartPointer<MarketModel>& model,
		  const SmartPointer<PricingEngine>& prizer,
		  const SmartPointer<Option>& option);
    void FwdVega(GreeksIntermediateResults& rr,
		 const SmartPointer<MarketModel>& model,
		 const SmartPointer<PricingEngine>& prizer,
		 const SmartPointer<Option>& option);
    void BwdVega(GreeksIntermediateResults& rr,
		 const SmartPointer<MarketModel>& model,
		 const SmartPointer<PricingEngine>& prizer,
		 const SmartPointer<Option>& option);
  };
}
#endif
