#include "../../lib/numeric_types.h"
#include "_3x3Matrix_Arbitrary_Rotation.h"

#include <cstdlib>
#include <cmath>

_3x3Matrix_Arbitrary_Rotation::_3x3Matrix_Arbitrary_Rotation
  (
    const sfloat32& alpha, 
    const sfloat32& beta, 
    const sfloat32& gamma
  )
{
  // Create 3 rows of 3 elements in a row in memory
  m_data = (sfloat32*)calloc( 9, sizeof(sfloat32) );
  
  sfloat32 ca = cos( alpha );
  sfloat32 cb = cos( beta );
  sfloat32 cg = cos( gamma );
  
  sfloat32 sa = sin( alpha );
  sfloat32 sb = sin( beta );
  sfloat32 sg = sin( gamma );

  m_data[0] = cb * cg;
  m_data[1] = sg * cb * -1;
  m_data[2] = sb;
  m_data[3] = cg * sa * sb + ca * sg;
  m_data[4] = sa * sb * sg * -1 + ca * cg;
  m_data[5] = cb * sa * -1;
  m_data[6] = ca * cg * sb * -1 + sa * sg;
  m_data[7] = ca * sb * sg + sa * cg;
  m_data[8] = ca * cb;
}
