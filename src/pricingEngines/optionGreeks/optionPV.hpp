#ifndef JULIAN_OPTIONPV_HPP
#define JULIAN_OPTIONPV_HPP

#include <map>
#include <pricingEngines/optionGreeks/optionGreeks.hpp>

namespace julian {
  /**
   * @file   optionPV.hpp
   * @brief  File contains implementation of OptionPV.
   */
  /** \ingroup optiongreeks
   *  \brief Calculates PV.
   *
   * This method calculates PV. It calls the method _prize_ of julian::PricingEngine using model and option as arguments. The result is saved in map.
   * OptionPV is a concrete component in decorator structure. Concrete Component is a class that contains basic behaviour that can be altered by decorators.
   */
  
  class OptionPV: public OptionGreeks {
  public:
    OptionPV() {};
    std::map<std::string,double> getRisks(const SmartPointer<MarketModel>&,
					  const SmartPointer<PricingEngine>&,
					  const SmartPointer<Option>&);
    GreeksIntermediateResults calculateRisks(const SmartPointer<MarketModel>& model,
				     const SmartPointer<PricingEngine>& prizer,
				     const SmartPointer<Option>& option);
    OptionPV* clone() const;
    
    ~OptionPV(){};
};
  
}


#endif
