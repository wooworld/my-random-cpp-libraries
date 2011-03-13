#include "../../lib/numeric_types.h"
#include "_3x3Matrix.h"

#include <cstdio>
#include <cstdlib>

_3x3Matrix::_3x3Matrix()
{
  // Create 4 rows of 4 elements in a row in memory
  m_data = (sfloat32*)calloc( 9, sizeof(sfloat32) );
}

_3x3Matrix::_3x3Matrix( const _3x3Matrix& M )
{
  // Create 4 rows of 4 elements in a row in memory
  m_data = (sfloat32*)calloc( 9, sizeof(sfloat32) );
  
  m_data[0] = M.m_data[0];
  m_data[1] = M.m_data[1];
  m_data[2] = M.m_data[2];
  m_data[3] = M.m_data[3];
  m_data[4] = M.m_data[4];
  m_data[5] = M.m_data[5];
  m_data[6] = M.m_data[6];
  m_data[7] = M.m_data[7];
  m_data[8] = M.m_data[8];
}

void _3x3Matrix::set_all( const sfloat32& F )
{
  m_data[0] = F;
  m_data[1] = F;
  m_data[2] = F;
  m_data[3] = F;
  m_data[4] = F;
  m_data[5] = F;
  m_data[6] = F;
  m_data[7] = F;
  m_data[8] = F;
  
  return;
}

_3x3Matrix& _3x3Matrix::operator=( const _3x3Matrix& M )
{
  // Check for assignment against self
  if ( this == &M )
    return *this;
  
  m_data[0] = M.m_data[0];
  m_data[1] = M.m_data[1];
  m_data[2] = M.m_data[2];
  m_data[3] = M.m_data[3];
  m_data[4] = M.m_data[4];
  m_data[5] = M.m_data[5];
  m_data[6] = M.m_data[6];
  m_data[7] = M.m_data[7];
  m_data[8] = M.m_data[8];
  
  return *this;
}

_3x3Matrix _3x3Matrix::operator*( const _3x3Matrix& M )
{
  _3x3Matrix Temp;
  
  Temp[0] = m_data[0]*M.m_data[0] + m_data[1]*M.m_data[3] + m_data[2]*M.m_data[6];
  Temp[1] = m_data[0]*M.m_data[1] + m_data[1]*M.m_data[4] + m_data[2]*M.m_data[7];
  Temp[2] = m_data[0]*M.m_data[2] + m_data[1]*M.m_data[5] + m_data[2]*M.m_data[8];
  Temp[3] = m_data[3]*M.m_data[0] + m_data[4]*M.m_data[3] + m_data[5]*M.m_data[6];
  Temp[4] = m_data[3]*M.m_data[1] + m_data[4]*M.m_data[4] + m_data[5]*M.m_data[7];
  Temp[5] = m_data[3]*M.m_data[2] + m_data[4]*M.m_data[5] + m_data[5]*M.m_data[8];
  Temp[6] = m_data[6]*M.m_data[0] + m_data[7]*M.m_data[3] + m_data[8]*M.m_data[6];
  Temp[7] = m_data[6]*M.m_data[1] + m_data[7]*M.m_data[4] + m_data[8]*M.m_data[7];
  Temp[8] = m_data[6]*M.m_data[2] + m_data[7]*M.m_data[5] + m_data[8]*M.m_data[8];
  
  return Temp;
}

