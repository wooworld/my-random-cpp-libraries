/*
  @file _3DFrame.h
  @auth Gary Steelman
  @desc The structure declaration and function prototypes for a 3D Frame
    to be used with the Lego Mindstorm NXT 2.0 kit.
  @edit 09 Apr 2011
*/

#ifndef _3DFRAMEH
#define _3DFRAMEH

#include "NXCDefs.h"

#define _3DFrame float[];

// Due to current BricxCC implementation this is necessary
float _3D_INIT_ARRAY[] = {1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0};

void _3D_Mult        ( float A[], float B[], float& C[] );

void     _3D_set_rot_x   ( float& F[], float alpha );
void     _3D_rot_x       ( float& F[], float alpha );

void     _3D_Init        ( float& F[] );
void     _3D_Copy        ( float& A[], float B[] );
void     _3D_Print       ( float F[] );
void     _3D_translate   ( float& F[], float x, float y, float z );
void     _3D_move        ( float F[], float G[] );


safecall void _3D_Init( float F[] )
{
  F = _3D_INIT_ARRAY;

  return;
}

safecall void _3D_Copy( float A[], float B[] )
{
  A = B;

  return;
}
void _3D_Print( float F[] )
{
  // For each column of the matrix
  for ( int i = 0; i < 4; i++ )
  {
    // For each row of the matrix
    for ( int j = 0; j < 3; j++ )
    {
       // Each character is 5 px wide, +1 space between chars
       TextOut( i*24, LCD_LINE1-8*j, FormatNum( "%4.1f", F[(j*4) + i] ) );
    }
  }
}

void _3D_Print_Upper( float F[] )
{
  // For each column of the matrix
  for ( int i = 0; i < 4; i++ )
  {
    // For each row of the matrix
    for ( int j = 0; j < 3; j++ )
    {
       // Each character is 5 px wide, +1 space between chars
       TextOut( i*24, LCD_LINE1-8*j, FormatNum( "%4.1f", F[(j*4) + i] ) );
    }
  }
  
  return;
}

void _3D_Print_Lower( float F[] )
{
  // For each column of the matrix
  for ( int i = 0; i < 4; i++ )
  {
    // For each row of the matrix
    for ( int j = 0; j < 3; j++ )
    {
       // Each character is 5 px wide, +1 space between chars
       TextOut( i*24, LCD_LINE5-8*j, FormatNum( "%4.1f", F[(j*4) + i] ) );
    }
  }
}

void _3D_translate( float F[], float x, float y, float z )
{
  float temp[12];
  temp = F;

  // Since F[3] is only used in one line, I believe we don't even need a temp

  temp[3]  = F[0]*x + F[1]*y + F[2]*z + F[3];
  temp[7]  = F[4]*x + F[5]*y + F[6]*z + F[7];
  temp[11] = F[8]*x + F[9]*y + F[10]*z + F[11];

  F = temp;
}

void _3D_move( float F[], float G[] )
{
  // Perform inverse kinematics on
  // G.m from F.m to attain angles for motors necessary to end in G from F.

  return;
}

void _3D_Mult( float A[], float B[], float& C[] )
{
  C[0]  = A[0]*B[0] + A[1]*B[4] + A[2]*B[8];
  C[1]  = A[0]*B[1] + A[1]*B[5] + A[2]*B[9];
  C[2]  = A[0]*B[2] + A[1]*B[6] + A[2]*B[10];
  C[3]  = A[0]*B[3] + A[1]*B[7] + A[2]*B[11] + A[3];
  C[4]  = A[4]*B[0] + A[5]*B[4] + A[6]*B[8];
  C[5]  = A[4]*B[1] + A[5]*B[5] + A[6]*B[9];
  C[6]  = A[4]*B[2] + A[5]*B[6] + A[6]*B[10];
  C[7]  = A[4]*B[3] + A[5]*B[7] + A[6]*B[11] + A[7];
  C[8]  = A[8]*B[0] + A[9]*B[4] + A[10]*B[8];
  C[9]  = A[8]*B[1] + A[9]*B[5] + A[10]*B[9];
  C[10] = A[8]*B[2] + A[9]*B[6] + A[10]*B[10];
  C[11] = A[8]*B[3] + A[9]*B[7] + A[10]*B[11] + A[11];
}

void  _3D_set_rot_x( float& F[], float alpha )
{
  float sa = sin( alpha );
  float ca = cos( alpha );

  F[0]  = 1.0;
  F[1]  = 0.0;
  F[2]  = 0.0;
  F[4]  = 0.0;
  F[5]  = ca;
  F[6]  = -1.0 * sa;
  F[8]  = 0.0;
  F[9]  = sa;
  F[10] = ca;

  return;
}

void _3D_rot_x( float& F[], float alpha )
{
  float rot_x[12];
  float temp[12];
  // No need for ArrayInit call?
  
  _3D_set_rot_x( rot_x, alpha );

  _3D_Mult( F, rot_x, temp );
  
  _3D_Copy( F, temp );

  return;
}

#endif
