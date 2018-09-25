#ifndef JULIAN_OPTIONGREEKS_HPP
#define JULIAN_OPTIONGREEKS_HPP

#include <map>
#include <marketModels/marketModel.hpp>
#include <pricingEngines/pricingEngine.hpp>
#include <instruments/options/option.hpp>

namespace julian {
  /**
   * @file   optionGreeks.hpp
   * @brief  Interface of option's Greeks structure.
   */
  /** \ingroup optiongreeks
   * \brief Data structure holding the PV and Greeks
   *
   * The structure contains two std::maps: 
   * * one with name of Greeks as key and the value of Greeks as value;
   * * one with PVs calculated with different spot and vol shifts. To calculate Greeks using finite difference method we need to calculate PVs after shifting Spot or Vol values. 
   * Some Greeks,like Delta and Gamma, may be using the same shifted values. To avoid multiple calculations of the same values, the intermediates results are saved for later use. 
   * The intermediate results are saved in std::map, with key represented by tuple containing two doubles: spot shift and volatility shift, and value of PV calculated using these shifts.    
   */
  struct GreeksIntermediateResults {
    std::map<std::tuple<double,double>, double> intermediate_results_; /*!< \brief std::map with PVs calculated with different spot and vol shifts*/
    std::map<std::string,double> PV_and_Greeks_; /*!< \brief std::map with name of Greeks as key and the value of Greeks as value;*/
  };
  
  /** \ingroup optiongreeks
   * \brief Interface for OptionGreeks decorator.
   */
  
  class OptionGreeks {
  public:

    /** \brief returns the PV and Greek parameter
     *  
     * \return method returns map with name of Greeks as key and the value of Greeks as value
     */
    virtual std::map<std::string,double> getRisks(const SmartPointer<MarketModel>&, const SmartPointer<PricingEngine>&, const SmartPointer<Option>&) = 0;
    
    /** \brief calculates the PV or Greek parameter
     *  
     * \return method returns the OptionResults
     */
    virtual GreeksIntermediateResults calculateRisks(const SmartPointer<MarketModel>&,
						     const SmartPointer<PricingEngine>&,
						     const SmartPointer<Option>&) = 0;
	
    /** \brief Virtual copy constructor
     */
    virtual OptionGreeks* clone() const;
	
    /** \brief Destructor
     */
    virtual ~OptionGreeks(){};
  };


}

#endif 
