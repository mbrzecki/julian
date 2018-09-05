#ifndef JULIAN_OPTIONVANNA_HPP
#define JULIAN_OPTIONVANNA_HPP

#include <pricingEngines/optionGreeks/optionGreeksDecorator.hpp>
#include <mathematics/mathUtils.hpp>

namespace julian {
  /**
   * @file   OptionVanna.hpp
   * @brief  File contains implementation of OptionVanna.
   */
  /** \ingroup optiongreeks
   *  \brief Calculates option's Vanna.
   *
   * This method calculates Vanna. Using the method _prize_ of julian::PricingEngine and _bumpVolatility/bumpSpot_ of julian::MarketModel it calculates the cross-derivative of option prize wrt to spot and volatility.
   *
   * Vanna of option is calculated using the finite difference scheme
   * \f[Vanna = \frac{\partial^2PV}{\partial Spot \partial Vol} \approx \frac{PV(Spot+h_s,Vol+h_v) - PV(Spot+h_s,Vol-h_v) - PV(Spot-hs,Vol+h_v) + PV(Spot-hs,Vol-hv)}{4h_sh_v}\f]
   *
   * The result is saved in map.
   * OptionVanna is a concrete decorator in decorator structure. Concrete Decorator is a class that altered alters the behaviour of Concrete Component.
   *
   * \todo Implement different schemes for numerical differentiation. At this moment only central differencing is implemented.
   */
  class OptionVanna: public OptionGreeksDecorator {
  public:
    /** \brief Constructor
     */
    OptionVanna(SmartPointer<OptionGreeks> input, double hs, double hv, std::string risk_name = "Vanna"):
      OptionGreeksDecorator(input), hs_(hs), hv_(hv), risk_name_(risk_name) {}
    std::map<std::string,double> getRisks(const SmartPointer<MarketModel>& model,
					  const SmartPointer<PricingEngine>& prizer,
					  const SmartPointer<Option>& option);
    GreeksIntermediateResults calculateRisks(const SmartPointer<MarketModel>& model,
					     const SmartPointer<PricingEngine>& prizer,
					     const SmartPointer<Option>& option);
    OptionVanna* clone() const;
  
    ~OptionVanna(){};
  private:
    double hs_ ; /*!< \brief Increment used in differencing scheme for spot direction.*/
    double hv_ ; /*!< \brief Increment used in differencing scheme for volatility direction.*/
    std::string risk_name_; /*!< \brief Risk name that will be used as key for result map. Default name is Vanna*/
  };
}  // namespace julian

#endif
