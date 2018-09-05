#include <dates/timeGrids/discretizeWithNumberOfSteps.hpp>

namespace julian {

   /** \brief Discretizes the time interval into predefined number of periods
 */   
  std::vector<double> DiscretizeWithNumberOfSteps::operator()(Date startDate, Date endDate, SmartPointer<YearFraction> yf) const {
    double numberOfSteps = static_cast<double>(n_);
    double dt = (yf->operator()(startDate,endDate) ) / numberOfSteps ;
    
    double t = 0.0;
    std::vector<double> result {t};
    for (int i = 0; i < n_; i++) {
      t += dt;
      result.push_back(t);
    }
    return result;
  }

  DiscretizeWithNumberOfSteps* DiscretizeWithNumberOfSteps::clone() const {
    return new DiscretizeWithNumberOfSteps(*this);
  }

}  // namespace julian
