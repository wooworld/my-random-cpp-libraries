#ifndef _3X3MATRIX_H
#define _3X3MATRIX_H

#include "../../lib/numeric_types.h"

class _3x3Matrix
{
  public:
    _3x3Matrix();
    _3x3Matrix( const _3x3Matrix& M );
    
    void set_all( const sfloat32& F );
    
    _3x3Matrix& operator=(  const _3x3Matrix& M );
    _3x3Matrix  operator*(  const _3x3Matrix& M );
    _3x3Matrix  operator+(  const _3x3Matrix& M );
    _3x3Matrix  operator-(  const _3x3Matrix& M );
    _3x3Matrix  operator!();
 
    const sfloat32& operator[]( const uint32& i ) const;
          sfloat32& operator[]( const uint32& i );
 
    void scale( _3x3Matrix& M, const sfloat32& F );
    
    void print() const;  
  
  protected:
    sfloat32 *m_data;
};

#endif
