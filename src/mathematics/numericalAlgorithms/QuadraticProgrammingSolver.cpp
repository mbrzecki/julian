#include <mathematics/numericalAlgorithms/QuadraticProgrammingSolver.hpp>
#include <ooqp/QpGenData.h>
#include <ooqp/QpGenVars.h>
#include <ooqp/QpGenResiduals.h>
#include <ooqp/GondzioSolver.h>
#include <ooqp/QpGenSparseMa27.h>
#include <vector>

namespace julian {
  /** \brief Sets matrix Q
   *
   * Sets matrix Q. 
   */
  void QuadraticProgrammingSolver::setQuadraticTerm(const arma::mat& input) {
    quadratic_term_ = input;
  }

  /** \brief Sets vector L
   *
   * Sets vector L. 
   */
  void QuadraticProgrammingSolver::setLinearTerm(const arma::mat& input) {
    linear_term_ = input;
  }

  /** \brief Sets matrix E
   *
   * Sets matrix E. 
   */
  void QuadraticProgrammingSolver::setEqualityConstrainsMatrix(const arma::mat& input) {
    equality_constrains_matrix_ = input;
  }

  /** \brief Sets vector b
   *
   * Sets vector b. 
   */
  void QuadraticProgrammingSolver::setEqualityConstrainsVector(const arma::mat& input) {
    equality_constrains_vector_ = input;
  }

  /** \brief Sets matrix N
   *
   *  Sets matrix N. 
   */
  void QuadraticProgrammingSolver::setNonEqualityConstrainsMatrix(const arma::mat& input) {
    non_equality_constrains_matrix_ = input;
  }

  /** \brief Sets vector c
   *
   *  Sets vector c 
   */
  void QuadraticProgrammingSolver::setNonEqualityConstrainsLowerVector(const arma::mat& input) {
    non_equality_constrains_lower_vector_ = input;
  }

  /** \brief Sets vector d
   *
   *  Sets vector d 
   */  
  void QuadraticProgrammingSolver::setNonEqualityConstrainsUpperVector(const arma::mat& input) {
    non_equality_constrains_upper_vector_ = input;
  }

  /** \brief Sets vector e
   *
   *  Sets vector e 
   */  
  void QuadraticProgrammingSolver::setArgumentLowerConstrains(const arma::mat& input) {
    argument_lower_constrains_ = input;
  }

  /** \brief Sets vector f
   *
   *  Sets vector f
   */  
  void QuadraticProgrammingSolver::setArgumentUpperConstrains(const arma::mat& input) {    
    argument_upper_constrains_ = input;
  }

  /** \brief Sets silent_ variable
   *
   * Sets silent_ variable 
   *
   */   
  void QuadraticProgrammingSolver::setInfo(const bool input) {
    silent_ = input;
  }
  
