#include <pricingEngines/optionGreeks/optionGamma.hpp>

namespace julian {

  /** \brief Calculates the option's gamma
   *
   * Delta of option is calculated using the finite difference scheme
   * * \f$\Gamma = \frac{\partial^2 PV}{\partial Spot^2} \approx \frac{PV(Spot+2h) - 2PV(Spot+h) + PV(Spot)}{h^2}\f$ when forward scheme is used,
   * * \f$\Gamma = \frac{\partial^2 PV}{\partial Spot^2} \approx \frac{PV(Spot) - 2PV(Spot-h) + PV(Spot-2h)}{h^2}\f$ when backward scheme is used,
   * * \f$\Gamma = \frac{\partial^2 PV}{\partial Spot^2} \approx \frac{PV(Spot+h) - 2PV(Spot) + PV(Spot-h)}{h^2}\f$ when central scheme is used.
   *
   */
  GreeksIntermediateResults OptionGamma::calculateRisks(const SmartPointer<MarketModel>& model,
							const SmartPointer<PricingEngine>& prizer,
							const SmartPointer<Option>& option)  {
    auto ret = OptionGreeksDecorator::calculateRisks(model, prizer, option);
    switch (scheme_) {
    case NumDiffScheme::CNTR: {
      CntrGamma(ret, model, prizer, option);
    } break;
    case NumDiffScheme::FWD: {
      FwdGamma(ret, model, prizer, option);
    } break;
    case NumDiffScheme::BWD: {
      BwdGamma(ret, model, prizer, option);
    } break;
    }
    return ret;
  }
  
  /** \brief Returns the PV and Greek parameter
   *  
   * \return method returns map with name of Greeks as key and the value of Greeks as value
   */
  std::map<std::string,double> OptionGamma::getRisks(const SmartPointer<MarketModel>& model,
						     const SmartPointer<PricingEngine>& prizer,
						     const SmartPointer<Option>& option) {
    auto ret = calculateRisks(model, prizer, option);
    return ret.PV_and_Greeks_;
  }

  
  /** \brief Calculates gamma using central differencing scheme
   *
   * Method checks if the PV for a given market shifts were calculated. If yes, it uses them in estimating the Gamma. 
   * If they were not calculated, it performs calculations, saves them and then calculates Gamma. 
   */
  void OptionGamma::CntrGamma(GreeksIntermediateResults& rr,
			      const SmartPointer<MarketModel>& model,
			      const SmartPointer<PricingEngine>& prizer,
			      const SmartPointer<Option>& option) {
    double fwd, bwd, pv;
    auto pv_key =  std::make_tuple(0.0, 0.0);
    auto fwd_key = std::make_tuple(h_, 0.0);
    auto bwd_key = std::make_tuple(-h_, 0.0);

    pv = rr.intermediate_results_[pv_key];

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
    rr.PV_and_Greeks_[risk_name_] = (fwd - 2.0*pv +  bwd) / (h_*h_);
  }

  /** \brief Calculates gamma using forward differencing scheme
   *
   * Method checks if the PV for a given market shifts were calculated. If yes, it uses them in estimating the Gamma. 
   * If they were not calculated, it performs calculations, saves them and then calculates Gamma. 
   */
  void OptionGamma::FwdGamma(GreeksIntermediateResults& rr,
			     const SmartPointer<MarketModel>& model,
			     const SmartPointer<PricingEngine>& prizer,
			     const SmartPointer<Option>& option)  {
    auto pv_key =  std::make_tuple(0.0, 0.0);
    auto pv = rr.intermediate_results_[pv_key];

    auto fwd_key = std::make_tuple(h_, 0.0);
    auto fwdfwd_key = std::make_tuple(2.0*h_, 0.0);
    double fwd, fwdfwd;

    if (rr.intermediate_results_.find(fwd_key) == rr.intermediate_results_.end()) {
      SmartPointer<MarketModel> bumped = model;
      bumped->bumpAssetPrize(h_);
      fwd = prizer->prize(bumped, option);
      rr.intermediate_results_[fwd_key] = fwd;
    } else {
      fwd = rr.intermediate_results_[fwd_key];
    }
    
    if (rr.intermediate_results_.find(fwdfwd_key) == rr.intermediate_results_.end()) {
      SmartPointer<MarketModel> bumped = model;
      bumped->bumpAssetPrize(2.0*h_);
      fwdfwd = prizer->prize(bumped, option);
      rr.intermediate_results_[fwdfwd_key] = fwdfwd;
    } else {
      fwdfwd = rr.intermediate_results_[fwdfwd_key];
    }
    rr.PV_and_Greeks_[risk_name_] = (fwdfwd - 2.0*fwd +  pv) / (h_*h_);
  }

  /** \brief Calculates gamma using backward differencing scheme
   *
   * Method checks if the PV for a given market shifts were calculated. If yes, it uses them in estimating the Gamma. 
   * If they were not calculated, it performs calculations, saves them and then calculates Gamma. 
   */
  void OptionGamma::BwdGamma(GreeksIntermediateResults& rr,
			     const SmartPointer<MarketModel>& model,
			     const SmartPointer<PricingEngine>& prizer,
			     const SmartPointer<Option>& option) {
    auto pv_key =  std::make_tuple(0.0, 0.0);
    auto pv = rr.intermediate_results_[pv_key];

    auto bwd_key = std::make_tuple(-h_, 0.0);
    auto bwdbwd_key = std::make_tuple(-2.0*h_, 0.0);
    double bwd;
    double bwdbwd;

    if (rr.intermediate_results_.find(bwd_key) == rr.intermediate_results_.end()) {
      SmartPointer<MarketModel> bumped = model;
      bumped->bumpAssetPrize(-h_);
      bwd = prizer->prize(bumped, option);
      rr.intermediate_results_[bwd_key] = bwd;
    } else {
      bwd = rr.intermediate_results_[bwd_key];
    }
    
    if (rr.intermediate_results_.find(bwdbwd_key) == rr.intermediate_results_.end()) {
      SmartPointer<MarketModel> bumped = model;
      bumped->bumpAssetPrize(-2.0*h_);
      bwdbwd = prizer->prize(bumped, option);
      rr.intermediate_results_[bwdbwd_key] = bwdbwd;
    } else {
      bwdbwd = rr.intermediate_results_[bwdbwd_key];
    }
    rr.PV_and_Greeks_[risk_name_] = (pv - 2*bwd + bwdbwd) / (h_*h_);
  }
  
  
  /** \brief virtual copy constructor
   */
  OptionGamma* OptionGamma::clone() const {
    return new OptionGamma(*this);
  }
}  // namespace julian
