#include <pricingEngines/optionGreeks/optionTheta.hpp>

namespace julian {

  /** \brief calculates the option's theta
   * 
   *  \f$ Theta = PV(T+1Day) -PV(T)\f$
   *
   */
  GreeksIntermediateResults OptionTheta::calculateRisks(const SmartPointer<MarketModel>& model,
						const SmartPointer<PricingEngine>& prizer,
						const SmartPointer<Option>& option) {
    auto ret = OptionGreeksDecorator::calculateRisks(model, prizer, option);
    auto date = model->getDate() + 1*DAY;
    SmartPointer<MarketModel> moved_market = model;
    moved_market->setDate(date);
    auto pv_key =  std::make_tuple(0.0, 0.0);
    ret.PV_and_Greeks_[risk_name_] = prizer->prize(moved_market, option) - ret.intermediate_results_[pv_key];
    return ret;
  }

  /** \brief returns the PV and Greek parameter
   *  
   * \return method returns map with name of Greeks as key and the value of Greeks as value
   */
  std::map<std::string,double> OptionTheta::getRisks(const SmartPointer<MarketModel>& model,
						     const SmartPointer<PricingEngine>& prizer,
						     const SmartPointer<Option>& option) {
    auto ret = calculateRisks(model, prizer, option);
    return ret.PV_and_Greeks_;
  }

  /** \brief Virtual copy constructor
   */
  OptionTheta* OptionTheta::clone() const {
    return new OptionTheta(*this);
  }
}  // namespace julian
