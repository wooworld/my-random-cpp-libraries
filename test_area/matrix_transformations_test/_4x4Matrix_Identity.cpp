#include "../../lib/numeric_types.h"
#include "_4x4Matrix_Identity.h"

#include <cstdlib>

_4x4Matrix_Identity::_4x4Matrix_Identity()
{
  // Create 4 rows of 4 elements in a row in memory
  m_data = (sfloat32*)calloc( 16, sizeof(sfloat32) );
  
  m_data[0]  = 1.0;
  m_data[5]  = 1.0;
  m_data[10] = 1.0;
  m_data[15] = 1.0;
}
