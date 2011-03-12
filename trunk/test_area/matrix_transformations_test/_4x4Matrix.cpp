#include "numeric_types.h"
#include <cstdio>

_4x4Matrix::_4x4Matrix()
{
  // Create 4 rows of 4 elements in a row in memory
  m_data = (sfloat32*)calloc( 16, sizeof(sfloat32) )
}

_4x4Matrix::_4x4Matrix( const _4x4Matrix& M )
{
  // Create 4 rows of 4 elements in a row in memory
  m_data = (sfloat32*)calloc( 16, sizeof(sfloat32) )
  
  m_data[0]  = M.m_data[0];
  m_data[1]  = M.m_data[1];
  m_data[2]  = M.m_data[2];
  m_data[3]  = M.m_data[3];
  m_data[4]  = M.m_data[4];
  m_data[5]  = M.m_data[5];
  m_data[6]  = M.m_data[6];
  m_data[7]  = M.m_data[7];
  m_data[8]  = M.m_data[8];
  m_data[9]  = M.m_data[9];
  m_data[10] = M.m_data[10];
  m_data[11] = M.m_data[11];
  m_data[12] = M.m_data[12];
  m_data[13] = M.m_data[13];
  m_data[14] = M.m_data[14];
  m_data[15] = M.m_data[15];
}

void _4x4Matrix::set_all( const sfloat32& F )
{
  m_data[0]  = F;
  m_data[1]  = F;
  m_data[2]  = F;
  m_data[3]  = F;
  m_data[4]  = F;
  m_data[5]  = F;
  m_data[6]  = F;
  m_data[7]  = F;
  m_data[8]  = F;
  m_data[9]  = F;
  m_data[10] = F;
  m_data[11] = F;
  m_data[12] = F;
  m_data[13] = F;
  m_data[14] = F;
  m_data[15] = F;
  
  return;
}

_4x4Matrix& _4x4Matrix::operator=( const _4x4Matrix& M )
{
  // Check for assignment against self
  if ( this == &rhs )
    return *this;
  
  m_data[0]  = M.m_data[0];
  m_data[1]  = M.m_data[1];
  m_data[2]  = M.m_data[2];
  m_data[3]  = M.m_data[3];
  m_data[4]  = M.m_data[4];
  m_data[5]  = M.m_data[5];
  m_data[6]  = M.m_data[6];
  m_data[7]  = M.m_data[7];
  m_data[8]  = M.m_data[8];
  m_data[9]  = M.m_data[9];
  m_data[10] = M.m_data[10];
  m_data[11] = M.m_data[11];
  m_data[12] = M.m_data[12];
  m_data[13] = M.m_data[13];
  m_data[14] = M.m_data[14];
  m_data[15] = M.m_data[15];
  
  return *this;
}

