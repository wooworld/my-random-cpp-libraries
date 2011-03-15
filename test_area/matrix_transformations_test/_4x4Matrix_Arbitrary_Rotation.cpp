#include "_4x4Matrix_Arbitrary_Rotation.h"

_4x4Matrix_Arbitrary_Rotation::_4x4Matrix_Arbitrary_Rotation
  (
    const sfloat32& alpha, 
    const sfloat32& beta, 
    const sfloat32& gamma
  )
{
  m_data = (sfloat32*)calloc( 16, sizeof(sfloat32) );
  
  sfloat32 ca = cos( alpha );
  sfloat32 cb = cos( beta );
  sfloat32 cg = cos( gamma );
  
  sfloat32 sa = sin( alpha );
  sfloat32 sb = sin( beta );
  sfloat32 sg = sin( gamma );

  m_data[0]  = cb * cg;
  m_data[1]  = -1.0 * cb * sg;
  m_data[2]  = sb;
  m_data[4]  = cg * sa * sb + ca * sg;
  m_data[5]  = -1.0 * sa * sb * sg + ca * cg;
  m_data[6]  = -1.0 * cb * sa;
  m_data[8]  = -1.0 * ca * cg * sb + sa * sg;
  m_data[9]  = ca * sb * sg + sa * cg;
  m_data[10] = ca * cb;
  m_data[15] = 1.0;
}
