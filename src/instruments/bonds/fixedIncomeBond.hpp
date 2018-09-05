#ifndef JULIAN_FIXEDINCOMEBOND_HPP
#define JULIAN_FIXEDINCOMEBOND_HPP

#include <instruments/bonds/bond.hpp>
#include <instruments/CashFlowVector.hpp>
#include <interestRates/interestRate.hpp>
#include <dates/timeUnit.hpp>

namespace julian {
  /**
   * @file   fixedIncomeBond.hpp
   * @brief  File contains definition of FixedIncomeBond.
   */
   
  /** \ingroup bonds
   * \brief Class implements the bond paying fixed coupon. 
   *
   * A fixed coupon bond is represented by julian::CashFlowVector containing FixedCashFlow. Other data is provided just for information purposes only.
   *
   * More information see \cite tuckman 
   */
  class FixedIncomeBond: public Bond {
  public:
    /**\brief Default Constructor
     */
    FixedIncomeBond(){};

    /**\brief Constructor
     */
    FixedIncomeBond(Date issue_date, Date maturity_date, double principal, double coupon, InterestRate rate, CashFlowVector cash_flows, Frequency payment_frequency):
      issue_date_(issue_date), maturity_date_(maturity_date), principal_(principal), coupon_(coupon), rate_(rate), cash_flows_(cash_flows), payment_frequency_(payment_frequency) {};
    /*! \name Bond interface
     */
    //@{
    virtual void valuation(const SmartPointer<ir::Curve>& curve) const override;
    virtual void valuation(const SmartPointer<ir::Curve>& curve, const SmartPointer<ir::Curve>& ) const override;
    
    virtual double prize(const SmartPointer<ir::Curve>& curve) const override;
    virtual double prize(const SmartPointer<ir::Curve>& curve, const SmartPointer<ir::Curve>& ) const override;
    
    virtual double getPrincipal() const override;
    virtual Date getDate() const override;
    virtual FixedIncomeBond* clone() const override;
    //@}

    double getCoupon() const;
    
    /** \brief destructor
     */
    virtual ~FixedIncomeBond(){};
       
    friend std::ostream& operator<<(std::ostream&, FixedIncomeBond&);
  
  private:
    Date issue_date_;            /*!< \brief Bond's issue date*/
    Date maturity_date_;         /*!< \brief Date of repaying original sum loaned*/
    double principal_;           /*!< \brief Principal of bond*/
    double coupon_;              /*!< \brief Coupon paid by bond*/
    InterestRate rate_;          /*!< \brief Interest rate convention*/
    CashFlowVector cash_flows_;  /*!< \brief Cash Flow Vector containing julian::FixedCashFlow*/ 
    Frequency payment_frequency_;/*!< \brief Frequency of coupon payment*/
  };
}

#endif
