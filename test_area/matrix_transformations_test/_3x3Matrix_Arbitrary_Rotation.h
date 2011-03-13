#ifndef _3X3MATRIX_ARBITRARY_ROTATION_H
#define _3X3MATRIX_ARBITRARY_ROTATION_H

#include "../../lib/numeric_types.h"
#include "_3x3Matrix.h"

class _3x3Matrix_Arbitrary_Rotation: public _3x3Matrix
{
  public:
    _3x3Matrix_Arbitrary_Rotation
      ( 
        const sfloat32& alpha, 
        const sfloat32& beta, 
        const sfloat32& gamma 
      );
};

#endif
