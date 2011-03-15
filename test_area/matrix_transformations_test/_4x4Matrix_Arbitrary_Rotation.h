#ifndef _4X4MATRIX_ARBITRARY_ROTATION_H
#define _4X4MATRIX_ARBITRARY_ROTATION_H

#include "../../lib/numeric_types.h"
#include "_4x4Matrix.h"
#include <cmath>

class _4x4Matrix_Arbitrary_Rotation: public _4x4Matrix
{
  public:
    _4x4Matrix_Arbitrary_Rotation
      ( 
        const sfloat32& alpha, 
        const sfloat32& beta, 
        const sfloat32& gamma 
      );
};

#endif
