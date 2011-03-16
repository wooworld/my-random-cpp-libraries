#include "_3DFrame.h"

_3DFrame::_3DFrame()
{
  m_trans = (sfloat32*)calloc( 3, sizeof(sfloat32) );
  
  m_frame[0]  = 1.0;
  m_frame[5]  = 1.0;
  m_frame[10] = 1.0;
  m_frame[15] = 1.0;
}

_3DFrame::_3DFrame( const _3DFrame& M )
{
  m_trans = (sfloat32*)calloc( 3, sizeof(sfloat32) );
  memcpy( m_trans, M.m_trans, 3 * sizeof(sfloat32) );
  
  m_frame = M.m_frame;
  m_rot   = M.m_rot;
}

_3DFrame::~_3DFrame()
{

}

_3DFrame& _3DFrame::operator=( const _3DFrame& M )
{
  // Check for assignment against self
  if ( this == &M )
    return *this;
  
  m_frame = M.m_frame;
  m_rot   = M.m_rot;
  memcpy( m_trans, M.m_trans, 3 * sizeof(sfloat32) );
  
  return *this;
}

_3DFrame _3DFrame::operator*( const _3DFrame& F )
{
  _3DFrame Temp;
  
  Temp.m_frame = (m_frame * F.m_frame);
  
  return Temp;
}

_3x3Matrix _3DFrame::get_rotation_matrix()
{
  // Build the 3x3 rotation matrix
  m_rot[0] = m_frame[0];
  m_rot[1] = m_frame[1];
  m_rot[2] = m_frame[2];
  m_rot[3] = m_frame[4];
  m_rot[4] = m_frame[5];
  m_rot[5] = m_frame[6];
  m_rot[6] = m_frame[8];
  m_rot[7] = m_frame[9];
  m_rot[8] = m_frame[10];
  
  return m_rot;
}

sfloat32* _3DFrame::get_translation_vector()
{
  // Build the 3x1 translation vector
  m_trans[0] = m_frame[3];
  m_trans[1] = m_frame[7];
  m_trans[2] = m_frame[11];
  
  return m_trans;
}

void _3DFrame::set_rotation_matrix( const _3x3Matrix& M ) 
{
  m_frame[0]  = M[0];
  m_frame[1]  = M[1];
  m_frame[2]  = M[2];
  m_frame[4]  = M[3];
  m_frame[5]  = M[4];
  m_frame[6]  = M[5];
  m_frame[8]  = M[6];
  m_frame[9]  = M[7];
  m_frame[10] = M[8];

  return;
}

void _3DFrame::set_translation_vector( const sfloat32 *F )
{
  memcpy( m_trans, F, 3 * sizeof(sfloat32) );

  return;
}

void _3DFrame::trans_curr( const sfloat32& a, const sfloat32& b, const sfloat32& c )
{
  m_frame[3]  += (m_frame[0]*a + m_frame[1]*b + m_frame[2]*c);
  m_frame[7]  += (m_frame[4]*a + m_frame[5]*b + m_frame[6]*c);
  m_frame[11] += (m_frame[8]*a + m_frame[9]*b + m_frame[10]*c);
  
  return;
}

void _3DFrame::trans_x_curr( const sfloat32& a )
{
  m_frame[3]  += (m_frame[0]*a);
  m_frame[7]  += (m_frame[4]*a);
  m_frame[11] += (m_frame[8]*a);
  
  return;
}

void _3DFrame::trans_y_curr( const sfloat32& b )
{
  m_frame[3]  += (m_frame[1]*b);
  m_frame[7]  += (m_frame[5]*b);
  m_frame[11] += (m_frame[9]*b);
  
  return;
}

void _3DFrame::trans_z_curr( const sfloat32& c )
{
  m_frame[3]  += (m_frame[2]*c);
  m_frame[7]  += (m_frame[6]*c);
  m_frame[11] += (m_frame[10]*c);
  
  return;
}

void _3DFrame::arb_rot_curr_rad( const sfloat32& alpha, const sfloat32& beta, const sfloat32& gamma )
{
  _4x4Matrix_Arbitrary_Rotation R( alpha, beta, gamma );

  m_frame = m_frame * R;

  return;
}

void _3DFrame::arb_rot_curr_deg( const sfloat32& alpha, const sfloat32& beta, const sfloat32& gamma )
{
  _4x4Matrix_Arbitrary_Rotation R( alpha*_RAD_PER_DEG, beta*_RAD_PER_DEG, gamma*_RAD_PER_DEG );

  m_frame = m_frame * R;

  return;
}

void _3DFrame::euler_rot_curr_rad( const sfloat32& phi, const sfloat32& theta, const sfloat32& psi )
{
  _4x4Matrix_Euler_Rotation R( phi, theta, psi );

  m_frame = m_frame * R;

  return;
}

void _3DFrame::euler_rot_curr_deg( const sfloat32& phi, const sfloat32& theta, const sfloat32& psi )
{
  _4x4Matrix_Euler_Rotation R( phi*_RAD_PER_DEG, theta*_RAD_PER_DEG, psi*_RAD_PER_DEG );

  m_frame = m_frame * R;

  return;
}

void _3DFrame::print()
{
  print_frame();
  
  return;
}

void _3DFrame::print_frame()
{
  m_frame.print();
  
  return;
}

void _3DFrame::print_rot()
{
  m_rot.print();
}

void _3DFrame::print_trans()
{
  printf( "% 10.3f\n", m_trans[0] );
  printf( "% 10.3f\n", m_trans[1] );
  printf( "% 10.3f\n", m_trans[2] );
  printf( "\n" );
  
  return;
}