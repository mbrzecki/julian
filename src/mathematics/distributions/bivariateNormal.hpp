#ifndef JULIAN_BIVARIATENORMAL_HPP
#define JULIAN_BIVARIATENORMAL_HPP


namespace julian {

    /**
   * @file   bivariateNormal.hpp
   * @brief  File contains implementation of bivariate normal random variable.
   */
  
  /** \ingroup distributions
   *
   * \brief Class implements Bivariate Normal Random Variable
   
   Class implements algorithm described in \cite bivariate
   */ 

  class BivariateNormal {
  public:
    BivariateNormal(double rho);
    // function
    double operator()(double a, double b) const;
  private:
    double rho_; /*!< \brief Correlation.*/
    double rho2_; /*!< \brief Squared correlation.*/
    static const double x_[]; /*!< \brief Technical tables*/
    static const double y_[]; /*!< \brief Technical tables*/ 
  };
}

#endif
