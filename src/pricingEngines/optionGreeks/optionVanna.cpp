#include <pricingEngines/optionGreeks/OptionVanna.hpp>

namespace julian {

  /** \brief calculates the option's Vanna
   *  
   * Vanna of option is calculated using the finite difference scheme
   * \f$Vanna = \frac{PV(Spot+h_s,Vol+h_v) - PV(Spot+h_s,Vol-h_v) - PV(Spot-hs,Vol+h_v) + PV(Spot-hs,Vol-hv)}{4h_sh_v}\f$ 
   * \return method returns map with key "Vanna" and value of Vanna
   */
  GreeksIntermediateResults OptionVanna::calculateRisks(const SmartPointer<MarketModel>& model,
							const SmartPointer<PricingEngine>& prizer,
							const SmartPointer<Option>& option)  {
    auto rr = OptionGreeksDecorator::calculateRisks(model, prizer, option);
    double fwdS_fwdV, fwdS_bwdV, bwdS_fwdV, bwdS_bwdV;
    auto fwdS_fwdV_key = std::make_tuple( hs_, hv_);
    auto fwdS_bwdV_key = std::make_tuple( hs_,-hv_);
    auto bwdS_fwdV_key = std::make_tuple(-hs_, hv_);
    auto bwdS_bwdV_key = std::make_tuple(-hs_,-hv_);

    if (rr.intermediate_results_.find(fwdS_fwdV_key) == rr.intermediate_results_.end()) {
      SmartPointer<MarketModel> bumped = model;
      bumped->bumpAssetPrize(hs_);
      bumped->bumpVolatility(hv_);
      fwdS_fwdV = prizer->prize(bumped, option);
      rr.intermediate_results_[fwdS_fwdV_key] = fwdS_fwdV;
    } else {
      fwdS_fwdV = rr.intermediate_results_[fwdS_fwdV_key];
    }
    if (rr.intermediate_results_.find(bwdS_fwdV_key) == rr.intermediate_results_.end()) {
      SmartPointer<MarketModel> bumped = model;
      bumped->bumpAssetPrize(-hs_);
      bumped->bumpVolatility( hv_);
      bwdS_fwdV = prizer->prize(bumped, option);
      rr.intermediate_results_[bwdS_fwdV_key] = bwdS_fwdV;
    } else {
      bwdS_fwdV = rr.intermediate_results_[bwdS_fwdV_key];
    }    
    if (rr.intermediate_results_.find(fwdS_bwdV_key) == rr.intermediate_results_.end()) {
      SmartPointer<MarketModel> bumped = model;
      bumped->bumpAssetPrize( hs_);
      bumped->bumpVolatility(-hv_);
      fwdS_bwdV = prizer->prize(bumped, option);
      rr.intermediate_results_[fwdS_bwdV_key] = fwdS_bwdV;
    } else {
      fwdS_bwdV = rr.intermediate_results_[fwdS_bwdV_key];
    }
    if (rr.intermediate_results_.find(bwdS_bwdV_key) == rr.intermediate_results_.end()) {
      SmartPointer<MarketModel> bumped = model;
      bumped->bumpAssetPrize(-hs_);
      bumped->bumpVolatility(-hv_);
      bwdS_bwdV = prizer->prize(bumped, option);
      rr.intermediate_results_[bwdS_bwdV_key] = bwdS_bwdV;
    } else {
      bwdS_bwdV = rr.intermediate_results_[bwdS_bwdV_key];
    }

    rr.PV_and_Greeks_[risk_name_] = (fwdS_fwdV - bwdS_fwdV - fwdS_bwdV + bwdS_bwdV) / (4.0 * hs_ * hv_);

    return rr;
  }
  /** \brief returns the PV and Greek parameter
   *  
   * \return method returns map with name of Greeks as key and the value of Greeks as value
   */
  std::map<std::string,double> OptionVanna::getRisks(const SmartPointer<MarketModel>& model,
						     const SmartPointer<PricingEngine>& prizer,
						     const SmartPointer<Option>& option) {
    auto ret = calculateRisks(model, prizer, option);
    return ret.PV_and_Greeks_;
  }
  /** \brief Virtual copy constructor
   */
  OptionVanna* OptionVanna::clone() const {
    return new OptionVanna(*this);
  }
}  // namespace julian