// _3x3Matrix& _3x3Matrix::operator*=( const _3x3Matrix& M )
// {
  // _3x3Matrix Temp;

  // Temp[0] = m_data[0]*M.m_data[0] + m_data[1]*M.m_data[3] + m_data[2]*M.m_data[6];
  // Temp[1] = m_data[0]*M.m_data[1] + m_data[1]*M.m_data[4] + m_data[2]*M.m_data[7];
  // Temp[2] = m_data[0]*M.m_data[2] + m_data[1]*M.m_data[5] + m_data[2]*M.m_data[8];
  // Temp[3] = m_data[3]*M.m_data[0] + m_data[4]*M.m_data[3] + m_data[5]*M.m_data[6];
  // Temp[4] = m_data[3]*M.m_data[1] + m_data[4]*M.m_data[4] + m_data[5]*M.m_data[7];
  // Temp[5] = m_data[3]*M.m_data[2] + m_data[4]*M.m_data[5] + m_data[5]*M.m_data[8];
  // Temp[6] = m_data[6]*M.m_data[0] + m_data[7]*M.m_data[3] + m_data[8]*M.m_data[6];
  // Temp[7] = m_data[6]*M.m_data[1] + m_data[7]*M.m_data[4] + m_data[8]*M.m_data[7];
  // Temp[6] = m_data[6]*M.m_data[2] + m_data[7]*M.m_data[5] + m_data[8]*M.m_data[8];
  
  // *this = Temp;
  
  // return *this;
// }

_3x3Matrix _3x3Matrix::operator+( const _3x3Matrix& M )
{
  _3x3Matrix Temp;
  
  Temp[0] = m_data[0] + M.m_data[0];
  Temp[1] = m_data[1] + M.m_data[1];
  Temp[2] = m_data[2] + M.m_data[2];
  Temp[3] = m_data[3] + M.m_data[3];
  Temp[4] = m_data[4] + M.m_data[4];
  Temp[5] = m_data[5] + M.m_data[5];
  Temp[6] = m_data[6] + M.m_data[6];
  Temp[7] = m_data[7] + M.m_data[7];
  Temp[8] = m_data[8] + M.m_data[8];
  
  return Temp;
}

_3x3Matrix _3x3Matrix::operator-( const _3x3Matrix& M )
{
  _3x3Matrix Temp;
  
  Temp[0] = m_data[0] - M.m_data[0];
  Temp[1] = m_data[1] - M.m_data[1];
  Temp[2] = m_data[2] - M.m_data[2];
  Temp[3] = m_data[3] - M.m_data[3];
  Temp[4] = m_data[4] - M.m_data[4];
  Temp[5] = m_data[5] - M.m_data[5];
  Temp[6] = m_data[6] - M.m_data[6];
  Temp[7] = m_data[7] - M.m_data[7];
  Temp[8] = m_data[8] - M.m_data[8];
  
  return Temp;
}

_3x3Matrix _3x3Matrix::operator!()
{
  _3x3Matrix Temp;
  
  // Temp[0] = m_data[0];
  Temp[1] = m_data[3];
  Temp[2] = m_data[6];
  Temp[3] = m_data[1];
  // Temp[4] = m_data[4];
  Temp[5] = m_data[7];
  Temp[6] = m_data[2];
  Temp[7] = m_data[5];
  // Temp[8] = m_data[8]; 
  
  return Temp;
}

const sfloat32& _3x3Matrix::operator[]( const uint32& i ) const
{
  // Assumes i = [0,15] 
  // Could do an if ( i > 15 ) check, but it's slower
  return m_data[i];
}

sfloat32& _3x3Matrix::operator[]( const uint32& i )
{
  return m_data[i];
}

void _3x3Matrix::scale( _3x3Matrix& M, const sfloat32& F )
{
  // Doesn't protect against overflow
  m_data[0] *= F;
  m_data[1] *= F;
  m_data[2] *= F;
  m_data[3] *= F;
  m_data[4] *= F;
  m_data[5] *= F;
  m_data[6] *= F;
  m_data[7] *= F;
  m_data[8] *= F;
  
  return;
}

void _3x3Matrix::print() const
{  
  for ( uint8 i = 0; i < 9; i++ )
  {
    printf( "% 10.3f ", m_data[i] );
    
    if ( (i+1) % 3 == 0 )
      printf( "\n" );
  }  

  printf( "\n" );

  return;
}