  /** \brief Solves quadratic problem
   *
   *  Algorithm used is primal-dual interior-point. Returns the vector of numbers \f$x\f$ which minimizes expression \f$\frac{1}{2}x^T Q x + L^T x \f$ 
   *
   */    
  arma::mat QuadraticProgrammingSolver::solve(){

    /* QuadriaticTerm conversion*/
    const int nnzQ = (quadratic_term_.n_rows * quadratic_term_.n_rows + quadratic_term_.n_rows) / 2;
    int *irowQ = new int[nnzQ];
    int *jcolQ = new int[nnzQ];
    double *dQ = new double[nnzQ];

    SymetricMatrixToArray(irowQ, jcolQ, dQ, quadratic_term_);

    /* Linear Term conversion*/
    const int nx   = quadratic_term_.n_rows;
    double* c = new double[nx];

    if (linear_term_.n_rows) {
      Matrix1dToArray(c, linear_term_);
    } else {
      for (int i = 0; i < nx; i++)
	c[i] = 0.0;
    }
    /* equality_constrains_matrix_ and equality_constrains_vector_ conversion*/
    int my = equality_constrains_vector_.n_rows;
    double *b_ = new double[my];

    int nnzA = equality_constrains_matrix_.n_rows * equality_constrains_matrix_.n_rows;

    int *irowA = new int[nnzA];
    int *jcolA = new int[nnzA];
    double *dA = new double[nnzA];

    if ( equality_constrains_matrix_.n_rows ) {
      Matrix1dToArray(b_, equality_constrains_vector_);
      MatrixToArray(irowA, jcolA, dA, equality_constrains_matrix_);
    }

    /* NonEquality constrains */
    int unsigned mz = non_equality_constrains_matrix_.n_rows;

    double *clow = new double[mz];
    char  *iclow = new char[mz];
    double *cupp = new double[mz];
    char  *icupp = new char[mz];

    int nnzC = non_equality_constrains_matrix_.n_rows * non_equality_constrains_matrix_.n_cols;
    int *irowC = new int[nnzC];
    int *jcolC = new int[nnzC];
    double *dC = new double[nnzC];

    if (non_equality_constrains_matrix_.n_rows )
      MatrixToArray(irowC, jcolC, dC, non_equality_constrains_matrix_);

    if (non_equality_constrains_lower_vector_.n_rows) {
      arma::mat temp(mz, 1);
      for (unsigned int i = 0; i < mz; i++) {
	if (arma::is_finite( non_equality_constrains_lower_vector_(i, 0))) {
	  temp(i, 0) = non_equality_constrains_lower_vector_(i, 0);
	  iclow[i] = 1;
	} else {
	  temp(i, 0) = 0.0;
	  iclow[i] = 0;
	}
      }
      Matrix1dToArray(clow, temp);
    }

    if (non_equality_constrains_upper_vector_.n_rows) {
      arma::mat temp(mz, 1);
      for (unsigned int i = 0; i < mz; i++) {
	if ( arma::is_finite( non_equality_constrains_upper_vector_(i,0))) {
	  temp(i,0) = non_equality_constrains_upper_vector_(i,0);
	  icupp[i] = 1;
	} else {
	  temp(i,0) = 0.0;
	  icupp[i] = 0;
	}
      }
      Matrix1dToArray(cupp, temp);
    }

    /* Argument constrains */

    double *xupp = new double[nx];
    char  *ixupp = new char[nx];

    double *xlow = new double[nx];
    char  *ixlow = new char[nx];


    for (int i = 0; i < nx; i++) {
      xupp[i] = 0.0;
      ixupp[i] = 0;
      xlow[i] = 0.0;
      ixlow[i] = 0;
    }

    if (argument_lower_constrains_.n_rows) {
      arma::mat temp(nx,1);
      for (int i = 0; i < nx; i++) {
	if ( arma::is_finite(argument_lower_constrains_(i, 0))) {
	  temp(i,0) = argument_lower_constrains_(i,0);
	  ixlow[i] = 1;
	} else {
	  temp(i,0) = 0.0;
	  ixlow[i] = 0;
	}
      }
      Matrix1dToArray(xlow, temp);
    }

    if (argument_upper_constrains_.n_rows) {
      arma::mat temp(nx,1);
      for (int i = 0; i < nx; i++) {
	if (arma::is_finite(argument_upper_constrains_(i, 0))) {
	  temp(i,0) = argument_upper_constrains_(i,0);
	  ixupp[i] = 1;
	} else {
	  temp(i,0) = 0.0;
	  ixupp[i] = 0;
	}
      }
      Matrix1dToArray(xupp,temp);
    }

    /* Setting solver*/
    QpGenSparseMa27 * qp
      = new QpGenSparseMa27( nx, my, mz, nnzQ, nnzA, nnzC );

    QpGenData      * prob = (QpGenData * ) qp->copyDataFromSparseTriple(c,      irowQ,  nnzQ,   jcolQ,  dQ,
									xlow,   ixlow,  xupp,   ixupp,
									irowA,  nnzA,   jcolA,  dA,     b_,
									irowC,  nnzC,   jcolC,  dC,
									clow,   iclow,  cupp,   icupp );

    QpGenVars      * vars = (QpGenVars *) qp->makeVariables( prob );
    QpGenResiduals * resid = (QpGenResiduals *) qp->makeResiduals( prob );
    GondzioSolver  * s     = new GondzioSolver( qp, prob );

    if ( silent_ ) {
      s->monitorSelf();
    }

    int ierr = s->solve(prob, vars, resid);

    if (ierr != 0) {
      std::cout << "\nDid not converge\n";
    }

    int qsize = quadratic_term_.n_rows;
    double *array = new double[qsize];
    OoqpVectorHandle simpv = vars -> x;
    simpv->copyIntoArray(array);

    arma::mat result(quadratic_term_.n_rows, 1);

    for (unsigned int i = 0; i < quadratic_term_.n_rows; i++)
      result(i, 0) = array[i];

    delete[] irowQ;
    delete[] jcolQ;
    delete[] dQ;
    delete[] b_;
    delete[] irowA;
    delete[] jcolA;
    delete[] dA;
    delete[] clow;
    delete[] iclow;
    delete[] irowC;
    delete[] jcolC;
    delete[] dC;
    delete[] xupp;
    delete[] ixupp;
    delete[] xlow;
    delete[] ixlow;
    delete[] array;

    delete qp;
    delete s;

    return result;
  }


  /** \brief Symetric matrix adapter
   *
   * Function adapts armadillo matrix to sparse matrix used by OOQP 
   *
   */   
  void QuadraticProgrammingSolver::SymetricMatrixToArray(int* row,int* col, double* A,const arma::mat& B){
    std::vector<int> r,c;
    std::vector<double> w;

    for (unsigned int i = 0; i < B.n_rows ; i++)
      for (unsigned int j = 0 ; j<= i; j++) {
	w.push_back(B(i, j));
	r.push_back(i);
	c.push_back(j);
      }

    int n = (B.n_rows * B.n_rows + B.n_rows) / 2;
    for(int i = 0 ; i < n; i++) {
      A[i]   = w.at(i);
      row[i] = r.at(i);
      col[i] = c.at(i);
    }
  }

  /** \brief Column matrix adapter
   *
   * Function adapts armadillo matrix to sparse matrix used by OOQP 
   *
   */   
  void QuadraticProgrammingSolver::Matrix1dToArray(double* A, const arma::mat& B) {
    for (unsigned int i = 0; i < B.n_rows; i++)
      A[i] = B(i, 0);
  }

  /** \brief Matrix adapter
   *
   * Function adapts armadillo matrix to sparse matrix used by OOQP 
   *
   */   
  void QuadraticProgrammingSolver::MatrixToArray(int* row, int* col, double* A, const arma::mat& B) {
    std::vector<int> r, c;
    std::vector<double> w;
    for (unsigned int i = 0; i < B.n_rows ; i++)
      for (unsigned int j = 0 ; j< B.n_cols; j++) {
	w.push_back(B(i, j));
	r.push_back(i);
	c.push_back(j);
      }

    int n = B.n_rows * B.n_cols;
    for (int i = 0 ; i < n; i++) {
      A[i] = w.at(i);
      row[i] = r.at(i);
      col[i] = c.at(i);
    }
  }
}  // namespace julian
