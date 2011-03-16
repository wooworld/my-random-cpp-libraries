#ifndef _3DFRAME_H
#define _3DFRAME_H

#include "../../lib/numeric_types.h"
#include "../../lib/numeric_constants.h"
// #include "_4x4Matrix.h"
#include "_3x3Matrix.h"
#include "_3DPoint.h"
// #include "_4x4Matrix_Arbitrary_Rotation.h"
// #include "_4x4Matrix_Euler_Rotation.h"
#include <cstdio>


class _3DFrame
{
  public:
    _3DFrame();
    _3DFrame( const _3DFrame& F );
    ~_3DFrame();
    
    _3DFrame&   operator=( const _3DFrame& F );
    _3DFrame    operator*( const _3DFrame& F );
    
    _3x3Matrix  get_rotation_matrix();
    sfloat32*   get_translation_vector();
    
    void        set_rotation_matrix   ( const _3x3Matrix& M );
    void        set_translation_vector( const sfloat32 *F );
    
                             // trans x, trans y, trans z
    void        trans_curr  ( const sfloat32& a, const sfloat32& b, const sfloat32& c );
    void        trans_x_curr( const sfloat32& a );
    void        trans_y_curr( const sfloat32& b );
    void        trans_z_curr( const sfloat32& c );
    
    // void trans_world( const sfloat32& x, const sfloat32& y, const sfloat32& z );
    // void trans_x_world( const sfloat32& x );
    // void trans_y_world( const sfloat32& y );
    // void trans_z_world( const sfloat32& z );
    
                               // rotate x, rotate y, rotate z
    void arb_rot_curr_rad( const sfloat32& alpha, const sfloat32& beta, const sfloat32& gamma );
    void arb_rot_curr_deg( const sfloat32& alpha, const sfloat32& beta, const sfloat32& gamma );
                               // rotate z, rotate y, rotate z
    void euler_rot_curr_rad( const sfloat32& phi, const sfloat32& theta, const sfloat32& psi );
    void euler_rot_curr_deg( const sfloat32& phi, const sfloat32& theta, const sfloat32& psi );
    
    void print();
    void print_frame();
    void print_rot();
    void print_trans();
    
  protected:
    _3x3Matrix m_rot;
    _3Dpoint   m_loc;
};

#endif
