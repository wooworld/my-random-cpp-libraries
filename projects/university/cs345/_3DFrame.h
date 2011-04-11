/*
  @file _3DFrame.h
  @auth Gary Steelman
  @desc The structure declaration and function prototypes for a 3D Frame
    to be used with the Lego Mindstorm NXT 2.0 kit.
  @edit 09 Apr 2011
*/

/*
  @fn     void _3D_Init( _3DFrame& F )
  @desc   Initializes a _3DFrame object with an identity matrix for its rotation.
  @pre    F exists.
  @param  _3DFrame& F -- the _3DFrame to initialize.
  @post   F is now useable as a _3DFrame.
  @note   This must be called after creating a _3DFrame object to make it useful.

  
  @fn     void _3D_Destroy( _3DFrame& F )
  @desc   Destroys a _3DFrame object. 
  @pre    F has been initialized using _3D_Init().
  @param  _3DFrame& F -- the _3DFrame to destroy.
  @post   Memory in use by F is freed.

  
  @fn     void _3D_Copy( _3DFrame& A, const _3DFrame& B )
  @desc   Copies B into A.
  @pre    A has been initialized using _3D_Init().
  @pre    B has been initialized using _3D_Init().
  @param  _3DFrame& A -- the frame to copy into.
  @param  _3DFrame& B -- the frame to copy from.
  @post   Copies all entries in B to A.

  
  @fn     void _3D_Print( const _3DFrame& F )
  @desc   Prints F to the NXT brick LCD screen.
  @pre    F has been initialized using _3D_Init().
  @param  _3DFrame& F -- the _3DFrame to output to the LCD screen.
  @post   Outputs F's entries in a 3x4 fashion to the NXT's LCD screen.

  
  @fn     _3DFrame _3D_Mult( const _3DFrame& A, const _3DFrame& B )
  @desc   Multiplies A by B and returns the result; eg return (A * B)
  @pre    A has been initialized using _3D_Init().
  @pre    B has been initialized using _3D_Init().
  @param  _3DFrame& A -- the left hand side to multiply by.
  @param  _3DFrame& B -- the right hand side to multiply by.
  @rtn    _3DFrame -- the result of the multiplication A*B.
  @post   Multiplies A by B and returns the result.

  
  @fn     void _3D_set_rot_x( _3DFrame& F, float alpha )
  @desc   Sets F to be the frame for rotating about the current X axis by alpha.
  @pre    F has been initialized using _3D_Init().
  @pre    alpha is a rotation value in radians.
  @param  _3DFrame& F -- the _3DFrame to set the rotation matrix to of.
  @param  float alpha -- the magnitude of the rotation in radians. 
  @post   Sets F to be a rotation about the current X axist by an angle alpha.

  
  @fn     void _3D_set_rot_y( _3DFrame& F, float beta )
  @desc   Sets F to be the frame for rotating about the current Y axis by beta.
  @pre    F has been initialized using _3D_Init().
  @pre    beta is a rotation value in radians.
  @param  _3DFrame& F -- the _3DFrame to set the rotation matrix to of.
  @param  float beta -- the magnitude of the rotation in radians. 
  @post   Sets F to be a rotation about the current Y axist by an angle beta.

  
  @fn     void _3D_set_rot_z( _3DFrame& F, float gamma )
  @desc   Sets F to be the frame for rotating about the current Z axis by gamma.
  @pre    F has been initialized using _3D_Init().
  @pre    gamma is a rotation value in radians.
  @param  _3DFrame& F -- the _3DFrame to set the rotation matrix to of.
  @param  float gamma -- the magnitude of the rotation in radians. 
  @post   Sets F to be a rotation about the current Z axist by an angle gamma.

  
  @fn     void _3D_set_x( _3DFrame& F, float x )
  @desc   Sets F's X axis position to x.
  @pre    F has been initialized using _3D_Init().
  @pre    x is a real number.
  @param  _3DFrame& F -- the _3DFrame to set the X component of.
  @param  float x -- the value to relocate the frame to.
  @post   Sets F's X axis position to x.

  
  @fn     void _3D_set_y( _3DFrame& F, float y )
  @desc   Sets F's Y axis position to y.
  @pre    F has been initialized using _3D_Init().
  @pre    y is a real number.
  @param  _3DFrame& F -- the _3DFrame to set the Y component of.
  @param  float y -- the value to relocate the frame to.
  @post   Sets F's Y axis position to y.

  
  @fn     void _3D_set_z( _3DFrame& F, float Z )
  @desc   Sets F's Z axis position to z.
  @pre    F has been initialized using _3D_Init().
  @pre    z is a real number.
  @param  _3DFrame& F -- the _3DFrame to set the Z component of.
  @param  float z -- the value to relocate the frame to.
  @post   Sets F's Z axis position to z.

  
  @fn     void _3D_set_loc( _3DFrame& F, float x, float y, float z )
  @desc   Sets F's X axis position to x, Y axis position to y, and Z axis 
            position to z.
  @pre    F has been initialized using _3D_Init().
  @pre    x is a real number.
  @pre    y is a real number.
  @pre    z is a real number.
  @param  _3DFrame& F -- the _3DFrame to set the x, y, and z components of.
  @param  float x -- the x value to relocate the frame to.
  @param  float y -- the y value to relocate the frame to.
  @param  float z -- the z value to relocate the frame to.
  @post   Sets F's X, Y, and Z axis positions to x, y, z.
  @note   This is NOT translation! This is a direct relocation! This /can/ and
            probably will break the math and orientation of the frame!

            
  @fn     _3DFrame _3D_rot_x( const _3DFrame& F, float alpha )
  @desc   Returns the rotation of F about its current X axis by alpha radians.
  @pre    F has been initialized using _3D_Init().
  @pre    alpha is a real number in radians.
  @param  const _3DFrame& F -- the _3DFrame to rotate.
  @param  float alpha -- the value to rotate the frame by.
  @rtn    _3DFrame& F -- The result of the rotation.
  @post   Returns the rotation of F about its current X axis by alpha radians.

  
  @fn     _3DFrame _3D_rot_y( const _3DFrame& F, float beta )
  @desc   Returns the rotation of F about its current Y axis by beta radians.
  @pre    F has been initialized using _3D_Init().
  @pre    beta is a real number in radians.
  @param  const _3DFrame& F -- the _3DFrame to rotate.
  @param  float beta -- the value to rotate the frame by.
  @rtn    _3DFrame& F -- The result of the rotation.
  @post   Returns the rotation of F about its current Y axis by beta radians.

  
  @fn     _3DFrame _3D_rot_z( const _3DFrame& F, float gamma )
  @desc   Returns the rotation of F about its current Z axis by gamma radians.
  @pre    F has been initialized using _3D_Init().
  @pre    gamma is a real number in radians.
  @param  const _3DFrame& F -- the _3DFrame to rotate.
  @param  float gamma -- the value to rotate the frame by.
  @rtn    _3DFrame& F -- The result of the rotation.
  @post   Returns the rotation of F about its current Z axis by gamma radians.

  
  @fn     _3DFrame _3D_translate ( const _3DFrame& F, float x, float y, float z )
  @desc   Returns the translation of F along its X, Y, and Z axes by x, y, and z.
  @pre    F has been initialized using _3D_Init().
  @pre    x is a real number.
  @pre    y is a real number.
  @pre    z is a real number.
  @param  const _3DFrame& F -- the _3DFrame to translate by x, y, z.
  @param  float x -- the x value to translate along F's X axis.
  @param  float y -- the y value to translate along F's Y axis.
  @param  float z -- the z value to translate along F's Z axis.
  @rtn    _3DFrame& F -- The result of the translation.
  @post   Returns the translation of F along its X, Y, and Z axes by x, y, and z.

  
  @fn     void _3D_clear_rot( _3DFrame& F )
  @desc   Sets the rotation matrix of F to 0.0.
  @pre    F has been initialized using _3D_Init().
  @param  _3DFrame& F -- the _3DFrame to clear the rotation matrix from.
  @post   Sets the rotation matrix of F to 0.0.

  
  @fn     void _3D_reset_rot( _3DFrame& F )
  @desc   Sets the rotation matrix of F to the identity (congruent to world frame).
  @pre    F has been initialized using _3D_Init().
  @param  _3DFrame& F -- the _3DFrame to reset the rotation matrix of. 
  @post   Sets the rotation matrix of F to the identity (congruent to world frame).

  
  @fn     void _3D_clear_loc( _3DFrame& F );
  @desc   Sets the location vector of F to 0.0.
  @pre    F has been initialized using _3D_Init().
  @param  _3DFrame& F -- the _3DFrame to clear the location vector from.
  @post   Sets the location vector of F to 0.0.
*/

