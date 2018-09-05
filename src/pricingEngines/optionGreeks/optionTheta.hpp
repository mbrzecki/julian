#ifndef JULIAN_OPTIONTHETA_HPP
#define JULIAN_OPTIONTHETA_HPP

#include <pricingEngines/optionGreeks/optionGreeksDecorator.hpp>
#include <mathematics/mathUtils.hpp>

namespace julian {
  /**
   * @file   optionTheta.hpp
   * @brief  File contains implementation of OptionTheta.
   */
  /** \ingroup optiongreeks
   *  \brief Calculates option's theta.
   *
   * This method calculates Theta. Method moves the market to next day and calculates the difference in \f$Theta = PV(T+1) - PV(T)\f$
   * Theta does not change the market data, the change of the value is connected only with change in time value of the option.  
   * The result is saved in map.
   * OptionTheta is a concrete decorator in decorator structure. Concrete Decorator is a class that altered alters the behaviour of Concrete Component.
   */
  class OptionTheta: public OptionGreeksDecorator {
  public:
    /** \brief Constructor
     */
    OptionTheta(SmartPointer<OptionGreeks> input, const std::string& risk_name = "Theta"):
      OptionGreeksDecorator(input), risk_name_(risk_name) {}
    GreeksIntermediateResults calculateRisks(const SmartPointer<MarketModel>& model,
					     const SmartPointer<PricingEngine>& prizer,
					     const SmartPointer<Option>& option);

    std::map<std::string,double> getRisks(const SmartPointer<MarketModel>& model,
					  const SmartPointer<PricingEngine>& prizer,
					  const SmartPointer<Option>& option);
    OptionTheta* clone() const;
  
    ~OptionTheta(){};
  private:
    std::string risk_name_; /*!< \brief Risk name that will be used as key for result map. Default name is Theta*/
    
  };
}  // namespace julian

#endif
