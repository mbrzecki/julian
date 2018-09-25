#include <mathematics/stochasticProcesses/path.hpp>

namespace julian {

  /** \brief constructor
   */
  Path::Path(TimeGrid time,std::vector<double> values): values_(values),time_(time) {
  }
  
  /** \brief returns time series
   */
  std::vector<double> Path::getValues() {
    return values_;
  }

}  // namespace julian
