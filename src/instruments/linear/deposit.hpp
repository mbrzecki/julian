#ifndef JULIAN_DEPOSIT_HPP
#define JULIAN_DEPOSIT_HPP

#include <instruments/linear/linearInstrument.hpp>
#include <marketData/interestRateCurves/curveBuildingBlock.hpp>
#include <interestRates/interestRate.hpp>
#include <instruments/instrumentAuxiliaryTypes.hpp>

namespace julian {

  /**
   * @file   deposit.hpp
   * @brief  File contains definition of deposit.
   */
  
  /** \ingroup linearInstruments
   *  \brief Class implements a deposit contract.
   *
   * Class models the interbank deposit - one bank holding funds of another bank and paying interest rate.
   */

  class Deposit: public LinearInstrument, public ir::BuildingBlock {
  public:
    Deposit(Date trade_date,Date start_date,Date end_date,InterestRate rate ,double notional,double quoting);
  
    /*! \name Linear instrument interface
     */
    //@{

    double price(const SmartPointer<ir::Curve>&);
    double price(const SmartPointer<ir::Curve>& discounting1,const SmartPointer<ir::Curve>& ,const SmartPointer<ir::Curve>& ,const SmartPointer<ir::Curve>& );
    void valuation(const SmartPointer<ir::Curve>&);
    void valuation(const SmartPointer<ir::Curve>& discounting1,const SmartPointer<ir::Curve>& discounting2,const SmartPointer<ir::Curve>& projecting1,const SmartPointer<ir::Curve>& projecting2);
    //@}
    
    /*! \name Building Block interface
     */
    //@{
    Date getDate() const override;
    std::pair<CashFlowVector, CashFlowVector> getCFs() const override;
    InterestRate getInterestRate() const override;
    double calibrate(const SmartPointer<ir::Curve>& calibrated) override;
    double calibrate(const SmartPointer<ir::Curve>& discounting, const SmartPointer<ir::Curve>& projection, const SmartPointer<ir::Curve>& calibrated) override;
    double getParRate(const SmartPointer<ir::Curve>& discounting,const SmartPointer<ir::Curve>& projection, const SmartPointer<ir::Curve>& projection2) override;
    double getQuoting() override;
    void changeQuoting(double) override;
    std::string info() const override;
    //@}
    
    ~Deposit(){};
    Deposit* clone() const;
    
    friend std::ostream& operator<<(std::ostream&, Deposit&);
  
  private:
    Date trade_date_;  /*!< @brief The date on which deposit is dealt.*/
    InterestRate rate_; /*!< @brief Convention of interest rates*/
    double quoting_; /*!< @brief Deposit interest rate.*/
    CashFlowVector cfs_; /*!< @brief Deposit cashflows .*/
  };
}
#endif
