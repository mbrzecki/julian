#ifndef JULIAN_IRS_HPP
#define JULIAN_IRS_HPP

#include <instruments/linear/linearInstrument.hpp>
#include <interestRates/interestRate.hpp>
#include <dates/_all_dates.hpp>
#include <marketData/interestRateCurves/curveBuildingBlock.hpp>
#include <instruments/instrumentAuxiliaryTypes.hpp>

namespace julian {

  /**
   * @file   IRS.hpp
   * @brief  File contains definition of IRS contract.
   */
  
  /** \ingroup linearInstruments
   *  \brief Class implements an plain vanilla (flo/fix) interest rate swap contract.
   *  
   * IRS is an agreement between two counter-parties to make periodic interest payments to one another during the life of the swap, 
   * on a predetermined set of dates, based on a notional principal amount. One party is the fixed-rate payer (rate is agreed at the time of trade of the swap); 
   * other party is the floating-rate payer (rate is determined during the life of the swap)
   *
   * For more details see \cite derivativeInstruments and \cite OGguide.
   *
   */

  class IRS: public LinearInstrument, public ir::BuildingBlock {
  public:
    /** \brief Default constructor
     */
    IRS(){};
    /** \brief Constructor
     */
    IRS(Date trade_date,Date start_date, Date maturity_date,
	CashFlowVector fixed_leg, CashFlowVector floating_leg, InterestRate fixed_leg_rate, InterestRate floating_leg_rate,
	double notional,  double quoting,Frequency fixed_leg_freq, Frequency floating_leg_freq) {
      trade_date_ = trade_date;
      start_date_ = start_date;
      maturity_date_ = maturity_date;

      fixed_leg_ = fixed_leg;
      floating_leg_ = floating_leg;
      
      fixed_leg_rate_ = fixed_leg_rate;
      floating_leg_rate_ = floating_leg_rate;
      notional_ = notional; 
      quoting_ = quoting;
      //fixing_ = fixing;
      
      fixed_leg_freq_ = fixed_leg_freq;
      floating_leg_freq_ = floating_leg_freq;
    };
    
    
    
    /*! \name Linear instrument interface
     */
    //@{
    virtual double price(const SmartPointer<ir::Curve>&);
    virtual double price(const SmartPointer<ir::Curve>& discounting, const SmartPointer<ir::Curve>& projecting,const SmartPointer<ir::Curve>& ,const SmartPointer<ir::Curve>& );
    virtual void valuation(const SmartPointer<ir::Curve>&);
    virtual void valuation(const SmartPointer<ir::Curve>& discounting, const SmartPointer<ir::Curve>& projecting,const SmartPointer<ir::Curve>& ,const SmartPointer<ir::Curve>& );
    //@}
    
   /*! \name Building Block interface
     */
    //@{
    virtual Date getDate() const override;
    virtual std::pair<CashFlowVector, CashFlowVector> getCFs() const override;
    virtual double calibrate(const SmartPointer<ir::Curve>& calibrated) override;
    virtual double calibrate(const SmartPointer<ir::Curve>& discounting, const SmartPointer<ir::Curve>& projection ,const SmartPointer<ir::Curve>& calibrated) override;
    virtual double getParRate(const SmartPointer<ir::Curve>& discounting,const  SmartPointer<ir::Curve>& projection,const  SmartPointer<ir::Curve>& projection2) override;
    virtual double getQuoting() override;
    virtual void changeQuoting(double) override;
    virtual InterestRate getInterestRate() const override;
    std::string info() const override;
    //@}
    
    virtual ~IRS(){};
    virtual IRS* clone() const;
		
    friend std::ostream& operator<<(std::ostream&, IRS&);
  private:
    Date trade_date_;  /*!< @brief The date on which IRS is dealt.*/
    Date start_date_; /*!< @brief The date initial date of first accrual period */
    Date maturity_date_; /*!< @brief The date on which the IRS expires.*/
    CashFlowVector fixed_leg_; /*!< @brief Fixed leg cash flows.*/
    CashFlowVector floating_leg_; /*!< @brief Floating leg cash flows.*/
    InterestRate fixed_leg_rate_; /*!< @brief Convention of fixed leg interest rate.*/
    InterestRate floating_leg_rate_; /*!< @brief Convention of floating leg interest rate.*/ 
    double notional_;  /*!< @brief The amount for which IRS is traded.*/
    double quoting_;  /*!< @brief Interest rate at which IRS is paying fixed leg.*/
    Frequency fixed_leg_freq_;  /*!< @brief Frequency of payment of fixed leg.*/
    Frequency floating_leg_freq_;  /*!< @brief Frequency of payment of floating leg.*/
  };
}
#endif
