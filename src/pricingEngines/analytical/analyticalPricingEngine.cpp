#include <pricingEngines/analytical/analyticalPricingEngine.hpp>

namespace julian {

  double AnalyticalPricingEngine::prize(const SmartPointer<MarketModel>& model,
					const SmartPointer<Option>& option) const {
    return option->prizeAnalytically(model);
  }
}  // namespace julian
