#ifndef JULIAN_CASHFLOWVECTOR_HPP
#define JULIAN_CASHFLOWVECTOR_HPP

#include <instruments/CashFlow.hpp>
#include <utils/smartPointer.hpp>
#include <boost/serialization/vector.hpp>
#include <vector>

namespace julian {

  /**
   * @file   CashFlowVector.hpp
   * @brief  File contains definition of cash flow vector.
   */
  
  /** \ingroup instruments
   * \brief Class helps to handle the vector of CFs.
   *
   * CashFlowVector is building block for almost all instruments generating regular CFs (for example bonds, swaps, etc.). 
   */
  
  class CashFlowVector {
  public:
    CashFlowVector(){};
    /** \brief Constructor
     */
    explicit CashFlowVector(std::vector<SmartPointer<CashFlow> >& cfs_): cfs(cfs_){};

    double prize(const SmartPointer<ir::Curve>& disc) const;
    double valuation(const SmartPointer<ir::Curve>& disc) const;
    
    void updateCashFlows(double quote, const InterestRate& rate);
    void updateCashFlows(const SmartPointer<ir::Curve>&);
    void addCashFlow(SmartPointer<CashFlow> cf);

    SmartPointer<CashFlow> operator[](int) const;

    std::vector<Date> getDates() const;
    int size() const;
    
    friend std::ostream& operator<<(std::ostream&, CashFlowVector&);
    friend class boost::serialization::access;
  private:
    template<class Archive>
    void serialize(Archive & ar,  const unsigned int);
    
    std::vector<SmartPointer<CashFlow> > cfs; /*!< \brief Vector of cashflows */
  };

  /** \brief interface used by Boost serialization library
   */
  template<class Archive>
  void CashFlowVector::serialize(Archive & ar,  const unsigned int) {
    ar & BOOST_SERIALIZATION_NVP(cfs);
  }
}
#endif /* CASHFLOWVECTOR_HPP */
