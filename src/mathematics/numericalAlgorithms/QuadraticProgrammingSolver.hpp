#ifndef JULIAN_QUADRATICPROGRAMMINGSOLVER_HPP
#define JULIAN_QUADRATICPROGRAMMINGSOLVER_HPP

#include <armadillo>
#include <vector>
#include <utils/utils.hpp>


namespace julian {

  /**
   * @file   QuadraticProgrammingSolver.hpp
   * @brief  File contains implementation of root finder algorithm using derivative.
   */
  
  
  /**\ingroup num_alg
   * \brief Quadratic Programming Solver
   *
   * An algorithm implemented in QuadraticProgrammingSolver  solves following problem:
   * \f[ \min_{x} \frac{1}{2}x^T Q x + L^T x \f] 
   * subject to: <br>
   * \f$E x = b \f$ <br>
   * \f$c <= N x <= d \f$ <br> 
   * \f$e <= x <= f \f$ <br>
   * where: 
   * * \f$Q\f$ is symmetric, positive-definite matrix representing quadratic term
   * * \f$L\f$ is a vector representing linear term
   * * \f$E\f$ is a matrix representing an equality constrain  
   * * \f$N\f$ is a matrix representing non-equality constrain
   *
   * More information about algorithm see OOQP manual \cite ooqp (<a href="http://pages.cs.wisc.edu/~swright/ooqp/ooqp-paper.pdf">link</a>)
   * \remarks Class uses algorithms implemented in OOQP
   */
  
  class QuadraticProgrammingSolver {    
  public:
    QuadraticProgrammingSolver(): silent_(false) {};
    
    void setQuadraticTerm(const arma::mat& );
    void setLinearTerm(const arma::mat& );

    void setEqualityConstrainsMatrix(const arma::mat& );
    void setEqualityConstrainsVector(const arma::mat& );
    
    void setNonEqualityConstrainsMatrix(const arma::mat&);
    void setNonEqualityConstrainsLowerVector(const arma::mat&);
    void setNonEqualityConstrainsUpperVector(const arma::mat&);

    void setArgumentLowerConstrains(const arma::mat& );
    void setArgumentUpperConstrains(const arma::mat& );    
    
    void setInfo(const bool input);
 
    arma::mat solve();  

  private:
    void MatrixToArray(int*,int*,double*,const arma::mat&); 
    void SymetricMatrixToArray(int*,int*,double*,const arma::mat&);
    void Matrix1dToArray(double*,const arma::mat&);

    arma::mat quadratic_term_; /*!< \brief Matrix Q, representing the quadratic term of cost function*/
    arma::mat linear_term_;  /*!< \brief Matrix L, representing the linear term of cost function*/
  
    arma::mat equality_constrains_matrix_;/*!< \brief Matrix E, representing an equality constrain */  
    arma::mat equality_constrains_vector_; /*!< \brief Vector b */ 
    
    arma::mat non_equality_constrains_matrix_; /*!< \brief Matrix N, representing an non-equality constrain */  
    arma::mat non_equality_constrains_lower_vector_; /*!< \brief Vector c */ 
    arma::mat non_equality_constrains_upper_vector_; /*!< \brief Vector d */ 
    
    arma::mat argument_lower_constrains_;/*!< \brief Vector e */ 
    arma::mat argument_upper_constrains_;/*!< \brief Vector f */ 
 
    bool silent_; /*!< \brief If true solve function prints status of each iteration.*/ 
  };
}

// The following is a notice of limited availability of this software and disclaimer which must be included as a preface to the software,
// in all source listings of the code, and in any supporting documentation.
// COPYRIGHT 2001 UNIVERSITY OF CHICAGO
// The copyright holder hereby grants you royalty-free rights to use, reproduce, prepare derivative works, and to redistribute this software to others, provided that any changes are clearly documented.
// This software was authored by:

//     E. MICHAEL GERTZ      gertz@mcs.anl.gov
//     Mathematics and Computer Science Division
//     Argonne National Laboratory
//     9700 S. Cass Avenue
//     Argonne, IL 60439-4844
//     STEPHEN J. WRIGHT     swright@cs.wisc.edu
//     Department of Computer Sciences
//     University of Wisconsin
//     1210 West Dayton Street
//     Madison, WI 53706   FAX: (608)262-9777
// Any questions or comments may be directed to one of the authors.

// ARGONNE NATIONAL LABORATORY (ANL), WITH FACILITIES IN THE STATES OF ILLINOIS AND IDAHO, IS OWNED BY THE UNITED STATES GOVERNMENT, AND OPERATED BY THE UNIVERSITY OF CHICAGO UNDER PROVISION OF A CONTRACT WITH THE DEPARTMENT OF ENERGY.
#endif

