#ifndef JULIAN_CURVEBUILDINGBLOCK_HPP
#define JULIAN_CURVEBUILDINGBLOCK_HPP

#include <string>
#include <instruments/CashFlowVector.hpp>
#include <marketData/interestRateCurves/irCurve.hpp>
#include <marketData/interestRateCurves/InterpolatedCurve.hpp>
#include <utility>  
 
namespace julian {
namespace ir {

  /**
   * @file   curveBuildingBlock.hpp
   * @brief  File containing definition of interest rates curve building block.
   */
  
  /** \ingroup irCurve
   * \brief Building Block is a class that defines the interface for benchmark instruments used for estimating interest rate curve.
   *
   * Building Blocks defines the interface used by interest rate curve estimators. 
   * * Method calibrate is used by Newton Raphson Estimator. The estimator calibrates curve by finding the root of this method. 
   * * Method parRate, giveQuoting and changeQuoting are used by smoothing optimization algorithms that find the curve which minimizes the difference between market rate and quoting implied from the curve.
   * * Method getCFs are used by standard boots-trappers which are based on defining linear system of equation [CFij] [DFi] = [PRIZEj]
   */
  
    class BuildingBlock {
    public:
      BuildingBlock(){};

      /**
       * \brief returns maturity. 
       */
      virtual Date getDate() const = 0;

      /**
       * \brief Method calibrate is used by root finding estimator. 
       *
       * The estimator calibrates curve by finding the root of this method. 
       *
       */
      virtual double calibrate(const SmartPointer<ir::Curve>& calibrated) = 0;

      /**
       * \brief Method calibrate is used by root finding estimator. 
       *
       * The estimator calibrates curve by finding the root of this method. This method is used when multi-curve environment is used.
       *
       */
      virtual double calibrate(const SmartPointer<Curve>& discounting,const SmartPointer<Curve>& projection , const SmartPointer<Curve>& calibrated) = 0;
      
      /**
       * \brief Implies quoting of benchmark instrument from interest rate curves provided. 
       *
       */
      virtual double getParRate(const SmartPointer<Curve>& discounting,const SmartPointer<Curve>& projection,const SmartPointer<Curve>& projection2) = 0;

      /**
       * \brief Returns quoting of the instrument
       *
       */
      virtual double getQuoting() = 0;

      /**
       * \brief changes quoting of the instrument
       *
       */
      virtual void changeQuoting(double) = 0;

      /**
       * \brief Returns the sets of cashflows associated with the benchmark instruments
       * 
       *
       */
      virtual std::pair<CashFlowVector, CashFlowVector> getCFs() const = 0;

      
      /**
       * \brief Returns interest rates convention of the benchmark instruments
       */
      virtual InterestRate getInterestRate() const = 0;

      /**
       * \brief Returns a name of instrument
       */
      virtual std::string info() const = 0;
      
      /**
       * \brief Virtual copy constructor
       */
      virtual BuildingBlock* clone() const = 0;

      /**
       * \brief destructor
       */
      virtual ~BuildingBlock(){};
    };
}  // namespace ir
}  // namespace julian
#endif
