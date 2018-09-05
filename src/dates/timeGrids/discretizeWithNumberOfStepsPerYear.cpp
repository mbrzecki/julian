#include <dates/timeGrids/discretizeWithNumberOfStepsPerYear.hpp>

namespace julian {

/** \brief Discretize the time interval in a way that each year have the same number of time steps 
*/
  std::vector<double> DiscretizeWithNumberOfStepsPerYear::operator()(Date start_date, Date end_date, SmartPointer<YearFraction> yf) const {
    std::vector<double> result;

    double T = yf->operator()(start_date,end_date);
    int iter = static_cast<int> (n_ * T);
  
    double dt = T / iter;
  
    double t_ = 0;
    result.push_back(t_);
    for (int i = 0; i < iter; i++) {
      t_ += dt;
      result.push_back(t_);
    }

    return result;
  }

  DiscretizeWithNumberOfStepsPerYear* DiscretizeWithNumberOfStepsPerYear::clone() const {
    return new DiscretizeWithNumberOfStepsPerYear(*this);
  }
 
} // namespace julian
