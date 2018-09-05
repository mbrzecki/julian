#ifndef JULIAN_REGRESSION_HPP
#define JULIAN_REGRESSION_HPP

#include <vector>

namespace julian {

  /**
   * @file   regression.hpp
   * @brief  File contains interface of regressions.
   */
  
  /** \ingroup regression
   *
   * \brief Class is an abstract class implementing interface of regression
   *
   * This class is a interface of all regression techniques.
   */

  class Regression {
  public:
    /**
     *  \brief Constructor.
     */
    Regression(){};

    /**
     *  \brief Estimates regression coefficients  
     */
    virtual void estimate(const std::vector<double>& x,const std::vector<double>& y) = 0;
    
    /** \brief return coefficients of the regression
     *
     * The i-th term of vector represents coefficient of \f$x^i\f$
     */
    virtual std::vector<double> getCoefficient() const = 0;
    
    /**
     * \brief Operator performing calculation.
     *
     * This operator returns the value for a given regressor.
     */
    virtual double operator()(double) const = 0;
    
    /** \brief Virtual copy constructor
     */
    virtual Regression* clone() const = 0;

    /** \brief Destructor
     */
    virtual ~Regression(){};
  };

  /** \ingroup regression
   * \brief Class uses Curiously Recurring Template Pattern to implement polymorphic copy construction in every derived class implementing Regression.
   *
   * For more details see \ref cpp_dp_deep_copy
   */
  template<typename T>
  class DeeplyCopyableRegression : public Regression {
  public:
    /** \brief virtual copy constructor
     */
    virtual Regression* clone() const {
      return new T(static_cast<const T&>(*this));
    }
  };
  
} // namespace julian
#endif
