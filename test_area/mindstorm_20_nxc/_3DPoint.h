/* 
  @file _3DPoint.h
  @auth Gary Steelman
  @desc The structure declaration and function prototypes for a 3D Point 
    to be used with the Lego Mindstorm NXT 2.0 kit.
  @edit 16 Mar 2011
*/

#include "numeric_types.h"

typedef struct
{
  sfloat32 m_data[3];
} _3DPoint;

// void _3DPoint_Construct( _3DPoint& P );
// void _3DPoint_Destruct ( _3DPoint& P );
void _3DPoint_Print();

// dot product
_3DPoint _3DPoint_Multiply ( const _3DPoint& A, const _3DPoint& B );
_3DPoint _3DPoint_Add      ( const _3DPoint& A, const _3DPoint& B );
_3DPoint _3DPoint_Subtract ( const _3DPoint& A, const _3DPoint& B );
void       _3DPoint_Copy     ( _3DPoint& A, _3DPoint& B );
