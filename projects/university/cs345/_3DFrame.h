/*
  @file _3DFrame.h
  @auth Gary Steelman
  @desc The structure declaration and function prototypes for a 3D Frame
    to be used with the Lego Mindstorm NXT 2.0 kit.
  @edit 12 Apr 2011
  @note This file includes many optimizations specifically for use with NXC on
    the Lego Mindstorm NXT 2.0.
*/

#ifndef _3DFRAMEH
#define _3DFRAMEH

#include "NXCDefs.h"

// The initial array structure for a 3D Frame.
float _3D_INIT_ARRAY[] = { 1.0, 0.0, 0.0, 0.0,
                           0.0, 1.0, 0.0, 0.0,
                           0.0, 0.0, 1.0, 0.0 };

#define _3D_Init( _F )      _F = _3D_INIT_ARRAY
#define _3D_Copy( _A, _B )  _A = _B

#define _3D_set_x( _F, _x ) _F[3] = _x
#define _3D_set_y( _F, _y ) _F[7] = _y
#define _3D_set_z( _F, _z ) _F[11] = _z

void     _3D_Print       ( float F[] );
void     _3D_Print_Upper ( float F[] );
void     _3D_Print_Lower ( float F[] );
                           
void     _3D_Mult        ( float A[], float B[], float& C[] );

void     _3D_set_rot_x   ( float& F[], float alpha );
void     _3D_set_rot_y   ( float& F[], float beta );
void     _3D_set_rot_z   ( float& F[], float gamma );

void     _3D_set_loc     ( float F[], float x, float y, float z, float& G[] );

void     _3D_rot_x       ( float F[], float alpha, float& G[] );
void     _3D_rot_y       ( float F[], float beta, float& G[] );
void     _3D_rot_z       ( float F[], float gamma, float& G[] );
void     _3D_rot_euler   ( float F[], float phi, float theta, float psi, float& G[] );
void     _3D_translate   ( float F[], float x, float y, float z, float& G[] );

void     _3D_move        ( float F[], float G[] );

void     _3D_clear_rot   ( float& F[] );
void     _3D_reset_rot   ( float& F[] );
void     _3D_clear_loc   ( float& F[] );

/******************************************************************************/

void _3D_Print( float F[] )
{
  _3D_Print_Upper( F );
}

void _3D_Print_Upper( float F[] )
{
  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 3; j++ )
       TextOut( i*24, LCD_LINE1-8*j, FormatNum( "%4.1f", F[(j*4) + i] ) );
}

void _3D_Print_Lower( float F[] )
{
  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 3; j++ )
       TextOut( i*24, LCD_LINE5-8*j, FormatNum( "%4.1f", F[(j*4) + i] ) );
}

void _3D_Mult( float A[], float B[], float& C[] )
{
  float A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11;
  float B0, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11;
  
  A0  = A[0]; A1  = A[1]; A2  = A[2];  A3  = A[3];
  A4  = A[4]; A5  = A[5]; A6  = A[6];  A7  = A[7];
  A8  = A[8]; A9  = A[9]; A10 = A[10]; A11 = A[11];
  
  B0  = B[0]; B1  = B[1]; B2  = B[2];  B3  = B[3];
  B4  = B[4]; B5  = B[5]; B6  = B[6];  B7  = B[7];
  B8  = B[8]; B9  = B[9]; B10 = B[10]; B11 = B[11];
  
  C[0]  = A0*B0 + A1*B4 + A2*B8;
  C[1]  = A0*B1 + A1*B5 + A2*B9;
  C[2]  = A0*B2 + A1*B6 + A2*B10;
  C[3]  = A0*B3 + A1*B7 + A2*B11 + A3;
  C[4]  = A4*B0 + A5*B4 + A6*B8;
  C[5]  = A4*B1 + A5*B5 + A6*B9;
  C[6]  = A4*B2 + A5*B6 + A6*B10;
  C[7]  = A4*B3 + A5*B7 + A6*B11 + A7;
  C[8]  = A8*B0 + A9*B4 + A10*B8;
  C[9]  = A8*B1 + A9*B5 + A10*B9;
  C[10] = A8*B2 + A9*B6 + A10*B10;
  C[11] = A8*B3 + A9*B7 + A10*B11 + A11;  
}

void _3D_set_rot_x( float& F[], float alpha )
{
  float sa  = sin(alpha);
  float ca  = cos(alpha);
  float nsa = -sa;
  float F3, F7, F11;
  
  F3 = F[3]; F7 = F[7]; F11 = F[11];
  
  ArrayBuild( F, 1.0, 0.0, 0.0, F3,
                 0.0, ca,  nsa, F7,
                 0.0, sa,  ca,  F11 );  
}

void _3D_set_rot_y( float& F[], float beta )
{
  float sb  = sin( beta );
  float cb  = cos( beta );
  float nsb = -sb;
  float F3, F7, F11;
  
  F3 = F[3]; F7 = F[7]; F11 = F[11];
  
  ArrayBuild( F, cb,  0.0, sb,  F3,
                 0.0, 1.0, 0.0, F7,
                 nsb, 0.0, cb,  F11 );
}

