#ifndef JULIAN_OPTIONGAMMA_HPP
#define JULIAN_OPTIONGAMMA_HPP

#include <pricingEngines/optionGreeks/optionGreeksDecorator.hpp>
#include <mathematics/mathUtils.hpp>

namespace julian {
  /**
   * @file   optionGamma.hpp
   * @brief  File contains implementation of OptionGamma.
   */
  /** \ingroup optiongreeks
   *  \brief Calculates option's gamma.
   *
   * This method calculates Gamma. Using the method _prize_ of julian::PricingEngine and _bumpSpot_ of julian::MarketModel  it calculates the second derivative of option prize wrt to spot prize. 
   * Delta of option is calculated using the finite difference scheme
   * * \f$\Gamma = \frac{\partial^2 PV}{\partial Spot^2} \approx \frac{PV(Spot+2h) - 2PV(Spot+h) + PV(Spot)}{h^2}\f$ when forward scheme is used,
   * * \f$\Gamma = \frac{\partial^2 PV}{\partial Spot^2} \approx \frac{PV(Spot) - 2PV(Spot-h) + PV(Spot-2h)}{h^2}\f$ when backward scheme is used,
   * * \f$\Gamma = \frac{\partial^2 PV}{\partial Spot^2} \approx \frac{PV(Spot+h) - 2PV(Spot) + PV(Spot-h)}{h^2}\f$ when central scheme is used.
   *
   * The result is saved in map.
   * OptionGamma is a concrete decorator in decorator structure. Concrete Decorator is a class that altered alters the behaviour of Concrete Component.
   */
  
  class OptionGamma: public OptionGreeksDecorator {
  public:
    /** \brief constructor
     */
    OptionGamma(SmartPointer<OptionGreeks> input, double h, NumDiffScheme scheme, std::string risk_name = "Gamma" ):
      OptionGreeksDecorator(input), h_(h), scheme_(scheme), risk_name_(risk_name) {}
    
    GreeksIntermediateResults calculateRisks(const SmartPointer<MarketModel>& model,
					     const SmartPointer<PricingEngine>& prizer,
					     const SmartPointer<Option>& option);
    
    std::map<std::string,double> getRisks(const SmartPointer<MarketModel>& model,
					  const SmartPointer<PricingEngine>& prizer,
					  const SmartPointer<Option>& option);
    
    OptionGamma* clone() const;
    
    ~OptionGamma(){};
  private:
    void CntrGamma(GreeksIntermediateResults& rr,
		   const SmartPointer<MarketModel>& model,
		   const SmartPointer<PricingEngine>& prizer,
		   const SmartPointer<Option>& option);
    void FwdGamma(GreeksIntermediateResults& rr,
		  const SmartPointer<MarketModel>& model,
		  const SmartPointer<PricingEngine>& prizer,
		  const SmartPointer<Option>& option);
    void BwdGamma(GreeksIntermediateResults& rr,
		  const SmartPointer<MarketModel>& model,
		  const SmartPointer<PricingEngine>& prizer,
		  const SmartPointer<Option>& option);
    
    double h_;/*!< \brief Increment used in differencing scheme.*/
    NumDiffScheme scheme_ ; /*!< \brief Scheme used in differencing.*/
    std::string risk_name_; /*!< \brief Risk name that will be used as key for result map. Default name is Gamma*/
  };
}
#endif