_4x4Matrix _4x4Matrix::operator*( const _4x4Matrix& M )
{
  _4x4Matrix Temp;
  
  // Hardcoded for SPEEEEEEEEEEEEED 8D~!
  // Could be accomplised with nested for loops, but that requires an extra
  //    boolean expression evaluation each loop
  Temp[0]  = m_data[0]*M.m_data[0]  + m_data[1]*M.m_data[4]  + m_data[2]*M.m_data[8]   + m_data[3]*M.m_data[12];
  Temp[1]  = m_data[0]*M.m_data[1]  + m_data[1]*M.m_data[5]  + m_data[2]*M.m_data[9]   + m_data[3]*M.m_data[13];
  Temp[2]  = m_data[0]*M.m_data[2]  + m_data[1]*M.m_data[6]  + m_data[2]*M.m_data[10]  + m_data[3]*M.m_data[14];
  Temp[3]  = m_data[0]*M.m_data[3]  + m_data[1]*M.m_data[7]  + m_data[2]*M.m_data[11]  + m_data[3]*M.m_data[15];
  Temp[4]  = m_data[4]*M.m_data[0]  + m_data[5]*M.m_data[4]  + m_data[6]*M.m_data[8]   + m_data[7]*M.m_data[12];
  Temp[5]  = m_data[4]*M.m_data[1]  + m_data[5]*M.m_data[5]  + m_data[6]*M.m_data[9]   + m_data[7]*M.m_data[13];
  Temp[6]  = m_data[4]*M.m_data[2]  + m_data[5]*M.m_data[6]  + m_data[6]*M.m_data[10]  + m_data[7]*M.m_data[14];
  Temp[7]  = m_data[4]*M.m_data[3]  + m_data[5]*M.m_data[7]  + m_data[6]*M.m_data[11]  + m_data[7]*M.m_data[15];
  Temp[8]  = m_data[8]*M.m_data[0]  + m_data[9]*M.m_data[4]  + m_data[10]*M.m_data[8]  + m_data[11]*M.m_data[12];
  Temp[9]  = m_data[8]*M.m_data[1]  + m_data[9]*M.m_data[5]  + m_data[10]*M.m_data[9]  + m_data[11]*M.m_data[13];
  Temp[10] = m_data[8]*M.m_data[2]  + m_data[9]*M.m_data[6]  + m_data[10]*M.m_data[10] + m_data[11]*M.m_data[14];
  Temp[11] = m_data[8]*M.m_data[3]  + m_data[9]*M.m_data[7]  + m_data[10]*M.m_data[11] + m_data[11]*M.m_data[15];
  Temp[12] = m_data[12]*M.m_data[0] + m_data[13]*M.m_data[4] + m_data[14]*M.m_data[8]  + m_data[15]*M.m_data[12];
  Temp[13] = m_data[12]*M.m_data[1] + m_data[13]*M.m_data[5] + m_data[14]*M.m_data[9]  + m_data[15]*M.m_data[13];
  Temp[14] = m_data[12]*M.m_data[2] + m_data[13]*M.m_data[6] + m_data[14]*M.m_data[10] + m_data[15]*M.m_data[14];
  Temp[15] = m_data[12]*M.m_data[3] + m_data[13]*M.m_data[7] + m_data[14]*M.m_data[11] + m_data[15]*M.m_data[15];
  
  return Temp;
}

// _4x4Matrix& _4x4Matrix::operator*=( const _4x4Matrix& M )
// {
  // _4x4Matrix Temp;

  // Temp[0] = m_data[0]*M.m_data[0]   + m_data[1]*M.m_data[4]  + m_data[2]*M.m_data[8]   + m_data[3]*M.m_data[12];
  // Temp[1] = m_data[0]*M.m_data[1]   + m_data[1]*M.m_data[5]  + m_data[2]*M.m_data[9]   + m_data[3]*M.m_data[13];
  // Temp[2] = m_data[0]*M.m_data[2]   + m_data[1]*M.m_data[6]  + m_data[2]*M.m_data[10]  + m_data[3]*M.m_data[14];
  // Temp[3] = m_data[0]*M.m_data[3]   + m_data[1]*M.m_data[7]  + m_data[2]*M.m_data[11]  + m_data[3]*M.m_data[15];
  // Temp[4] = m_data[4]*M.m_data[0]   + m_data[5]*M.m_data[4]  + m_data[6]*M.m_data[8]   + m_data[7]*M.m_data[12];
  // Temp[5] = m_data[4]*M.m_data[1]   + m_data[5]*M.m_data[5]  + m_data[6]*M.m_data[9]   + m_data[7]*M.m_data[13];
  // Temp[6] = m_data[4]*M.m_data[2]   + m_data[5]*M.m_data[6]  + m_data[6]*M.m_data[10]  + m_data[7]*M.m_data[14];
  // Temp[7] = m_data[4]*M.m_data[3]   + m_data[5]*M.m_data[7]  + m_data[6]*M.m_data[11]  + m_data[7]*M.m_data[15];
  // Temp[8] = m_data[8]*M.m_data[0]   + m_data[9]*M.m_data[4]  + m_data[10]*M.m_data[8]  + m_data[11]*M.m_data[12];
  // Temp[9] = m_data[8]*M.m_data[1]   + m_data[9]*M.m_data[5]  + m_data[10]*M.m_data[9]  + m_data[11]*M.m_data[13];
  // Temp[10] = m_data[8]*M.m_data[2]  + m_data[9]*M.m_data[6]  + m_data[10]*M.m_data[10] + m_data[11]*M.m_data[14];
  // Temp[11] = m_data[8]*M.m_data[3]  + m_data[9]*M.m_data[7]  + m_data[10]*M.m_data[11] + m_data[11]*M.m_data[15];
  // Temp[12] = m_data[12]*M.m_data[0] + m_data[13]*M.m_data[4] + m_data[14]*M.m_data[8]  + m_data[15]*M.m_data[12];
  // Temp[13] = m_data[12]*M.m_data[1] + m_data[13]*M.m_data[5] + m_data[14]*M.m_data[9]  + m_data[15]*M.m_data[13];
  // Temp[14] = m_data[12]*M.m_data[2] + m_data[13]*M.m_data[6] + m_data[14]*M.m_data[10] + m_data[15]*M.m_data[14];
  // Temp[15] = m_data[12]*M.m_data[3] + m_data[13]*M.m_data[7] + m_data[14]*M.m_data[11] + m_data[15]*M.m_data[15];
  
  // *this = Temp;
  
  // return *this;
