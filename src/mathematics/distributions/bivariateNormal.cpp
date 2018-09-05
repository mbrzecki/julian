#include <mathematics/distributions/bivariateNormal.hpp>
#include <mathematics/distributions/normalDistribution.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

namespace julian {
  const double BivariateNormal::x_[] = {
    0.24840615,
    0.39233107,
    0.21141819,
    0.03324666,
    0.00082485334
  };

  const double BivariateNormal::y_[] = {
    0.10024215,
    0.48281397,
    1.06094980,
    1.77972940,
    2.66976040000
  };

  /** \brief Constructor
   *
   * Constructor requires parametrization of random variables
   */
  BivariateNormal::BivariateNormal(double rho): rho_(rho), rho2_(rho*rho) {
  }

  /** \brief calculates value of Probability Distribution Function
  */
  double BivariateNormal::operator()(double a, double b) const {
    NormalDistribution cumNormalDist(0.0, 1.0);
    double CumNormDistA = cumNormalDist.CDF(a);
    double CumNormDistB = cumNormalDist.CDF(b);
    double MaxCumNormDistAB = std::max(CumNormDistA, CumNormDistB);
    double MinCumNormDistAB = std::min(CumNormDistA, CumNormDistB);

    if (1.0-MaxCumNormDistAB < 1e-15)
      return MinCumNormDistAB;
    if (MinCumNormDistAB < 1e-15)
      return MinCumNormDistAB;

    double a1 = a / std::sqrt(2.0 * (1.0 - rho2_));
    double b1 = b / std::sqrt(2.0 * (1.0 - rho2_));

    double result = -1.0;

    if (a <= 0.0 && b <= 0.0 && rho_ <= 0.0) {
      double sum = 0.0;
      for (int i =0; i < 5; i++) {
	for (int j = 0; j < 5; j++) {
	  sum += x_[i] * x_[j] *
	    std::exp(a1*(2.0*y_[i]-a1)+b1*(2.0*y_[j]-b1)
		     +2.0*rho_*(y_[i]-a1)*(y_[j]-b1));
	}
      }
      result = std::sqrt(1.0 - rho2_)/3.14159265358979323846264*sum;
    } else if (a <= 0 && b >= 0 && rho_ >= 0) {
	BivariateNormal bivCumNormalDist(-rho_);
	result = CumNormDistA - bivCumNormalDist(a, -b);
    } else if (a>=0.0 && b<=0.0 && rho_>=0.0) {
      BivariateNormal bivCumNormalDist(-rho_);
      result = CumNormDistB - bivCumNormalDist(-a, b);
    } else if (a >= 0.0 && b >= 0.0 && rho_ <= 0.0) {
      result = CumNormDistA + CumNormDistB -1.0 + (*this)(-a, -b);
    } else if (a*b*rho_> 0.0) {
      double rho1 = (rho_*a-b)*(a > 0.0 ? 1.0: -1.0)/std::sqrt(a*a-2.0*rho_*a*b+b*b);
      BivariateNormal bivCumNormalDist(rho1);

      double rho2 = (rho_*b-a)*(b > 0.0 ? 1.0: -1.0) / std::sqrt(a*a - 2.0*rho_*a*b + b*b);
      BivariateNormal CBND2(rho2);

      double delta = (1.0 -(a > 0.0 ? 1.0: -1.0)*(b > 0.0 ? 1.0: -1.0))/4.0;

      result = bivCumNormalDist(a, 0.0) + CBND2(b, 0.0) - delta;
    } else {
      std::cout << "ERROR";
    }
    return result;
  }
}  // namespace julian
