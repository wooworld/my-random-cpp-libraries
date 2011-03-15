#ifndef _4X4MATRIX_EULER_ROTATION_H
#define _4X4MATRIX_EULER_ROTATION_H

#include "../../lib/numeric_types.h"
#include "_4x4Matrix.h"
#include <cmath>

class _4x4Matrix_Euler_Rotation: public _4x4Matrix
{
  public:
    _4x4Matrix_Euler_Rotation
      ( 
        const sfloat32& phi, 
        const sfloat32& theta, 
        const sfloat32& psi 
      );
};

#endif
