/* 
  @file 3DFrame.h
  @auth Gary Steelman
  @desc The structure declaration and function prototypes for a 3D Frame
    to be used with the Lego Mindstorm NXT 2.0 kit.
  @edit 09 Apr 2011
*/

#include "NXCDefs.h"

#ifndef _3DFRAMEH
#define _3DFRAMEH

typedef struct
{
  float m[12];
} _3DFrame;

void     _3D_Init      ( _3DFrame& F );
void     _3D_Destroy   ( _3DFrame& F );
void     _3D_Copy      ( _3DFrame& A, const _3DFrame& B );
void     _3D_Print     ( const _3DFrame& F );

_3DFrame _3D_Mult      ( const _3DFrame& A, const _3DFrame& B );

void     _3D_set_rot_x ( _3DFrame& F, float alpha );
void     _3D_set_rot_y ( _3DFrame& F, float beta  );
void     _3D_set_rot_z ( _3DFrame& F, float gamma );

void     _3D_set_x     ( _3DFrame& F, float x );
void     _3D_set_y     ( _3DFrame& F, float y );
void     _3D_set_z     ( _3DFrame& F, float z );
void     _3D_set_loc   ( _3DFrame& F, float x, float y, float z );

_3DFrame _3D_rot_x     ( _3DFrame& F, float alpha );
_3DFrame _3D_rot_y     ( _3DFrame& F, float beta );
_3DFrame _3D_rot_z     ( _3DFrame& F, float gamma );
_3DFrame _3D_translate ( _3DFrame& F, float x, float y, float z );

void     _3D_clear_rot ( _3DFrame& F );
void     _3D_clear_loc ( _3DFrame& F );

safecall void _3D_Init( _3DFrame& F )
{
  F.m[0]  = 1.0;
  F.m[1]  = 0.0;
  F.m[2]  = 0.0;
  F.m[3]  = 0.0;
  F.m[4]  = 0.0;
  F.m[5]  = 1.0;
  F.m[6]  = 0.0;
  F.m[7]  = 0.0;
  F.m[8]  = 0.0;
  F.m[9]  = 0.0;
  F.m[10] = 1.0;
  F.m[11] = 0.0;

  return;
}

safecall void _3D_Destroy( _3DFrame& F )
{
}

safecall void _3D_Copy( _3DFrame& A, const _3DFrame& B )
{
  A.m[0]  = B.m[0];
  A.m[1]  = B.m[1];
  A.m[2]  = B.m[2];
  A.m[3]  = B.m[3];
  A.m[4]  = B.m[4];
  A.m[5]  = B.m[5];
  A.m[6]  = B.m[6];
  A.m[7]  = B.m[7];
  A.m[8]  = B.m[8];
  A.m[9]  = B.m[9];
  A.m[10] = B.m[10];
  A.m[11] = B.m[11];
}

void _3D_Print( const _3DFrame& F )
{
  for ( unsigned char i = 0; i < 12; i++ )
  {
    printf( "% 10.3f ", F.m[i] );

    if ( (i+1) % 4 == 0 )
      printf( "%d", 0 );
  }

  printf( "%d", 0 );
}

// TODO

_3DFrame _3D_Mult( const _3DFrame& A, const _3DFrame& B )
{
  _3DFrame temp;

  temp.m[0]  = 0.0;
  temp.m[1]  = 0.0;
  temp.m[2]  = 0.0;
  temp.m[3]  = 0.0;
  temp.m[4]  = 0.0;
  temp.m[5]  = 0.0;
  temp.m[6]  = 0.0;
  temp.m[7]  = 0.0;
  temp.m[8]  = 0.0;
  temp.m[9]  = 0.0;
  temp.m[10] = 0.0;
  temp.m[11] = 0.0;

  return temp;
}

safecall void _3D_set_rot_x( _3DFrame& F, float alpha )
{
  float sa = sin( alpha );
  float ca = cos( alpha );

  F.m[0]  = 1.0;
  F.m[1]  = 0.0;
  F.m[2]  = 0.0;
  F.m[4]  = 0.0;
  F.m[5]  = ca;
  F.m[6]  = -1.0 * sa;
  F.m[8]  = 0.0;
  F.m[9]  = sa;
  F.m[10] = ca;

  return;
}

safecall void _3D_set_rot_y( _3DFrame& F, float beta )
{
  float sb = sin( beta );
  float cb = cos( beta );

  F.m[0]  = cb;
  F.m[1]  = 0.0;
  F.m[2]  = sb;
  F.m[4]  = 0.0;
  F.m[5]  = 1.0;
  F.m[6]  = 0.0;
  F.m[8]  = -1.0 * sb;
  F.m[9]  = 0.0;
  F.m[10] = cb;

  return;
}

safecall void _3D_set_rot_z( _3DFrame& F, float gamma )
{
  float sg = sin( gamma );
  float cg = cos( gamma );

  F.m[0]  = cg;
  F.m[1]  = -1.0 * sg;
  F.m[2]  = 0.0;
  F.m[4]  = sg;
  F.m[5]  = cg;
  F.m[6]  = 0.0;
  F.m[8]  = 0.0;
  F.m[9]  = 0.0;
  F.m[10] = 1.0;

  return;
}

safecall void _3D_set_x( _3DFrame& F, float x )
{
  F.m[3] = x;

  return;
}

safecall void _3D_set_y( _3DFrame& F, float y )
{
  F.m[7] = y;

  return;
}

safecall void _3D_set_z( _3DFrame& F, float z )
{
  F.m[11] = z;

  return;
}

safecall void _3D_set_loc  ( _3DFrame& F,  float x, float y, float z )
{
  F.m[3]  = x;
  F.m[7]  = y;
  F.m[11] = z;

  return;
}

_3DFrame _3D_rot_x( _3DFrame& F, float alpha )
{
  _3DFrame temp;

  _3D_set_rot_x( temp, alpha );

  return _3D_Mult( temp, F );
}

_3DFrame _3D_rot_y( _3DFrame& F, float beta )
{
  _3DFrame temp;

  _3D_set_rot_y( temp, beta );

  return _3D_Mult( temp, F );
}

_3DFrame _3D_rot_z( _3DFrame& F, float gamma )
{
  _3DFrame temp;

  _3D_set_rot_z( temp, gamma );

  return _3D_Mult( temp, F );
}

_3DFrame _3D_translate( _3DFrame& F, float x, float y, float z )
{
  _3DFrame temp;

  temp.m[3]  = F.m[0]*x + F.m[1]*y + F.m[2]*z + F.m[3];
  temp.m[7]  = F.m[4]*x + F.m[5]*y + F.m[6]*z + F.m[7];
  temp.m[11] = F.m[8]*x + F.m[9]*y + F.m[10]*z + F.m[11];

  return temp;
}

safecall void _3D_clear_rot( _3DFrame& F )
{
  F.m[0]  = 0.0;
  F.m[1]  = 0.0;
  F.m[2]  = 0.0;
  F.m[4]  = 0.0;
  F.m[5]  = 0.0;
  F.m[6]  = 0.0;
  F.m[8]  = 0.0;
  F.m[9]  = 0.0;
  F.m[10] = 0.0;

  return;
}

safecall void _3D_clear_loc( _3DFrame& F )
{
  F.m[3]  = 0.0;
  F.m[7]  = 0.0;
  F.m[11] = 0.0;

  return;
}

#endif
