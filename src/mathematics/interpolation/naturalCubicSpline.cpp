#include <mathematics/interpolation/naturalCubicSpline.hpp>
#include <cmath>
#include <vector>
#include <string>

namespace julian {

  /** \brief Performs interpolation
    
    This operator returns value of interpolant at the point x. 
  */
  double NaturalCubicSpline::operator()(const std::vector<double>& x, const std::vector<double>& a, const double& s) const {
    BOOST_ASSERT_MSG(s >= x.front(), "Cannot return value for argument lower then first nodal point ");
    BOOST_ASSERT_MSG(s <= x.back(), "Cannot return value for argument higher then last nodal point ");
    BOOST_ASSERT_MSG(x.size() == a.size(), "Size of x and is different then size of  y vector. ");
    if ( s == x.back() )
      return a.back();
    if ( s == x.at(0))
      return a.at(0);

    int n = x.size();
    std::vector<double> h(n-1, 0.0);
    std::vector<double> alpha(n-1, 0.0);

    for (int i = 0; i <= n-2; i++)
      h[i] = x[i+1] - x[i];

    for (int i = 1; i <= n-2; i++)
      alpha[i] = 3.0/h[i]*(a[i+1] - a[i]) - 3.0/h[i-1]*(a[i] - a[i-1]);

    std::vector<double> l(n, 0.0);
    std::vector<double> u(n, 0.0);
    std::vector<double> z(n, 0.0);
    std::vector<double> c(n, 0.0);
    std::vector<double> b(n, 0.0);
    std::vector<double> d(n, 0.0);
    
    l[0] = 1;
    u[0] = 0;
    z[0] = 0;
    l[n-1] = 1;
    z[n-1] = 0;
    c[n-1] = 0;

    for (int i = 1; i <= n-2; i++) {
      l[i] = 2 * (x[i+1] - x[i-1]) - h[i-1]*u[i - 1];
      u[i] = h[i] / l[i];
      z[i] = (alpha[i] - h[i-1]*z[i-1]) / l[i];
    }

    for (int i = n-2; i >= 0; i--) {
      c[i] = z[i] - u[i]*c[i+1];
      b[i] = (a[i+1] - a[i]) / h[i] - h[i]*(c[i+1] + 2*c[i]) / 3;
      d[i] = (c[i+1] - c[i]) / 3 / h[i];
    }

    for (int i = 0; i <= n-2; i++) {
      if ((x[i] <= s) && (s <= x[i+1]))
	return a[i] + b[i]*(s - x[i]) + c[i]*pow(s-x[i], 2) + d[i]*pow(s-x[i], 3);
    }
    return 0.0;
  }
  
  /** \brief Virtual copy constructor
    
      Method is an implementation of virtual copy constructor.
  */

  NaturalCubicSpline* NaturalCubicSpline::clone() const {
    return new NaturalCubicSpline(*this);
  }

  
  int unsigned NaturalCubicSpline::getMinSize() const {
    return 4;
  }
  
  /** \brief Name of a class
      
      Method returns string that containing information about class. 
  */
  std::string NaturalCubicSpline::info() const {
    return "NaturalCubicSpline";
  }
}  // namespace julian