void _3D_set_rot_z( float& F[], float gamma )
{
  float sg  = sin( gamma );
  float cg  = cos( gamma );
  float nsg = -sg;
  float F3, F7, F11;
  
  F3 = F[3]; F7 = F[7]; F11 = F[11];
  
  ArrayBuild( F, cg,  nsg, 0.0, F3,
                 sg,  cg,  0.0, F7,
                 0.0, 0.0, 1.0, F11 );
}

void _3D_set_rot_euler( float F[], float phi, float theta, float psi )
{
  float F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11;
  float G0, G1, G2, G3, G4, G5, G6, G7, G8, G9, G10, G11;
  float sphi   = sin( phi );
  float cphi   = cos( phi );
  float stheta = sin( theta );
  float ctheta = cos( theta );
  float spsi   = sin( psi );
  float cpsi   = cos( psi );
  
  G[0] = (cphi * ctheta * cpsi) - (sphi * spsi);
  G[1] = 
  
  A0  = A[0]; A1  = A[1]; A2  = A[2];  A3  = A[3];
  A4  = A[4]; A5  = A[5]; A6  = A[6];  A7  = A[7];
  A8  = A[8]; A9  = A[9]; A10 = A[10]; A11 = A[11];
  
  B0  = B[0]; B1  = B[1]; B2  = B[2];  B3  = B[3];
  B4  = B[4]; B5  = B[5]; B6  = B[6];  B7  = B[7];
  B8  = B[8]; B9  = B[9]; B10 = B[10]; B11 = B[11];
  
  C[0]  = A0*B0 + A1*B4 + A2*B8;
  C[1]  = A0*B1 + A1*B5 + A2*B9;
  C[2]  = A0*B2 + A1*B6 + A2*B10;
  C[3]  = A0*B3 + A1*B7 + A2*B11 + A3;
  C[4]  = A4*B0 + A5*B4 + A6*B8;
  C[5]  = A4*B1 + A5*B5 + A6*B9;
  C[6]  = A4*B2 + A5*B6 + A6*B10;
  C[7]  = A4*B3 + A5*B7 + A6*B11 + A7;
  C[8]  = A8*B0 + A9*B4 + A10*B8;
  C[9]  = A8*B1 + A9*B5 + A10*B9;
  C[10] = A8*B2 + A9*B6 + A10*B10;
  C[11] = A8*B3 + A9*B7 + A10*B11 + A11;  
}

void _3D_rot_x( float F[], float alpha, float& G[] )
{
  float rot_x[12];
  float temp[12];
  
  _3D_set_rot_x( rot_x, alpha );

  _3D_Mult( F, rot_x, G );
}

void _3D_rot_y( float F[], float beta, float& G[] )
{
  float rot_y[12];
  float temp[12];
  
  _3D_set_rot_y( rot_y, beta );

  _3D_Mult( F, rot_y, G );
}

void _3D_rot_z( float F[], float gamma, float& G[] )
{
  float rot_z[12];
  float temp[12];
  
  _3D_set_rot_z( rot_z, gamma );

  _3D_Mult( F, rot_z, G );
}

void _3D_rot_euler( float F[], float phi, float theta, float psi, float& G[] )
{
  float rot_euler[12];
  float temp[12];
  
  _3D_set_rot_euler( rot_euler, phi, theta, psi );
  
  _3D_Mult( F, rot_euler, G );
}

void _3D_set_loc( float F[], float x, float y, float z, float& G[] )
{
  _3D_set_x( F, x );
  _3D_set_y( F, y );
  _3D_set_z( F, z );
}

void _3D_translate( float& F[], float x, float y, float z, float& G[] )
{
  G = F;
  
  G[3]  = F[0]*x + F[1]*y + F[2]*z + F[3];
  G[7]  = F[4]*x + F[5]*y + F[6]*z + F[7];
  G[11] = F[8]*x + F[9]*y + F[10]*z + F[11];
}

void _3D_move( float F[], float G[] )
{
  // Perform inverse kinematics to find the angles for the motors necessary
  // to move from F to G.
  //_3D_Print_Upper( F );
  //_3D_Print_Lower( G );
  
  //Wait( SEC_5 );
}

void _3D_clear_rot( float& F[] )
{
  float F3, F7, F11;
  
  F3 = F[3]; F7 = F[7]; F11 = F[11];
  
  ArrayBuild( F, 0.0, 0.0, 0.0, F3,
                 0.0, 0.0, 0.0, F7,
                 0.0, 0.0, 0.0, F11 );  
}

void _3D_reset_rot( float& F[] )
{
  float F3, F7, F11;
  
  F3 = F[3]; F7 = F[7]; F11 = F[11];
  
  ArrayBuild( F, 1.0, 0.0, 0.0, F3,
                 0.0, 1.0, 0.0, F7,
                 0.0, 0.0, 1.0, F11 );  
}

void _3D_clear_loc( float& F[] )
{
  F[3]  = 0.0;
  F[7]  = 0.0;
  F[11] = 0.0;
}

#endif
