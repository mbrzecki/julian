#include <instruments/CashFlowVector.hpp>
#include <algorithm>
#include <utils/formatters.hpp>

namespace julian {

  /** \brief appends CF to vector 
   */
  void CashFlowVector::addCashFlow(SmartPointer<CashFlow> cf) {
    cfs.push_back(cf);
  }

  /** \brief calculate discounted value of all CFs
   */
  double CashFlowVector::prize(const SmartPointer<ir::Curve>& disc) const {
    double sum = 0;
    for (auto cf : cfs) {
      sum += cf->price(disc);
    }
    return sum;
  }

  /** \brief updates all CFs with given quote
   */
  void CashFlowVector::updateCashFlows(double quote, const InterestRate& rate) {
    for (auto& cf : cfs) {
      cf->setCashFlow(quote, rate);
    }
  }

  /** \brief updates all CFs with forward rates calculated using interest curve provided
   */
  void CashFlowVector::updateCashFlows(const SmartPointer<ir::Curve>& c) {
    for (unsigned int i = 0; i < cfs.size(); i++) {
      cfs.at(i)->setCashFlow(c);
    }
  }

  /** \brief Overloads stream operator
   *
   * This overloaded operator enables to print the curve on the console.
   */
  std::ostream& operator<<(std::ostream& s, CashFlowVector& f) {
    for (auto& cf : f.cfs) {
      Date d = cf->getDate();
      double c = cf->getCF();
      std::cout << d << " " << formatter::currency(c) << std::endl;
    }
    return s;
  }

  /** \brief returns i-th CF
   */
  SmartPointer<CashFlow> CashFlowVector::operator[](int i) const {
    return cfs.at(i);
  }

  /** \brief values the CF
   */
  double CashFlowVector::valuation(const SmartPointer<ir::Curve>& disc) const {
    double value = 0.0;
    for (auto cf : cfs) {
      value += cf->value(disc);
    }
    return value;
  }

  /** \brief returns dates of cfs
   */
  std::vector<Date> CashFlowVector::getDates() const {
    std::vector<Date> ret;
    for (auto cf : cfs) {
      ret.push_back(cf->getDate());
    }
    return ret;
  }

  /** \brief number of CF
   */
  int CashFlowVector:: size() const {
    return cfs.size();
  }
}  // namespace julian

