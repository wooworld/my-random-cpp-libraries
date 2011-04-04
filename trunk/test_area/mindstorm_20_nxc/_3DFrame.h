/* 
  @file _3DFrame.h
  @auth Gary Steelman
  @desc The structure declaration and function prototypes for a 3D Frame
    to be used with the Lego Mindstorm NXT 2.0 kit.
  @edit 16 Mar 2011
*/

#include "numeric_types.h"
// #include "numeric_constants.h"
#include "cmath.h"
#include "cstdlib.h"

typedef struct
{
  sfloat32 m[12];
} _3DFrame;

void     _3D_Init      ( _3DFrame& F );
void     _3D_Destroy   ( _3DFrame& F );
void     _3D_Copy      ( _3DFrame& A, const _3DFrame& B );
void     _3D_Print     ( const _3DFrame& F );

_3DFrame _3D_Mult      ( const _3DFrame& A, const _3DFrame& B );

void     _3D_set_rot_x ( _3DFrame& F, sfloat32 alpha );
void     _3D_set_rot_y ( _3DFrame& F, sfloat32 beta  );
void     _3D_set_rot_z ( _3DFrame& F, sfloat32 gamma );

void     _3D_set_x     ( _3DFrame& F, sfloat32 x );
void     _3D_set_y     ( _3DFrame& F, sfloat32 y );
void     _3D_set_z     ( _3DFrame& F, sfloat32 z );
void     _3D_set_loc   ( _3DFrame& F,  sfloat32 x, sfloat32 y, sfloat32 z );

_3DFrame _3D_rot_x     ( _3DFrame& F, sfloat32 alpha );
_3DFrame _3D_rot_y     ( _3DFrame& F, sfloat32 beta );
_3DFrame _3D_rot_z     ( _3DFrame& F, sfloat32 gamma );
_3DFrame _3D_translate ( sfloat32 x, sfloat32 y, sfloat32 z );

void     _3D_clear_rot ( _3DFrame& F );
void     _3D_clear_loc ( _3DFrame& F );
