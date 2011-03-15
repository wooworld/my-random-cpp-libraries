#include "_4x4Matrix_Euler_Rotation.h"

_4x4Matrix_Euler_Rotation::_4x4Matrix_Euler_Rotation
  (
    const sfloat32& phi, 
    const sfloat32& theta, 
    const sfloat32& psi
  )
{
  m_data = (sfloat32*)calloc( 16, sizeof(sfloat32) );
  
  sfloat32 cphi = cos( phi );
  sfloat32 ctheta = cos( theta );
  sfloat32 cpsi = cos( psi );
  
  sfloat32 sphi = sin( phi );
  sfloat32 stheta = sin( theta );
  sfloat32 spsi = sin( psi );

  m_data[0]  = cphi * ctheta * cpsi - sphi * spsi ;
  m_data[1]  = -1.0 * cphi * ctheta * cpsi - sphi * cpsi;
  m_data[2]  = cphi * stheta;
  m_data[4]  = sphi * ctheta * cpsi + cphi * spsi;
  m_data[5]  = -1.0 * sphi * ctheta * spsi + cphi * cpsi;
  m_data[6]  = sphi * stheta;
  m_data[8]  = -1.0 * stheta * cpsi;
  m_data[9]  = stheta * spsi;
  m_data[10] = ctheta;
  m_data[15] = 1.0;
}
