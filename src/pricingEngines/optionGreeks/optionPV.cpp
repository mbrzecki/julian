#include <pricingEngines/optionGreeks/optionPV.hpp>

namespace julian {

  /** \brief calculates the PV parameter
   *  
   *  RiskReportResults contains result map with key "PV" and value of PV, and intermediate results 
   * 
   * \return method RiskReportResults with PV
   */
  GreeksIntermediateResults OptionPV::calculateRisks(const SmartPointer<MarketModel>& model,
						   const SmartPointer<PricingEngine>& prizer,
						   const SmartPointer<Option>& option) {
    GreeksIntermediateResults ret;
    double prize = prizer->prize(model, option);
    auto tup = std::make_tuple(0.0, 0.0);
    ret.intermediate_results_[tup] = prize;
    ret.PV_and_Greeks_["PV"]  = prize;
    return ret;
  }

  /** \brief calculates the PV parameter
   *  
   * \return method returns map with key "PV" and value of PV
   */
  std::map<std::string,double> OptionPV::getRisks(const SmartPointer<MarketModel>& model,
							 const SmartPointer<PricingEngine>& prizer,
							 const SmartPointer<Option>& option) {
    auto ret = calculateRisks(model, prizer, option);
    return ret.PV_and_Greeks_;
  }
  
  /** \brief Virtual copy constructor
   */
  OptionPV* OptionPV::clone() const {
    return new OptionPV(*this);
  }

}
