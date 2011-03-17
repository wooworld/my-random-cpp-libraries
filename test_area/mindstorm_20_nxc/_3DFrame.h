/* 
  @file _3DFrame.h
  @auth Gary Steelman
  @desc The structure declaration and function prototypes for a 3D Frame
    to be used with the Lego Mindstorm NXT 2.0 kit.
  @edit 16 Mar 2011
*/

#include "numeric_types.h"
// #include "_3x3Matrix.h"
// #include "_3DFrame.h"

typedef struct
{
  sfloat32 m[12];
} _3DFrame;

void _3DFrame_Construct( _3DFrame& F );
// void _3DFrame_Destruct ( _3DFrame& P );
void _3DFrame_Copy     ( _3DFrame& A, const _3DFrame& B );
void _3DFrame_Print();

_3DFrame _3DFrame_Multiply ( const _3DFrame& A, const _3DFrame& B );
// _3DPoint _3DFrame_Multiply ( const _3DFrame& F, const _3DPoint& P );
// _3DFrame _3DFrame_Add      ( const _3DFrame& A, const _3DFrame& B );
// _3DFrame _3DFrame_Subtract ( const _3DFrame& A, const _3DFrame& B );

void _3DFrame_Set_Rot  ( const _3x3Matrix& M );
void _3DFrame_Set_Loc  ( const _3DPoint& P );

void _3DFrame_Rotate   ( const _3x3Matrix& M );
void _3DFrame_Translate( const _3x3Point& P );

void _3DFrame_Construct( _3DFrame& F )
{
  m[0]  = 1.0;
  m[5]  = 1.0;
  m[10] = 1.0;
  
  return;
}