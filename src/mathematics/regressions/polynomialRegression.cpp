#include <mathematics/regressions/polynomialRegression.hpp>
#include <iostream>
#include <string>
#include <gsl/gsl_multifit.h>
#include <cmath>

namespace julian {

  /** \brief evaluates the linear regression model for x 
   */  
  double PolynomialRegression::operator()(double x) const {
    double ret = 0;
    double multi = 1.0;

    for (auto coef : coefs_) {
      ret += coef * multi;
      multi *= x;
    }
    return ret;
  }

  /** \brief return coefficients of the regression
   *
   * The i-th term of vector represents coefficient of i-th power of x
   */
  std::vector<double> PolynomialRegression::getCoefficient() const {
    return coefs_;
  }

  /** \brief estimates the parameters basing on provided data
   */
  void PolynomialRegression::estimate(const std::vector<double>& x,const std::vector<double>& y) {
    gsl_matrix *mat_X, *cov;
    gsl_vector *vec_y, *vec_c;
  
    mat_X = gsl_matrix_alloc (x.size(), order_ + 1);
    vec_y = gsl_vector_alloc (x.size());
    vec_c = gsl_vector_alloc (order_ + 1);
    cov = gsl_matrix_alloc (order_ + 1, order_ + 1);
  
    double chisq;
    for (unsigned int i = 0; i < x.size(); i++) {
      for (int j = 0; j <= order_; j++) {
	gsl_matrix_set (mat_X, i, j, std::pow(x.at(i), j));
      }
      gsl_vector_set (vec_y, i, y.at(i));
    }
    
    gsl_multifit_linear_workspace * work = gsl_multifit_linear_alloc (x.size(), order_ + 1);
    gsl_multifit_linear (mat_X, vec_y, vec_c, cov, &chisq, work);
    gsl_multifit_linear_free (work);

    for ( int i = 0; i <= order_; i++) {
      coefs_.push_back(gsl_vector_get(vec_c, i));
    }
  
    gsl_matrix_free (mat_X);
    gsl_vector_free (vec_y);
    gsl_vector_free (vec_c);
    gsl_matrix_free (cov);
  }

  /** \brief weighted estimates the parameters basing on provided data 
   */
  void PolynomialRegression::estimate(const std::vector<double>& x,const std::vector<double>& y,const std::vector<double>& w) {
    gsl_matrix *mat_X, *cov;
    gsl_vector *vec_y, *vec_c;
    gsl_vector *vec_w;

    mat_X = gsl_matrix_alloc(x.size(), order_+1);
    vec_y = gsl_vector_alloc(x.size());
    vec_w = gsl_vector_alloc(x.size());
    vec_c = gsl_vector_alloc(order_ + 1);
    cov = gsl_matrix_alloc(order_ + 1, order_ + 1);

    double chisq;
    for (unsigned int i = 0; i < x.size(); i++) {
      for (int j = 0; j <= order_; j++) {
	gsl_matrix_set(mat_X, i, j, std::pow(x.at(i), j));
      }
      gsl_vector_set(vec_y, i, y.at(i));
      gsl_vector_set(vec_w, i, w.at(i));
    }

    gsl_multifit_linear_workspace * work = gsl_multifit_linear_alloc(x.size(), order_ + 1);
    gsl_multifit_wlinear(mat_X, vec_w, vec_y, vec_c, cov, &chisq, work);
    gsl_multifit_linear_free(work);

    for ( int i = order_; i > 0; i--) {
      coefs_.push_back(gsl_vector_get(vec_c, i));
    }
  
    gsl_matrix_free (mat_X);
    gsl_vector_free (vec_y);
    gsl_vector_free (vec_w);
    gsl_vector_free (vec_c);
    gsl_matrix_free (cov);
  }  
}

std::ostream& operator<<(std::ostream& s, julian::PolynomialRegression& r) {
  auto c = r.getCoefficient();
  std::string coef;
  std::string sign;

  s << "Y = " << std::to_string(c.at(0));
  for(unsigned int i = 1; i < c.size(); i++) {
    double t = c.at(i);
    if ( t > 0) {
      sign = "+";
      coef = std::to_string(t);
    } else if ( t < 0) {
      sign = "-";
      coef = std::to_string(-t);
    }
      
    s << " " << sign << " " << coef << " X";
    if ( i > 1) s << i;
  }
  s << std::endl;
  return s;
}
