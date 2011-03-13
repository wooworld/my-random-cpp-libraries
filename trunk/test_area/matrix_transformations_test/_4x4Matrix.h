#ifndef _4X4MATRIX_H
#define _4X4MATRIX_H

#include "../../lib/numeric_types.h"

class _4x4Matrix
{
  public:
    _4x4Matrix();
    _4x4Matrix( const _4x4Matrix& M );
    
    void set_all( const sfloat32& F );
    
    _4x4Matrix& operator=(  const _4x4Matrix& M );
    _4x4Matrix  operator*(  const _4x4Matrix& M );
    _4x4Matrix  operator+(  const _4x4Matrix& M );
    _4x4Matrix  operator-(  const _4x4Matrix& M );
    _4x4Matrix  operator!();
 
    const sfloat32& operator[]( const uint32& i ) const;
          sfloat32& operator[]( const uint32& i );
 
    void scale( _4x4Matrix& M, const sfloat32& F );
    
    void print() const;  
  
  protected:
    sfloat32 *m_data;
};

#endif