#ifndef _3DFRAMEH
#define _3DFRAMEH

#include "NXCDefs.h"

typedef struct
{
  float m[12];
} _3DFrame;

// Due to current BricxCC implementation this is necessary
float _3D_INIT_ARRAY[] = {1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0};

void     _3D_Init        ( _3DFrame& F );
void     _3D_Destroy     ( _3DFrame& F );
void     _3D_Copy        ( _3DFrame& A, const _3DFrame& B );
void     _3D_Print       ( const _3DFrame& F );
void     _3D_Print_Upper ( const _3DFrame& F );
void     _3D_Print_Lower ( const _3DFrame& F );

_3DFrame _3D_Mult        ( const _3DFrame& A, const _3DFrame& B );

void     _3D_set_rot_x   ( _3DFrame& F, float alpha );
void     _3D_set_rot_y   ( _3DFrame& F, float beta  );
void     _3D_set_rot_z   ( _3DFrame& F, float gamma );

void     _3D_set_x       ( _3DFrame& F, float x );
void     _3D_set_y       ( _3DFrame& F, float y );
void     _3D_set_z       ( _3DFrame& F, float z );
void     _3D_set_loc     ( _3DFrame& F, float x, float y, float z );

_3DFrame _3D_rot_x       ( const _3DFrame& F, float alpha );
_3DFrame _3D_rot_y       ( const _3DFrame& F, float beta );
_3DFrame _3D_rot_z       ( const _3DFrame& F, float gamma );
_3DFrame _3D_translate   ( const _3DFrame& F, float x, float y, float z );

