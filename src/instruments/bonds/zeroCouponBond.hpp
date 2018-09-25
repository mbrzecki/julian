#ifndef JULIAN_ZEROCOUPONBOND_HPP
#define JULIAN_ZEROCOUPONBOND_HPP

#include <instruments/bonds/bond.hpp>
#include <instruments/CashFlowVector.hpp>
#include <interestRates/interestRate.hpp>

namespace julian {
  /**
   * @file   zeroCouponBond.hpp
   * @brief  File contains implementation of ZeroCouponBond.
   */
  /** \ingroup bonds
   * \brief Class implements the zero coupon bond. 
   *
   * A zero-coupon bond is a debt security that doesn't pay interest (a coupon), but is traded at a deep discount, rendering profit at maturity when the bond 
   * is redeemed for its full face value.
   *
   * More information see \cite tuckman
   */
  class ZeroCouponBond: public Bond {
  public:
    /**\brief Default constructor
     */
    ZeroCouponBond(){};
    /**\brief Constructor
     */
    ZeroCouponBond(Date issue_date, Date maturity_date, double principal, CashFlowVector cash_flows):
      issue_date_(issue_date), maturity_date_(maturity_date), principal_(principal), cash_flows_(cash_flows) {};
    /*! \name Bond interface
     */
    //@{
    virtual void valuation(const SmartPointer<ir::Curve>&) const override;
    virtual void valuation(const SmartPointer<ir::Curve>&,
			   const SmartPointer<ir::Curve>&) const override;
    virtual double prize(const SmartPointer<ir::Curve>&) const override;
    virtual double prize(const SmartPointer<ir::Curve>&,
			   const SmartPointer<ir::Curve>&) const override;

    virtual double getPrincipal() const override;
    virtual Date getDate() const override;
    virtual ZeroCouponBond* clone() const;
    //@}

    virtual ~ZeroCouponBond(){};
    
    friend std::ostream& operator<<(std::ostream&, ZeroCouponBond&);
  
  private:
    Date issue_date_;           /*!< \brief Bond's issue date*/
    Date maturity_date_;        /*!< \brief Date of repaying original sum loaned*/
    double principal_;          /*!< \brief Principal of bond*/
    CashFlowVector cash_flows_; /*!< \brief Cash Flow Vector containing julian::FixedCashFlow*/ 
  };
}

#endif
