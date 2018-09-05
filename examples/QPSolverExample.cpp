#include <armadillo>
#include <juliant.hpp>

/**
 * \example QPSolverExample.cpp 
 * \brief Code presents how to solve quadratic programming problem
 *
 * This example shows how to solve a quadratic programming problem formulted by equation:
 *
 * \f[ \arg \min_{x y}  4 x^2 + 2 xy + 5 y^2 + 1.5 x - 2 y\f]
 * \f[\begin{array}{rcr} \text{subject to } &
 *  \\ & 2 \leq 2x + y \leq \infty 
 *  \\ & -\infty \leq -x + 2y \leq 6 
 *  \\ & x \in [0, 20] \text{ and } y \in [0, \infty]  \end{array}\f]
 * Above problem can be rewritten:
 *
 * \f[ \arg \min_{x y} \frac{1}{2} (8 x^2 + 4 xy + 10 y^2) + 1.5 x - 2 y = \arg \min_{x y}  \frac{1}{2} \mathbf{x^T} Q \mathbf{x} + C \mathbf{x^T} \f]
 * \f[\begin{array}{rcr} \text{subject to } &
 *  \\ & \textbf{a} \leq A\textbf{x} \leq \textbf{b}
 *  \\ & \textbf{c} \leq \textbf{x} \leq \textbf{d}  \end{array}\f]
 *  \f[\begin{array}{rcr} \text{where } &
 *  \\ Q = & \begin{bmatrix} 8 & 2 \\ 2 & 10  \end{bmatrix}
 *  \\ C = & \begin{bmatrix} 1.5 \\ -2 \end{bmatrix}
 *  \\ A = & \begin{bmatrix} 2 & 1 \\ -1 & 2  \end{bmatrix}
 *  \\ \textbf{a} = & \begin{bmatrix} 2 \\ -\infty \end{bmatrix}
 *  \\ \textbf{b} = & \begin{bmatrix} \infty \\ 6 \end{bmatrix}
 *  \\ \textbf{c} = & \begin{bmatrix} 0 \\ 0 \end{bmatrix}
 *  \\ \textbf{d} = & \begin{bmatrix} 20 \\ \infty \end{bmatrix}
 *  \end{array}\f]
 * 
 * Matrix form of QP problem allows us to use QuadraticProgrammingSolver to find the minimum. 
 */

using namespace julian;

int main() {
  arma::mat Q, C, A;
  arma::mat a, b, c, d;


  Q << 8.0 << 2.0  << arma::endr
    << 2.0 << 10.0 << arma::endr;

  C << 1.5 << arma::endr
    << -2.0 << arma::endr;

  A << 2.0 << 1.0 << arma::endr
    <<-1.0 << 2.0 << arma::endr;

  a << 2.0 << arma::endr
    << arma::datum::inf << arma::endr;

  b << arma::datum::inf << arma::endr
    << 6.0 << arma::endr;

  c << 0.0 << arma::endr
    << 0.0 << arma::endr;

  d << 20.0  << arma::endr
    << arma::datum::inf << arma::endr;

  /******** setting solver ************/

  QuadraticProgrammingSolver qp_solver;

  qp_solver.setQuadraticTerm(Q);
  qp_solver.setLinearTerm(C);
  qp_solver.setNonEqualityConstrainsMatrix(A);
  qp_solver.setNonEqualityConstrainsLowerVector(a);
  qp_solver.setNonEqualityConstrainsUpperVector(b);
  qp_solver.setArgumentLowerConstrains(c);
  qp_solver.setArgumentUpperConstrains(d);  
  qp_solver.setInfo(true);  
  /******** results ************/

  auto result = qp_solver.solve();
  SHOW(result);

  return 0;
}
