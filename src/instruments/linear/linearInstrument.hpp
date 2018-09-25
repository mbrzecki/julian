#ifndef JULIAN_LINEARINSTRUMENTS_HPP
#define JULIAN_LINEARINSTRUMENTS_HPP

#include <marketData/interestRateCurves/irCurve.hpp>
#include <instruments/CashFlowVector.hpp>
#include <instruments/FixedCashFlow.hpp>
#include <instruments/FloatingCashFlow.hpp>

namespace julian {

  /**
   * @file   linearInstrument.hpp
   * @brief  File contains definition of linear instruments interface.
   */

  /** \ingroup linearInstruments
   *  \brief Class is an abstract class expressing the concept of linear instruments like deposits, FRAs, futures, fxForwards and swaps 
   *  
   */

  class LinearInstrument {
  public:
    /** \brief constructor
     */
    LinearInstrument(){};
    /** \brief calculate price of linear instrument using one curve for discounting and projecting forward rates
     */
    virtual double price(const SmartPointer<ir::Curve>&) = 0;

    /** \brief calculate price of linear instrument using different curve for discounting and projecting forward rates
     */
    virtual double price(const SmartPointer<ir::Curve>& discounting1,const SmartPointer<ir::Curve>& discounting2,const SmartPointer<ir::Curve>& projecting1,const SmartPointer<ir::Curve>& projecting2) = 0;

    /** \brief prints price and CFs of linear instrument using one curve for discounting and projecting forward rates
     */
    virtual void valuation(const SmartPointer<ir::Curve>& c) = 0;

    /** \brief prints price and CFs of linear instrument using different curve for discounting and projecting forward rates
     */
    virtual void valuation(const SmartPointer<ir::Curve>& discounting1,const SmartPointer<ir::Curve>& discounting2,const SmartPointer<ir::Curve>& projecting1,const SmartPointer<ir::Curve>& projecting2) = 0;

    /** \brief virtual copy constructor
     */
    virtual LinearInstrument* clone() const = 0;
    
    /** \brief destructor
     */
    virtual ~LinearInstrument(){};
  private:
  };
}
#endif
