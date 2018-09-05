#ifndef JULIAN_FLOATINGRATEBOND_HPP
#define JULIAN_FLOATINGRATEBOND_HPP

#include <instruments/bonds/bond.hpp>
#include <instruments/CashFlowVector.hpp>
#include <interestRates/interestRate.hpp>
#include <dates/timeUnit.hpp>

namespace julian {
  /**
   * @file   floatingRateBond.hpp
   * @brief  File contains definition of FloatingRateBond.
   */
   
  /** \ingroup bonds
   * \brief Class implements the bond paying floating coupon. 
   *
   * Floating rate bond is represented by julian::CashFlowVector containing FloatingCashFlow. Other data is provided just for information purposes only. 
   *
   * More information see \cite tuckman
   */
  class FloatingRateBond: public Bond {
  public:
    
    /**\brief Default Constructor
     */
    FloatingRateBond(){};

    /**\brief Constructor
     */
    FloatingRateBond(Date issue_date, Date maturity_date, double principal, double margin,
		     InterestRate rate, CashFlowVector cash_flows, Frequency payment_frequency):
      issue_date_(issue_date), maturity_date_(maturity_date), principal_(principal), margin_(margin),
      rate_(rate), cash_flows_(cash_flows), payment_frequency_(payment_frequency) {}

    /*! \name Bond interface
     */
    //@{
    virtual void valuation(const SmartPointer<ir::Curve>& curve) const override;
    virtual void valuation(const SmartPointer<ir::Curve>& discounting_curve,
			   const SmartPointer<ir::Curve>& projection_curve) const override;

    virtual double prize(const SmartPointer<ir::Curve>& curve) const override;
    virtual double prize(const SmartPointer<ir::Curve>& curve,
			 const SmartPointer<ir::Curve>& ) const override;
    virtual double getPrincipal() const override;
    virtual Date getDate() const override;
    virtual FloatingRateBond* clone() const;
    //@}
    
    /** \brief deconstructor
     */    
    virtual ~FloatingRateBond(){};
      
    friend std::ostream& operator<<(std::ostream&, FloatingRateBond&);
  
  private:
    Date issue_date_;            /*!< \brief Bond's issue date*/
    Date maturity_date_;         /*!< \brief Date of repaying original sum loaned*/
    double principal_;           /*!< \brief Principal of bond*/
    double margin_;              /*!< \brief Margin added to cash flows*/
    InterestRate rate_;          /*!< \brief Interest rate convention*/
    CashFlowVector cash_flows_;  /*!< \brief Cash Flow Vector containing julian::FloatingCashFlow*/ 
    Frequency payment_frequency_;/*!< \brief Frequency of coupon payment*/
  };
}

#endif
