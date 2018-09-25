#include <dates/timeGrids/discretizeWithTenor.hpp>

namespace julian {

/** \ brief Class discretize the time interval in such way that distance between each nodes is equal to tenor provided.
*/
  std::vector<double> DiscretizeWithTenor::operator()(Date start_date, Date end_date, SmartPointer<YearFraction> yf) const {
    std::vector<double> result;
    Date d(start_date);
    double temp = 0;
    result.push_back(temp);
  
  while(1) {
    d += tenor_;
    if (d >= end_date) {
      break;
    }
    
    temp = yf->operator()(start_date,d);
    result.push_back(temp);
  }
      
  temp = yf->operator()(start_date,end_date);
  result.push_back(temp);
  return result;
 }

  DiscretizeWithTenor* DiscretizeWithTenor::clone() const {
    return new DiscretizeWithTenor(*this);
  }
}  // namespace julian
