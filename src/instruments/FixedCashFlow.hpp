#ifndef JULIAN_FIXEDCASHFLOW_HPP
#define JULIAN_FIXEDCASHFLOW_HPP

#include <instruments/CashFlow.hpp>

namespace julian {

  /**
   * @file   FixedCashFlow.hpp
   * @brief  File contains definition of fixed cash flow class.
   */
  
  /** \ingroup instruments
   *  \brief  Class implements the concept of fixed cash flow
   *
   * Fixed cash flow is predefined amount paid on predefined date. 
   * Usually fixed cash flow is determined by interest rate given and length of accrual period covering 
   * time interval between FixedCashFlow::accrual_start_ and FixedCashFlow::accrual_end_ date.   
   */

    class FixedCashFlow : public CashFlow {
    public:
      FixedCashFlow(){};
      FixedCashFlow(Date start, Date end ,Date payment, double amount,
		    double notional, bool notional_is_paid);
      FixedCashFlow(Date start, Date end, Date payment, double q,
		    double notional, InterestRate rate, bool notional_is_paid);
      
      virtual double price(const SmartPointer<ir::Curve>& disc) override;
      double value(const SmartPointer<ir::Curve>& disc) override;
      virtual Date getDate() const override;
      virtual double getNotional() const override;
      virtual double getCF() const override;
      
      void setCashFlow(double amount) override;
      void setCashFlow(double quote, const InterestRate& rate) override;
      void setCashFlow(const SmartPointer<ir::Curve>&) override {};
      
      virtual void addToCashFlow(double amount);
      virtual void addToCashFlow(double quote, InterestRate rate);

      virtual FixedCashFlow* clone() const;
      virtual ~FixedCashFlow(){};

      friend std::ostream& operator<<(std::ostream&, FixedCashFlow&);
      friend class boost::serialization::access;
      
    private:

      /** \brief interface used by Boost serialization library
       */
      template<class Archive>
      void serialize(Archive & ar, const unsigned int);

      Date accrual_start_; /*!< \brief Date determining the beginning of accrual period*/
      Date accrual_end_;   /*!< \brief Date determining the end of accrual period*/
      Date payment_date_;  /*!< \brief Date on which the CF is paid*/
      double notional_;    /*!< \brief Notional of the CF*/
      double amount_;      /*!< \brief Amount paid on payment_date_*/

      bool notional_is_paid_; /*!< \brief If true notional of CF is paid on payment date with accrued amount */
    };
  
  template<class Archive>
  void FixedCashFlow::serialize(Archive & ar, const unsigned int){
    boost::serialization::base_object<CashFlow>(*this);
    ar & BOOST_SERIALIZATION_NVP(accrual_start_);
    ar & BOOST_SERIALIZATION_NVP(accrual_end_);
    ar & BOOST_SERIALIZATION_NVP(payment_date_);
    ar & BOOST_SERIALIZATION_NVP(notional_);
    ar & BOOST_SERIALIZATION_NVP(amount_);
    ar & BOOST_SERIALIZATION_NVP(notional_is_paid_);
  }
}  // namespace julian

#endif /* FIXEDCASHFLOW_HPP */
