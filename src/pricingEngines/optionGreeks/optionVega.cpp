#include <pricingEngines/optionGreeks/optionVega.hpp>


namespace julian {
  /** \brief calculates the option's Vega
   *  
   * Vega of option is calculated using the finite difference scheme
   * * \f$Vega = \frac{\partial PV}{\partial Vol} \approx \frac{PV(Vol+h) - PV(Vol)}{h}\f$ when forward differencing is used 
   * * \f$Vega = \frac{\partial PV}{\partial Vol} \approx \frac{PV(Vol) - PV(Vol-h)}{h}\f$ when backward differencing is used 
   * * \f$Vega = \frac{\partial PV}{\partial Vol} \approx \frac{PV(Vol+h) - PV(Vol-h)}{2h}\f$ when central differencing is used 
   *
   * \return method returns map with key "Vega" and value of Vega
   */
  GreeksIntermediateResults OptionVega::calculateRisks(const SmartPointer<MarketModel>& model,
						       const SmartPointer<PricingEngine>& prizer,
						       const SmartPointer<Option>& option)  {
    auto ret = OptionGreeksDecorator::calculateRisks(model, prizer, option);
    switch (scheme_) {
    case NumDiffScheme::CNTR: {
      CntrVega(ret, model, prizer, option);
    }
      break;
    case NumDiffScheme::FWD: {
      FwdVega(ret, model, prizer, option);
    }
      break;
    case NumDiffScheme::BWD: {
      BwdVega(ret, model, prizer, option);
    }
      break;
    }
    return ret;
  }

  /** \brief Calculates Vega using central differencing scheme
   *
   * Method checks if the PV for a given market shifts were calculated. If yes, it uses them in estimating the Vega. 
   * If they were not calculated, it performs calculations, saves them and then calculates Vega. 
   */
  void OptionVega::CntrVega(GreeksIntermediateResults& rr,
			    const SmartPointer<MarketModel>& model,
			    const SmartPointer<PricingEngine>& prizer,
			    const SmartPointer<Option>& option) {
    double fwd, bwd;
    auto fwd_key = std::make_tuple(0.0, h_);
    auto bwd_key = std::make_tuple(0.0,-h_);
    if (rr.intermediate_results_.find(fwd_key) == rr.intermediate_results_.end()) {
      SmartPointer<MarketModel> bumped = model;
      bumped->bumpVolatility(h_);
      fwd = prizer->prize(bumped, option);
      rr.intermediate_results_[fwd_key] = fwd;
    } else {
      fwd = rr.intermediate_results_[fwd_key];
    }
    if ( rr.intermediate_results_.find(bwd_key) == rr.intermediate_results_.end() ) {
      SmartPointer<MarketModel> bumped = model;
      bumped->bumpVolatility(-h_);
      bwd = prizer->prize(bumped, option);
      rr.intermediate_results_[bwd_key] = bwd;
    } else {
      bwd = rr.intermediate_results_[bwd_key];
    }
    rr.PV_and_Greeks_[risk_name_] = (fwd - bwd) / (2.0 * h_);
  }

  /** \brief Calculates Vega using forward differencing scheme
   *
   * Method checks if the PV for a given market shifts were calculated. If yes, it uses them in estimating the Vega. 
   * If they were not calculated, it performs calculations, saves them and then calculates Vega. 
   */
  void OptionVega::FwdVega(GreeksIntermediateResults& rr,
			   const SmartPointer<MarketModel>& model,
			   const SmartPointer<PricingEngine>& prizer,
			   const SmartPointer<Option>& option)  {
    auto pv_key =  std::make_tuple(0.0, 0.0);
    auto pv = rr.intermediate_results_[pv_key];

    auto fwd_key = std::make_tuple(0.0, h_);
    double fwd;

    if (rr.intermediate_results_.find(fwd_key) == rr.intermediate_results_.end()) {
      SmartPointer<MarketModel> bumped = model;
      bumped->bumpVolatility(h_);
      fwd = prizer->prize(bumped, option);
      rr.intermediate_results_[fwd_key] = fwd;
    } else {
      fwd = rr.intermediate_results_[fwd_key];
    }

    rr.PV_and_Greeks_[risk_name_] = (fwd - pv) / (h_);
  }

  /** \brief Calculates Vega using backward differencing scheme
   *
   * Method checks if the PV for a given market shifts were calculated. If yes, it uses them in estimating the Vega. 
   * If they were not calculated, it performs calculations, saves them and then calculates Vega. 
   */
  void OptionVega::BwdVega(GreeksIntermediateResults& rr,
			   const SmartPointer<MarketModel>& model,
			   const SmartPointer<PricingEngine>& prizer,
			   const SmartPointer<Option>& option) {
    auto pv_key =  std::make_tuple(0.0, 0.0);
    auto pv = rr.intermediate_results_[pv_key];

    auto bwd_key = std::make_tuple(0.0, -h_);
    double bwd;

    if (rr.intermediate_results_.find(bwd_key) == rr.intermediate_results_.end()) {
      SmartPointer<MarketModel> bumped = model;
      bumped->bumpVolatility(-h_);
      bwd = prizer->prize(bumped, option);
      rr.intermediate_results_[bwd_key] = bwd;
    } else {
      bwd = rr.intermediate_results_[bwd_key];
    }

    rr.PV_and_Greeks_[risk_name_] = (pv - bwd) / (h_);
  }
  /** \brief returns the PV and Greek parameter
   *  
   * \return method returns map with name of Greeks as key and the value of Greeks as value
   */
  std::map<std::string,double> OptionVega::getRisks(const SmartPointer<MarketModel>& model,
						    const SmartPointer<PricingEngine>& prizer,
						    const SmartPointer<Option>& option) {
    auto ret = calculateRisks(model, prizer, option);
    return ret.PV_and_Greeks_;
  } 
  /** \brief virtual copy constructor
   */
  OptionVega* OptionVega::clone() const {
    return new OptionVega(*this);
  }
}  // namespace julian
