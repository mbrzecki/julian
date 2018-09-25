#ifndef JULIAN_FRA_HPP
#define JULIAN_FRA_HPP

#include <instruments/linear/linearInstrument.hpp>
#include <interestRates/interestRate.hpp>
#include <utils/utils.hpp>
#include <marketData/interestRateCurves/curveBuildingBlock.hpp>
#include <instruments/instrumentAuxiliaryTypes.hpp>

namespace julian {

  /**
   * @file   FRA.hpp
   * @brief  File contains definition of FRA contract.
   */
  
  /** \ingroup linearInstruments
   *  \brief Class implements a Forward Rate Agreement.
   *
   * FRA is an OTC derivative instrument that trades as part of money markets. It is essentially a forward-starting loan,
   * but with no exchange of principal, so that only the difference in interest rate is traded.
   *
   * For more details see \cite derivativeInstruments and \cite OGguide.
   *
   */

  class FRA: public LinearInstrument, public ir::BuildingBlock {
  public:
    FRA(){};
    FRA(Date trade_date, Date fixing_date, Date value_date, Date maturity_date, InterestRate rate, double notional, double fixing, double quoting);
    
    /*! \name Linear instrument interface
     */
    //@{

    double price(const SmartPointer<ir::Curve>&) override;
    double price(const SmartPointer<ir::Curve>& discounting, const SmartPointer<ir::Curve>& projecting,
		 const SmartPointer<ir::Curve>& , const SmartPointer<ir::Curve>& ) override;
    void valuation(const SmartPointer<ir::Curve>&) override;
    void valuation(const SmartPointer<ir::Curve>& discounting1, const SmartPointer<ir::Curve>& discounting2,
		   const SmartPointer<ir::Curve>& projecting1, const SmartPointer<ir::Curve>& projecting2) override;
    //@}
    
    /*! \name Building Block interface
     */
    //@{
    Date getDate() const override;
    std::pair<CashFlowVector,CashFlowVector> getCFs() const override;
    double calibrate(const SmartPointer<ir::Curve>& calibrated) override;
    double calibrate(const SmartPointer<ir::Curve>& discounting, const SmartPointer<ir::Curve>& projection ,const SmartPointer<ir::Curve>& calibrated) override;
    double getParRate(const SmartPointer<ir::Curve>& discounting ,const SmartPointer<ir::Curve>& projection,const SmartPointer<ir::Curve>& projection2) override;
    double getQuoting() override;
    void changeQuoting(double) override;
    InterestRate getInterestRate() const override;
    std::string info() const override;
    //@}

    FRA* clone() const;
    ~FRA(){};
    
    friend std::ostream& operator<<(std::ostream&,FRA&);
    
  private:
    Date trade_date_; /*!< @brief The date on which FRA is dealt.*/
    Date fixing_date_; /*!< @brief The date on which reference rate is determined.*/
    Date value_date_; /*!< @brief The date on which the deposit of found becomes effective.*/
    Date maturity_date_; /*!< @brief The date on which the deposit expires.*/
    
    InterestRate rate_;  /*!< @brief Convention of interest rates*/
    double notional_; /*!< @brief The amount for which FRA is traded.*/
    double fixing_; /*!< @brief Determined fixing*/
    double quote_; /*!< @brief Interest rate at which FRA is traded.*/
    
    CashFlowVector floating_leg_; /*!< @brief Cash flow dependent on market index.*/
    CashFlowVector fixed_leg_; /*!< @brief Fixed cash flow.*/
  };
}
#endif
