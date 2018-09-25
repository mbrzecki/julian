#ifndef JULIAN_MARKETMODEL_HPP
#define JULIAN_MARKETMODEL_HPP

#include <marketData/interestRateCurves/irCurve.hpp>
#include <mathematics/stochasticProcesses/stochasticProcess.hpp>
#include <marketData/ForwardCurve.hpp>
#include <map>

namespace julian {
  class EuropeanOpt;

    /**
   * @file   marketModel.hpp
   * @brief  File contains implementation of interface for market models. 
   */
  
  /** \ingroup marketmodels
   *  \brief Interface for objects representing market models
   *
   * Market model is an object holding information about market state (interest rates, yields, volatility, asset prize) 
   * and its dynamics (usually represented by stochastic process).
   *
   */

  class MarketModel {
  public:
    MarketModel(){};

    /** \brief returns the date on which market data are actual
     */
    virtual Date getDate() const = 0;
    
    /** \brief returns the prize of asset
     */
    virtual double getAssetPrize() const = 0;
    
    /** \brief returns discounting curve
     */
    virtual SmartPointer<ir::Curve> getDiscountingCurve() const = 0;
    
    /** \brief returns dividend curve
     */
    virtual SmartPointer<ir::Curve> getDividendCurve() const = 0;

    /** \brief sets the market date
     *
     * \param date New market date
     */
    virtual void setDate(Date& date) = 0;
    
    /** \brief sets asset prize
     *
     *  \param prize new asset prize
     */
    virtual void setAssetPrize(double prize) = 0;

    /** \brief bump asset prize additively 
     *
     * \param h bump size
     */
    virtual void bumpAssetPrize(double h) = 0;

    /** \brief bump volatility additively 
     *
     *  \param h bump size
     *  \note Depending on the market model bumping volatility may have different mechanism
     */
    virtual void bumpVolatility(double h) = 0;

    /** \brief prize EuropeanOpt analytically 
     */
    virtual double prizeAnalytically(const EuropeanOpt& opt) const = 0;
       
	
    /** \brief virtual copy constructor
     */
    virtual MarketModel* clone() const = 0;

    /** \brief destructor
     */
    virtual ~MarketModel() {
    }
  };

  /** \ingroup marketmodels
   * \brief Class uses Curiously Recurring Template Pattern to implement polymorphic copy construction in every derived class implementing MarketModel.
   *
   * For more details see \ref cpp_dp_deepcopy
   */
  template<typename T>
  class DeeplyCopyableMarketModel : public MarketModel {
  public:
    /** \brief virtual copy constructor
     */
    virtual MarketModel* clone() const {
      return new T(static_cast<const T&>(*this));
    }
  };
}  // namespace julian


#endif /* MARKETMODEL_HPP */