void     _3D_move        ( const _3DFrame& F, const _3DFrame& G );

void     _3D_clear_rot   ( _3DFrame& F );
void     _3D_clear_loc   ( _3DFrame& F );

safecall void _3D_Init( _3DFrame& F )
{
  F.m = _3D_INIT_ARRAY;

  return;
}

safecall void _3D_Destroy( _3DFrame& F )
{
}

safecall void _3D_Copy( _3DFrame& A, const _3DFrame& B )
{
  A.m = B.m;

  return;
}

void _3D_Print( const _3DFrame& F )
{
  // For each column of the matrix
  for ( int i = 0; i < 4; i++ )
  {
    // For each row of the matrix
    for ( int j = 0; j < 3; j++ )
    {
       // Each character is 5 px wide, +1 space between chars
       TextOut( i*24, LCD_LINE1-8*j, FormatNum( "%4.1f", F.m[(j*4) + i] ) );
    }
  }
}

void _3D_Print_Upper( const _3DFrame& F )
{
  // For each column of the matrix
  for ( int i = 0; i < 4; i++ )
  {
    // For each row of the matrix
    for ( int j = 0; j < 3; j++ )
    {
       // Each character is 5 px wide, +1 space between chars
       TextOut( i*24, LCD_LINE1-8*j, FormatNum( "%4.1f", F.m[(j*4) + i] ) );
    }
  }
}

void _3D_Print_Lower( const _3DFrame& F )
{
  // For each column of the matrix
  for ( int i = 0; i < 4; i++ )
  {
    // For each row of the matrix
    for ( int j = 0; j < 3; j++ )
    {
       // Each character is 5 px wide, +1 space between chars
       TextOut( i*24, LCD_LINE5-8*j, FormatNum( "%4.1f", F.m[(j*4) + i] ) );
    }
  }
}