// }

_4x4Matrix _4x4Matrix::operator+( const _4x4Matrix& M )
{
  _4x4Matrix Temp;
  
  Temp[0]  = m_data[0]  + M.m_data[0];
  Temp[1]  = m_data[1]  + M.m_data[1];
  Temp[2]  = m_data[2]  + M.m_data[2];
  Temp[3]  = m_data[3]  + M.m_data[3];
  Temp[4]  = m_data[4]  + M.m_data[4];
  Temp[5]  = m_data[5]  + M.m_data[5];
  Temp[6]  = m_data[6]  + M.m_data[6];
  Temp[7]  = m_data[7]  + M.m_data[7];
  Temp[8]  = m_data[8]  + M.m_data[8];
  Temp[9]  = m_data[9]  + M.m_data[9];
  Temp[10] = m_data[10] + M.m_data[10];
  Temp[11] = m_data[11] + M.m_data[11];
  Temp[12] = m_data[12] + M.m_data[12];
  Temp[13] = m_data[13] + M.m_data[13];
  Temp[14] = m_data[14] + M.m_data[14];
  Temp[15] = m_data[15] + M.m_data[15];
  
  return Temp;
}

_4x4Matrix _4x4Matrix::operator-( const _4x4Matrix& M )
{
  _4x4Matrix Temp;
  
  Temp[0]  = m_data[0]  - M.m_data[0];
  Temp[1]  = m_data[1]  - M.m_data[1];
  Temp[2]  = m_data[2]  - M.m_data[2];
  Temp[3]  = m_data[3]  - M.m_data[3];
  Temp[4]  = m_data[4]  - M.m_data[4];
  Temp[5]  = m_data[5]  - M.m_data[5];
  Temp[6]  = m_data[6]  - M.m_data[6];
  Temp[7]  = m_data[7]  - M.m_data[7];
  Temp[8]  = m_data[8]  - M.m_data[8];
  Temp[9]  = m_data[9]  - M.m_data[9];
  Temp[10] = m_data[10] - M.m_data[10];
  Temp[11] = m_data[11] - M.m_data[11];
  Temp[12] = m_data[12] - M.m_data[12];
  Temp[13] = m_data[13] - M.m_data[13];
  Temp[14] = m_data[14] - M.m_data[14];
  Temp[15] = m_data[15] - M.m_data[15];
  
  return Temp;
}

const sfloat32& _4x4Matrix::operator[]( const uint32& i ) const
{
  // Assumes i = [0,15] 
  // Could do an if ( i > 15 ) check, but it's slower
  return m_data[i];
}

sfloat32& _4x4Matrix::operator[]( const uint32& i )
{
  return m_data[i];
}

void _4x4Matrix::scale( _4x4Matrix& M, const sfloat32& F )
{
  // Doesn't protect against overflow
  m_data[0]  *= F;
  m_data[1]  *= F;
  m_data[2]  *= F;
  m_data[3]  *= F;
  m_data[4]  *= F;
  m_data[5]  *= F;
  m_data[6]  *= F;
  m_data[7]  *= F;
  m_data[8]  *= F;
  m_data[9]  *= F;
  m_data[10] *= F;
  m_data[11] *= F;
  m_data[12] *= F;
  m_data[13] *= F;
  m_data[14] *= F;
  m_data[15] *= F;
  
  return;
}

void _4x4Matrix::print() const
{
  for ( uint8 i = 0; i < 4; i++ )
  {
    for ( uint8 j = 0; j < 4; j++ )
    {
      printf( "%6.2f", m_data[i+j] );
    }
    
    printf( "\n" );
  }    

  return;
}
