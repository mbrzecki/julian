#include <pricingEngines/optionGreeks/optionDelta.hpp>

namespace julian {

  /** \brief Calculates the option's delta
   *  
   * Delta of option is calculated using the finite difference scheme
   * * \f$Delta = \frac{\partial PV}{\partial Spot} \approx \frac{PV(Spot+h) - PV(Spot)}{h}\f$ when forward differencing is used 
   * * \f$Delta = \frac{\partial PV}{\partial Spot} \approx \frac{PV(Spot) - PV(Spot-h)}{h}\f$ when backward differencing is used 
   * * \f$Delta = \frac{\partial PV}{\partial Spot} \approx \frac{PV(Spot+h) - PV(Spot-h)}{2h}\f$ when central differencing is used 
   *
   */
  GreeksIntermediateResults OptionDelta::calculateRisks(const SmartPointer<MarketModel>& model,
						const SmartPointer<PricingEngine>& prizer,
						const SmartPointer<Option>& option)  {
    auto ret = OptionGreeksDecorator::calculateRisks(model, prizer, option);
    switch (scheme_) {
    case NumDiffScheme::CNTR: {
      CntrDelta(ret, model, prizer, option);
    } break;
    case NumDiffScheme::FWD: {
      FwdDelta(ret, model, prizer, option);
    } break;
    case NumDiffScheme::BWD: {
      BwdDelta(ret, model, prizer, option);
    } break;
    }
    return ret;
  }

  /** \brief returns the PV and Greek parameter
   *  
   * \return method returns map with name of Greeks as key and the value of Greeks as value
   */
  std::map<std::string,double> OptionDelta::getRisks(const SmartPointer<MarketModel>& model,
						     const SmartPointer<PricingEngine>& prizer,
						     const SmartPointer<Option>& option) {
    auto ret = calculateRisks(model, prizer, option);
    return ret.PV_and_Greeks_;
  }

  /** \brief Calculates delta using central differencing scheme
   *
   * Method checks if the PV for a given market shifts were calculated. If yes, it uses them in estimating the Delta. 
   * If they were not calculated, it performs calculations, saves them and then calculates Delta. 
   */
  void OptionDelta::CntrDelta(GreeksIntermediateResults& rr,
			      const SmartPointer<MarketModel>& model,
			      const SmartPointer<PricingEngine>& prizer,
			      const SmartPointer<Option>& option) {
    double fwd, bwd;
    auto fwd_key = std::make_tuple(h_, 0.0);
    auto bwd_key = std::make_tuple(-h_, 0.0);
    if (rr.intermediate_results_.find(fwd_key) == rr.intermediate_results_.end()) {
      SmartPointer<MarketModel> bumped = model;
      bumped->bumpAssetPrize(h_);
      fwd = prizer->prize(bumped, option);
      rr.intermediate_results_[fwd_key] = fwd;
    } else {
      fwd = rr.intermediate_results_[fwd_key];
    }
    if ( rr.intermediate_results_.find(bwd_key) == rr.intermediate_results_.end() ) {
      SmartPointer<MarketModel> bumped = model;
      bumped->bumpAssetPrize(-h_);
      bwd = prizer->prize(bumped, option);
      rr.intermediate_results_[bwd_key] = bwd;
    } else {
      bwd = rr.intermediate_results_[bwd_key];
    }
    rr.PV_and_Greeks_[risk_name_] = (fwd - bwd) / (2.0 * h_);
  }

  /** \brief Calculates delta using forward differencing scheme
   *
   * Method checks if the PV for a given market shifts were calculated. If yes, it uses them in estimating the Delta. 
   * If they were not calculated, it performs calculations, saves them and then calculates Delta. 
   */
  void OptionDelta::FwdDelta(GreeksIntermediateResults& rr,
			     const SmartPointer<MarketModel>& model,
			     const SmartPointer<PricingEngine>& prizer,
			     const SmartPointer<Option>& option)  {
    auto pv_key =  std::make_tuple(0.0, 0.0);
    auto pv = rr.intermediate_results_[pv_key];

    auto fwd_key = std::make_tuple(h_, 0.0);
    double fwd;

    if (rr.intermediate_results_.find(fwd_key) == rr.intermediate_results_.end()) {
      SmartPointer<MarketModel> bumped = model;
      bumped->bumpAssetPrize(h_);
      fwd = prizer->prize(bumped, option);
      rr.intermediate_results_[fwd_key] = fwd;
    } else {
      fwd = rr.intermediate_results_[fwd_key];
    }

    rr.PV_and_Greeks_[risk_name_] = (fwd - pv) / (h_);
  }

  /** \brief Calculates delta using backward differencing scheme
   *
   * Method checks if the PV for a given market shifts were calculated. If yes, it uses them in estimating the Delta. 
   * If they were not calculated, it performs calculations, saves them and then calculates Delta. 
   */
  void OptionDelta::BwdDelta(GreeksIntermediateResults& rr,
			     const SmartPointer<MarketModel>& model,
			     const SmartPointer<PricingEngine>& prizer,
			     const SmartPointer<Option>& option) {
    auto pv_key =  std::make_tuple(0.0, 0.0);
    auto pv = rr.intermediate_results_[pv_key];

    auto bwd_key = std::make_tuple(-h_, 0.0);
    double bwd;

    if (rr.intermediate_results_.find(bwd_key) == rr.intermediate_results_.end()) {
      SmartPointer<MarketModel> bumped = model;
      bumped->bumpAssetPrize(-h_);
      bwd = prizer->prize(bumped, option);
      rr.intermediate_results_[bwd_key] = bwd;
    } else {
      bwd = rr.intermediate_results_[bwd_key];
    }

    rr.PV_and_Greeks_[risk_name_] = (pv - bwd) / (h_);
  }
  
  /** \brief Virtual copy constructor
   */
  OptionDelta* OptionDelta::clone() const {
    return new OptionDelta(*this);
  }
}  // namespace julian
