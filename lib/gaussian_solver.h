// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @auth Gary Steelman
/// @file gaussian_solver.h
/// @edit 14 Nov 2009
/// @brief Contains functionality for solving a Matrix object.
/// @note Row and column addressing and indexing start at number 0, not 1
///   Therefore to get the first row of data, do get_row(0)
///   Or to get the very top-left element of the Matrix, matrix[0][0]
/// @note Column operations are slightly slower than row operations. 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @class gaussian_solver
/// @brief Solves a Matrix using the partial pivoting method.
/// @note Does NOT work with numbers smaller than E-15. These numbers will be
///   considered zero!
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Matrix<T> operator()( Matirx<T> M )
/// @brief Reduces M to reduced row echelon form.
/// @pre A Matrix object exists.
/// @param Matrix<T> M -- The Matrix to reduce to rref.
/// @post Reduces M to rref.
/// @return Matrix<T> -- The rref form of M.
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "matrix_norm.h"
#include "vector.h"
#include "exception.h"
#include <cmath>

template <class T>
class gaussian_solver
{
  public:
    void operator()( Normal_Matrix<T>& M )
    {
      try
      {        
        //Forward elimination
        for ( unsigned long int i = 0; i < M.height(); i++ )
        {
          //Find the largest element in the column at or below us by magnitude
          Vector<T> currColMag( absolute( M.get_col( i ) ) );
          
          //Swaps to the current location the row that has the largest absolute
          //value in the current column below where we are
          M.swap_row( i, 
            (unsigned long int)(currColMag.max_index( i, currColMag.size()-1 )) );

          if ( M[i][i] == 0 ) {}
            //do nothing and move to the next column over, this column is full 
            //of zeroes probably
          
          else  
          {
            //scale down the current row to where the leading coeff is 1
            M.set_row( i, M.scale_row( i, 1 / M[i][i] ) );
            
            //now reduce the rows below this row by multiplying current row by
            //a constant and adding it to other rows
            for ( unsigned long int k = (i+1); k < M.height(); k++ )
            {
              M.set_row( k, (M.scale_row(i, M[k][i]*-1) + M[k])  );
              
              //now do a close to zero check on each element of the row we just
              //changed to try to reduce error propogation
              for ( unsigned long int j = i; j < M.width(); j++ )
                if ( M.closeTo( M[k][j], 0, pow( 10, -15 ) ) )
                  M[k][j] = 0;
            }
          }          
        }
        
        //Backward elimination
        for ( unsigned long int i = M.height()-1; i > 0; i-- )
        { 
          if ( M[i][i] == 0 ) {}
            //do nothing and move to the next column over, this column is full 
            //of zeroes probably
            
          else  
          {
            //scale down the current row to where the leading coeff is 1
            M.set_row( i, M.scale_row( i, 1 / M[i][i] ) );
            
            //now reduce the rows above this row by multiplying the current row
            //by a constant and adding it to other rows
            for ( long int k = (i-1); k >= 0; k-- )
            {
              M.set_row( k, (M.scale_row(i, M[k][i]*-1) + M[k])  );
              
              //now do a close to zero check on each element to try to 
              //reduce error propogation
              for ( unsigned long int j = 0; j < M.width(); j++ )
                if ( M.closeTo( M[k][j], 0, pow( 10, -15 ) ) )
                  M[k][j] = 0;
            }
          }
        }
        
        //and now do a zero check  on the very last row
        for ( unsigned long int i = 0; i < M.width(); i++ )
          if ( M.closeTo( M[M.height()-1][i], 0, pow( 10, -15 ) ) )
            M[M.height()-1][i] = 0;
        
        //return M;
      }
      
      catch ( Exception e )
      {
        throw Exception( e.get_errorCode(), e.get_errorMsg() );
      }
    } 
};

// END OF FILE-----------------------------------------------------------------
