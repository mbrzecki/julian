#ifndef JULIAN_FLOATINGCASHFLOW_HPP
#define JULIAN_FLOATINGCASHFLOW_HPP

#include <instruments/CashFlow.hpp>

namespace julian {

  /**
   * @file   FloatingCashFlow.hpp
   * @brief  File contains definition of floating cash flow class.
   */
  
  /** \ingroup instruments
   *  \brief  Class implements the concept of floating cash flow
   *
   * Floating cash flow is paid on predefined date. Amount of cash paid is dependent on predefined
   * market benchmark. Market benchmark is defined by FloatingCashFlow::fixing_start_ and FloatingCashFlow::fixing_end_ dates.
   * On fixing start date we observe a benchmark rate, which matures on fixing end date. One can modify the amount of CF by additive or multiplicative margin. 
   *
   * Usually floating CF is determined by interest rate given and length of accrual period covering 
   * time interval between FloatingCashFlow::accrual_start_ and FloatingCashFlow::accrual_end_ date.   
   */
  
  class FloatingCashFlow : public CashFlow {
  public:
    FloatingCashFlow(){};
    FloatingCashFlow(Date acc_start, Date acc_end, Date fix_start, Date fix_end, Date payment, double n, double additive_margin, double multiplicative_margin, bool notional_is_paid);
    virtual double price(const SmartPointer<ir::Curve>& disc);
    double value(const SmartPointer<ir::Curve>& disc);
    virtual Date getDate() const;
    virtual double getCF() const;
    virtual double getNotional() const;
    
    void setCashFlow(double amount);
    void setCashFlow(double quote, const InterestRate& rate);
    void setCashFlow(const SmartPointer<ir::Curve>&);
    virtual FloatingCashFlow* clone() const;
    virtual ~FloatingCashFlow(){};
    
    friend std::ostream& operator<<(std::ostream&, FloatingCashFlow&);
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int);
  private:
    Date accrual_start_;/*!< \brief Date determining the beginning of accrual period*/
    Date accrual_end_;  /*!< \brief Date determining the end of accrual period*/
    Date fixing_start_; /*!< \brief Date of fixings the benchmark rate*/
    Date fixing_end_;   /*!< \brief Benchmark rate maturity date*/
    
    Date payment_date_; /*!< \brief Date on which the CF is paid*/
    
    double notional_;   /*!< \brief Notional of the CF*/
    double amount_;     /*!< \brief Amount paid on payment_date_*/
    double additive_margin_;      /*!< \brief Margin added to benchmark date*/ 
    double multiplicative_margin_;/*!< \brief Margin multiplying to benchmark date*/ 
    
    bool notional_is_paid_;/*!< \brief If true notional of CF is paid on payment date with accrued amount */   
  };

  /** \brief interface used by Boost serialization library
   */
  template<class Archive>
  void FloatingCashFlow::serialize(Archive & ar, const unsigned int) {
    boost::serialization::base_object<CashFlow>(*this);
    ar & BOOST_SERIALIZATION_NVP(accrual_start_);
    ar & BOOST_SERIALIZATION_NVP(accrual_end_);
    ar & BOOST_SERIALIZATION_NVP(fixing_start_);
    ar & BOOST_SERIALIZATION_NVP(fixing_end_);      
    ar & BOOST_SERIALIZATION_NVP(payment_date_);
    ar & BOOST_SERIALIZATION_NVP(notional_);
    ar & BOOST_SERIALIZATION_NVP(amount_);
    ar & BOOST_SERIALIZATION_NVP(additive_margin_);
    ar & BOOST_SERIALIZATION_NVP(multiplicative_margin_);
    ar & BOOST_SERIALIZATION_NVP(notional_is_paid_); 
  }
  
}  // namespace julian

#endif /* FLOATINGCASHFLOW_HPP */
