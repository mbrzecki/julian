#include <mathematics/regressions/robustRegression.hpp>
#include <vector>
#include <gsl/gsl_multifit.h>
#include <cmath>

namespace julian {
  /** \brief estimates the parameters basing on provided data
   */
  void RobustRegression::estimate(const std::vector<double>& x,const std::vector<double>& y) {
    const gsl_multifit_robust_type* Type = gsl_multifit_robust_default;

    switch(type_) {
    case BISQUARE: Type = gsl_multifit_robust_bisquare; break;
    case CAUCHY:   Type = gsl_multifit_robust_cauchy;   break;
    case FAIR:     Type = gsl_multifit_robust_fair;     break;
    case HUBER:    Type = gsl_multifit_robust_huber;    break;
    case OLS:      Type = gsl_multifit_robust_ols;      break;
    case WELSCH:   Type = gsl_multifit_robust_welsch;   break;
    }

    gsl_matrix* mat_X;
    gsl_vector* vec_y;

    mat_X = gsl_matrix_alloc (x.size(), order_ + 1);
    vec_y = gsl_vector_alloc (x.size());
    
    for (unsigned int i = 0; i < x.size(); i++) {
      for (int j = 0; j <= order_; j++) {
    	gsl_matrix_set (mat_X, i, j, std::pow(x.at(i), j));
      }
      gsl_vector_set (vec_y, i, y.at(i));
    }

    gsl_vector* vec_c;
    gsl_vector* vec_c_ols;
    gsl_matrix* mat_cov;
    
    vec_c = gsl_vector_alloc (order_ + 1);
    vec_c_ols = gsl_vector_alloc (order_ + 1);
    mat_cov = gsl_matrix_alloc (order_ + 1, order_ + 1);

    gsl_multifit_robust_workspace * work = gsl_multifit_robust_alloc (Type, mat_X->size1, mat_X->size2);
    gsl_multifit_robust (mat_X, vec_y, vec_c, mat_cov, work);

    for ( int i = 0; i <= order_; i++) {
      coefs_.push_back(gsl_vector_get(vec_c, i));
    }

    gsl_matrix_free(mat_X);
    gsl_vector_free(vec_y);
    gsl_vector_free(vec_c);
    gsl_vector_free(vec_c_ols);
    gsl_matrix_free(mat_cov); 
    gsl_multifit_robust_free (work);
  }
  
  double RobustRegression::operator()(double x) const {
    double ret = 0.0;
    double multi = 1.0;
    
    for (auto coef : coefs_) {
      ret += coef * multi;
      multi *= x;
    }
    
    return ret;
  }

  std::vector<double> RobustRegression::getCoefficient() const {
    return coefs_;
  }
  
} // namespace julian

std::ostream& operator<<(std::ostream& s, julian::RobustRegression& r) {
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
