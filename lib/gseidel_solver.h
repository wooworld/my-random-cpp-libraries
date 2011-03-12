///////////////////////////////////////////////////////////////////////////////
/// @file gseidelsolver.h
/// @author Gary Steelman
/// @brief -- A class for solving for x in matrix equations of the form Ax = B
///           where B is a single column matrix.
///////////////////////////////////////////////////////////////////////////////
/// @class GSeidelSolver
/// @brief -- A class for solving for x in matrix equations of the form Ax = B
///           where B is a single column matrix.
/////////////////////////////////////////////////////////////////////////////// 
/// @fn MathVec<T> operator()(const Matrix<T> & matrix, const MathVec<T> & vect)
/// @brief -- Solves for x in the equation
///           (matrix) * x = (vect)
///           where vect is a vector (one-column matrix).
/// @pre -- vect.size() == matrix.width()
/// @post -- Returns the solution to the equation.
///////////////////////////////////////////////////////////////////////////////

#ifndef GSEIDELSOLVER_H
#define GSEIDELSOLVER_H

#include "magnitude.h"
#include "matrix.h"
#include "mathvec.h"

const double _TOLERANCE = 1e-20;
const unsigned int _MAX_ITERATIONS = 10000;

class GSeidelSolver
{
  public:
    template <typename T>
    MathVec<T> operator()(const Matrix<T> & matrix, const MathVec<T> & vect)
    {
      //Makes sure the matrix is diagonally dominant
      if ( !matrix.diag_dom() ) 
      {
        throw Exception(104, "Cannot perform Gauss-Seidel Reduction on a matrix "
                             "that is not diagonally dominant. "
                             "(class GSeidelSolver, operator()())");
      }
  
      //Create a vector for our intial guess.
      MathVec<T> approx( vect.size(), 0 );
      
      //Variables for use in the algorithm itself
      double sigma = 0;
      
      //Status tracking
      double error = 1.0;
      unsigned long int num_iterations = 0;
      MathVec<T> papprox( approx );
        
      //Keep iterating on the current x until it stops changing. 
      while ( error > _TOLERANCE && num_iterations < _MAX_ITERATIONS )
      {
        num_iterations+=1; //Increment iterations 
        error = 0;         //Reset error
        papprox = approx;  //Store previous approximation
        
        for ( unsigned int i = 0; i < approx.size(); i++ )
        {
          sigma = 0; //Reset approximation
          
          //Iterates on sigma
          for ( unsigned int j = 0; j < approx.size(); j++ )
            if ( i != j )
              sigma += ( matrix.get_row(i)[j] * approx[j] );
            
          //Calculates the new approximation
          approx[i] = ((vect[i] - sigma)/matrix.get_row(i)[i]);
        }
        
        error = magnitude(((papprox * papprox) - (approx * approx)) / (papprox * papprox));
      }
      
      cout << "(Gauss-Seidel took " << num_iterations << " iterations to complete.)" << endl;
      
      return approx;
    }
};

#endif
