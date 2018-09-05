#ifndef JULIAN_PRICINGENGINE_HPP
#define JULIAN_PRICINGENGINE_HPP

#include <utils/smartPointer.hpp>
#include <marketModels/marketModel.hpp>
#include <instruments/options/option.hpp>

namespace julian {
  
	/**
	* @file   pricingEngine.hpp
	* @brief  File contains definition of PricingEngine interface.
	*/
  
  /** \ingroup pricing_engines
   *  \brief Interface for all pricing engines
   *
   */

  class PricingEngine {
  public:
    /** \brief prizes option using market model
     */
    virtual double prize(const SmartPointer<MarketModel>&,const SmartPointer<Option>&) const = 0;

    /** \brief virtual copy constructor
     */
    virtual PricingEngine* clone() const = 0;
    
    /** \brief destructor
     */
    virtual ~PricingEngine(){};
  };


  /** \ingroup pricing_engines
   * \brief Class uses Curiously Recurring Template Pattern to implement polymorphic copy construction in every derived class implementing PricingEngine.
   *
   * For more details see \ref cpp_dp_deep_copy
   */
  template<typename T>
  class DeeplyCopyablePricingEngine : public PricingEngine {
  public:
    /** \brief virtual copy constructor
     */
    virtual PricingEngine* clone() const {
      return new T(static_cast<const T&>(*this));
    }
  };
}  // namespace julian
#endif
