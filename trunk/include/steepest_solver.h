// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @auth Gary Steelman
/// @file steepest_solver.h
/// @edit 14 Nov 2009
/// @brief Contains functionality for solving a Matrix object.
/// @note Row and column addressing and indexing start at number 0, not 1
///   Therefore to get the first row of data, do get_row(0)
///   Or to get the very top-left element of the Matrix, matrix[0][0]
/// @note Column operations are slightly slower than row operations. 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @class steepest_solver
/// @brief Solves a Matrix using the steepest descent method. 
/// @note Does NOT work with numbers smaller than E-15. These numbers will be
///   considered zero!
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T> operator()( Normal_Matirx<T>& M )
/// @brief Reduces M to reduced row echelon form.
/// @pre A Normal_Matrix object exists.
/// @param Matrix<T> M -- The Normal_Matrix to reduce to rref.
/// @post Reduces M to rref.
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool rowDominance( const unsigned long int& n, const Vector<T>& v )
/// @brief Returns if the given element in the row is dominant 
/// @pre n < v.size()
/// @param const unsigned long int& n -- The element to check in the row
/// @param const Vector<T>& v -- The row to check for dominance
/// @post Returns true if the given element in the row is dominant
/// @return bool -- true if the given element is dominant in the row
/// @return bool -- false if the given element is NOT dominant in the row
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool diagDominance( const Normal_Matrix<T>& M )
/// @brief Checks the given Matrix for diagonal dominance
/// @pre M exists.
/// @param const Normal_Matrix<T>& M -- The matrix to check for dominance
/// @post Returns true if the Matrix is diagonally dominant.
/// @return bool -- true if the given Matrix is diagonally dominant
/// @return bool -- false if the given Matrix is NOT diagonally dominant
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "matrix_norm.h"
#include "vector.h"
#include "exception.h"
#include <cmath>

template <class T>
class steepest_solver
{
  public:
    Vector<T> operator()( const Normal_Matrix<T>& M, const unsigned long int& iterations )
    {
      try
      {        
        Vector<T> NULLVECT;
        //check for diagonal dominance
        if ( diagDominance( M ) != true )
          return NULLVECT;
        
        //Sets up the right hand side, F, of the Matrix
        Vector<T> F( M.get_col( M.width() - 1 ) );
        
        //Sets up the coefficient matrix of the Matrix
        Normal_Matrix<T> A(M);
        A.delete_col( A.width() -1 );
        Vector<T> xn( A.width() );
        Vector<T> r( F - A*xn );
        
        for ( unsigned long int i = 0; i < iterations; i++ )
        {
          r = F - A*xn;
          xn = xn + r.scale( innerProduct( r, r ) / innerProduct( A*r, r ) );
        }
        
        return xn;  
      }
      
      catch ( Exception e )
      {
        throw Exception( e.get_errorCode(), e.get_errorMsg() );
      }
    } 
    
  private:
    bool rowDominance( const unsigned long int& n, const Vector<T>& v )
    {
      if ( n > v.size() )
        throw( Exception( 2, "Out of bounds access. steepest_solver rowDominance()." ) );
        
      T sum = T();
      Vector<T> absv( absolute( v ) );
      for ( unsigned long int i = 0; i < absv.size(); i++ )
        sum+=v[i];
        
      sum-=v[n];
      
      if ( sum < v[n] )
        return true;
        
      return false;
    }
    
    bool diagDominance( const Normal_Matrix<T>& M )
    {
      Normal_Matrix<T> withoutRHS( M );
      withoutRHS.delete_col( M.width()-1 );
      for ( unsigned long int i = 0; i < withoutRHS.height(); i++ )
        if ( rowDominance( i, withoutRHS[i] ) != true ) 
          return false;
      
      return true;
    }
};

// END OF FILE-----------------------------------------------------------------
