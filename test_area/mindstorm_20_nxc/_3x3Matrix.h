/* 
  @file _3x3Matrix.h
  @auth Gary Steelman
  @desc The structure declaration and function prototypes for a 3x3 Matrix class
    to be used with the Lego Mindstorm NXT 2.0 kit.
  @edit 16 Mar 2011
*/

#include "numeric_types.h"

typedef struct
{
  sfloat32 m_data[9];
} _3x3Matrix;

// void _3x3Matrix_Construct( _3x3Matrix& M );
// void _3x3Matrix_Destruct ( _3x3Matrix& M );
void _3x3Matrix_Print();

_3x3Matrix _3x3Matrix_Multiply ( const _3x3Matrix& A, const _3x3Matrix& B );
_3x3Matrix _3x3Matrix_Add      ( const _3x3Matrix& A, const _3x3Matrix& B );
_3x3Matrix _3x3Matrix_Subtract ( const _3x3Matrix& A, const _3x3Matrix& B );
void       _3x3Matrix_Copy     ( _3x3Matrix& A, _3x3Matrix& B );