_3DFrame _3D_Mult( const _3DFrame& A, const _3DFrame& B )
{
  _3DFrame temp;
  ArrayInit( temp.m, 0.0, 12 );
  
  temp.m[0]  = A.m[0]*B.m[0] + A.m[1]*B.m[4] + A.m[2]*B.m[8];
  temp.m[1]  = A.m[0]*B.m[1] + A.m[1]*B.m[5] + A.m[2]*B.m[9];
  temp.m[2]  = A.m[0]*B.m[2] + A.m[1]*B.m[6] + A.m[2]*B.m[10];
  temp.m[3]  = A.m[0]*B.m[3] + A.m[1]*B.m[7] + A.m[2]*B.m[11] + A.m[3];
  temp.m[4]  = A.m[4]*B.m[0] + A.m[5]*B.m[4] + A.m[6]*B.m[8];
  temp.m[5]  = A.m[4]*B.m[1] + A.m[5]*B.m[5] + A.m[6]*B.m[9];
  temp.m[6]  = A.m[4]*B.m[2] + A.m[5]*B.m[6] + A.m[6]*B.m[10];
  temp.m[7]  = A.m[4]*B.m[3] + A.m[5]*B.m[7] + A.m[6]*B.m[11] + A.m[7];
  temp.m[8]  = A.m[8]*B.m[0] + A.m[9]*B.m[4] + A.m[10]*B.m[8];
  temp.m[9]  = A.m[8]*B.m[1] + A.m[9]*B.m[5] + A.m[10]*B.m[9];
  temp.m[10] = A.m[8]*B.m[2] + A.m[9]*B.m[6] + A.m[10]*B.m[10];
  temp.m[11] = A.m[8]*B.m[3] + A.m[9]*B.m[7] + A.m[10]*B.m[11] + A.m[11];

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

_3DFrame _3D_rot_x( const _3DFrame& F, float alpha )
{
  _3DFrame temp;

  ArrayInit( temp.m, 0.0, 12 );

  _3D_set_rot_x( temp, alpha );

  //_3D_Copy( temp, _3D_Mult( temp, F ) );
  _3D_Copy( temp, _3D_Mult( F, temp ) );

  return temp;
}

_3DFrame _3D_rot_y( const _3DFrame& F, float beta )
{
  _3DFrame temp;
  temp.m = _3D_INIT_ARRAY;
  //ArrayInit( temp.m, 0.0, 12 );

  _3D_set_rot_y( temp, beta );

  return _3D_Mult( temp, F );
}

_3DFrame _3D_rot_z( const _3DFrame& F, float gamma )
{
  _3DFrame temp;
  temp.m = _3D_INIT_ARRAY;
  //ArrayInit( temp.m, 0.0, 12 );

  _3D_set_rot_z( temp, gamma );

  return _3D_Mult( temp, F );
}

_3DFrame _3D_translate( const _3DFrame& F, float x, float y, float z )
{
  _3DFrame temp;
  temp.m = F.m;

  temp.m[3]  = F.m[0]*x + F.m[1]*y + F.m[2]*z + F.m[3];
  temp.m[7]  = F.m[4]*x + F.m[5]*y + F.m[6]*z + F.m[7];
  temp.m[11] = F.m[8]*x + F.m[9]*y + F.m[10]*z + F.m[11];

  return temp;
}

void _3D_move( const _3DFrame& F, const _3DFrame& G )
{
  // Perform inverse kinematics on
  // G.m from F.m to attain angles for motors necessary to end in G from F.

  return;
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

safecall void _3D_reset_rot( _3DFrame& F )
{
  F.m[0]  = 1.0;
  F.m[1]  = 0.0;
  F.m[2]  = 0.0;
  F.m[4]  = 0.0;
  F.m[5]  = 1.0;
  F.m[6]  = 0.0;
  F.m[8]  = 0.0;
  F.m[9]  = 0.0;
  F.m[10] = 1.0;

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
