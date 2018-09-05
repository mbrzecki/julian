#ifndef JULIAN_OPTIONDELTA_HPP
#define JULIAN_OPTIONDELTA_HPP

#include <pricingEngines/optionGreeks/optionGreeksDecorator.hpp>
#include <mathematics/mathUtils.hpp>

namespace julian {
  /**
   * @file   optionDelta.hpp
   * @brief  File contains implementation of OptionDelta.
   */
  /** \ingroup optiongreeks
   *  \brief Calculates option's delta.
   *
   * This method calculates Delta. Using the method _prize_ of julian::PricingEngine and _bumpSpot_ of julian::MarketModel it calculates the option sensitivity to asset prize change. 
   * Delta of option is calculated using following finite difference scheme:
   * * \f$Delta = \frac{\partial PV}{\partial Spot} \approx \frac{PV(Spot+h) - PV(Spot)}{h}\f$ when forward differencing is used 
   * * \f$Delta = \frac{\partial PV}{\partial Spot} \approx \frac{PV(Spot) - PV(Spot-h)}{h}\f$ when backward differencing is used 
   * * \f$Delta = \frac{\partial PV}{\partial Spot} \approx \frac{PV(Spot+h) - PV(Spot-h)}{2h}\f$ when central differencing is used 
   * The result is saved in map.
   * OptionDelta is a concrete decorator in decorator structure. Concrete Decorator is a class that altered alters the behaviour of Concrete Component.
   */
  class OptionDelta: public OptionGreeksDecorator {
  public:
    /** \brief Constructor
     */
    OptionDelta(SmartPointer<OptionGreeks> input, double h, NumDiffScheme scheme, std::string risk_name = "Delta"):
      OptionGreeksDecorator(input), h_(h), scheme_(scheme), risk_name_(risk_name) {}
    
    GreeksIntermediateResults calculateRisks(const SmartPointer<MarketModel>& model,
				     const SmartPointer<PricingEngine>& prizer,
				     const SmartPointer<Option>& option);
    
    std::map<std::string,double> getRisks(const SmartPointer<MarketModel>& model,
					  const SmartPointer<PricingEngine>& prizer,
					  const SmartPointer<Option>& option);
    OptionDelta* clone() const;
  
    ~OptionDelta(){};
  private:
    void CntrDelta(GreeksIntermediateResults& rr,
		   const SmartPointer<MarketModel>& model,
		   const SmartPointer<PricingEngine>& prizer,
		   const SmartPointer<Option>& option);
    void FwdDelta(GreeksIntermediateResults& rr,
		  const SmartPointer<MarketModel>& model,
		  const SmartPointer<PricingEngine>& prizer,
		  const SmartPointer<Option>& option);
    void BwdDelta(GreeksIntermediateResults& rr,
		  const SmartPointer<MarketModel>& model,
		  const SmartPointer<PricingEngine>& prizer,
		  const SmartPointer<Option>& option);
    
    double h_ ; /*!< \brief Increment used in differencing scheme.*/
    NumDiffScheme scheme_ ; /*!< \brief Scheme used in differencing.*/
    std::string risk_name_; /*!< \brief Risk name that will be used as key for result map. Default name is Delta*/
  };
}  // namespace julian

#endif
