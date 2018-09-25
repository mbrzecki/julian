#ifndef JULIAN_OPTIONGREEKSDECORATOR_HPP
#define JULIAN_OPTIONGREEKSDECORATOR_HPP

#include <pricingEngines/optionGreeks/optionGreeks.hpp>

namespace julian {
  /**
   * @file   optionGreeksDecorator.hpp
   * @brief  Interface of option Greeks decorating classes.
   */
  /** \ingroup optiongreeks
   * \brief Interface for classes decorating Option Greeks.
   */ 
  
  class OptionGreeksDecorator: public OptionGreeks {
  public:
    /** \brief Constructor
     */
    OptionGreeksDecorator(SmartPointer<OptionGreeks> risks): risks_(risks) {}
    
    virtual GreeksIntermediateResults calculateRisks(const SmartPointer<MarketModel>& model,
							const SmartPointer<PricingEngine>& prizer,
							const SmartPointer<Option>& option) {
      return risks_->calculateRisks(model, prizer, option);
    }

    virtual std::map<std::string,double> getRisks(const SmartPointer<MarketModel>& model,
						  const SmartPointer<PricingEngine>& prizer,
						  const SmartPointer<Option>& option) {
      auto ret = risks_->calculateRisks(model, prizer, option);
      return ret.PV_and_Greeks_;
    }
    
    OptionGreeksDecorator* clone() const {
      return new OptionGreeksDecorator(*this);
    }
    
    virtual ~OptionGreeksDecorator(){};
  private:
    SmartPointer<OptionGreeks> risks_; /*!< \brief Pointer to decorator interface.*/
  };
}

#endif /* JULIAN_OPTIONGREEKSDECORATOR_HPP */
