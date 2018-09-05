#include <string>
#include <dates/yearFractions/OneYF.hpp>

namespace julian {

  /**
     Method calculates the year fraction on the basis of two dates.
  */
  double OneYF::operator()(const Date&, const Date&) const {
    return 1.0;
  }

  /** Method is an implementation of virtual copy constructor.
   */
  OneYF* OneYF::clone() const {
    return new OneYF(*this);
  }

  /** Method returns string that containing information about class. 
   */
  std::string OneYF::info() const {
    return "1/1";
  }
}  // namespace julian
