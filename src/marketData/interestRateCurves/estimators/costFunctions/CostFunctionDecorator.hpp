#ifndef JULIAN_COSTFUNCTIONDECORATOR_HPP
#define JULIAN_COSTFUNCTIONDECORATOR_HPP

#include <marketData/interestRateCurves/estimators/costFunctions/SmootherCostFunction.hpp>
#include <marketData/interestRateCurves/interpolatedCurve.hpp>
#include <utils/smartPointer.hpp>
#include <armadillo>

namespace julian {
namespace ir {
     /**
   * @file   CostFunctionDecorator.hpp
   * @brief  File contains implementation of abstract component of  SmootherCostFunction decorator
   */
  /** \ingroup irCurveCost
   * \brief Interface for classes decorating SmootherCostFunction.
   *  
   * CostFunctionDecorator is a interface for all classes decorating the SmootherCostFunction. 
   * CostFunctionSmoother's derived classes are used to define the cost function of optimization problems used in ir::InterpolatedCurve construction.
   *
   * Class also contains methods to calculate the \b D matrix and \b X matrix that implements differential operator.
   */
  
  class CostFunctionDecorator: public SmootherCostFunction {
  public:
  /** \brief Constructor
  */
    explicit CostFunctionDecorator(SmartPointer<SmootherCostFunction> c): cost_function_(c) {}; 

    virtual arma::mat giveQmatrix(const InterpolatedCurve&) const;
    virtual arma::mat giveCvector(const InterpolatedCurve&) const;
    virtual double calculateCost(const InterpolatedCurve&) const;

    virtual std::vector<double> giveSmoothedCurve(const InterpolatedCurve&) const;
    virtual void updateSmoothedCurve(InterpolatedCurve&,const std::vector<double>&) const;
    virtual CostFunctionDecorator* clone() const;

    /** \brief destructor
     */
    virtual ~CostFunctionDecorator(){};
      
  protected:
    arma::mat matrixD(int size, int order) const;
    arma::mat matrixX(const InterpolatedCurve& c, int order) const; 
         
      
  private:
    SmartPointer<SmootherCostFunction> cost_function_;  /*!< \brief Pointer to decorator interface.*/
  };
}  // namespace ir
}  // namespace julian
#endif
