#ifndef JULIAN_ANALITYCALPRICINGENGINE_HPP
#define JULIAN_ANALITYCALPRICINGENGINE_HPP

#include <utils/smartPointer.hpp>
#include <pricingEngines/pricingEngine.hpp>

namespace julian {
  /**
   * @file   analyticalPricingEngine.hpp
   * @brief  File contains analytical pricing engine.
   */
  /** \ingroup analytical_engines
   *  \brief analytical pricer
   *
   * Class is just a interface for prizing options with analytical formulas. 
   * To effectively implement the analytical prizing the Visitor pattern was used. 
   * Visitor pattern is used to emulate double dispatch.Double dispatch is a mechanism that dispatches 
   * a function call to different concrete functions depending on the runtime types of two objects involved in the call (in this case Model and Option)
   *
   * Class AnalyticalPricingEngine provides an interface to proceeds the double dispatch mechanism.   
   *
   * For visitor pattern see \ref cpp_dp_visitor 
   */

  class AnalyticalPricingEngine : public DeeplyCopyablePricingEngine<AnalyticalPricingEngine> {
  public:
    /** \brief constructor
     */
    AnalyticalPricingEngine(){};

    /** \brief prized the option using double dispatch mechanism
     */
    double prize(const SmartPointer<MarketModel>&, const SmartPointer<Option>&) const;

    /** \brief destructor
     */
    virtual ~AnalyticalPricingEngine(){};
  };
  
}


#endif 
