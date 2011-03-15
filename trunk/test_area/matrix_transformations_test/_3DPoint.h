#ifndef _3DPOINT_H
#define _3DPOINT_H

#include "../../lib/numeric_types.h"
#include "../../lib/numeric_constants.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>


class _3DPoint
{
  public:
    _3DPoint();
    _3DPoint( const _3DPoint& P );
    _3DPoint( const sfloat32& x, const sfloat32& y, const sfloat32& z );
    ~_3DPoint();
    
    _3DPoint&   operator=( const _3DPoint& P );
    sfloat32    operator*( const _3DPoint& P );
    _3DPoint    operator+( const _3DPoint& P );
    _3DPoint    operator-( const _3DPoint& P );
    
    sfloat32  get_x();
    sfloat32  get_y();
    sfloat32  get_z();
    sfloat32* get_points();
    
    void     set_x( const sfloat32& x );
    void     set_y( const sfloat32& y );
    void     set_z( const sfloat32& z );    
    void     set_points( const sfloat32 *v );
    
          sfloat32& operator[]( const uint32& i );
    const sfloat32& operator[]( const uint32& i ) const;
    
    void print();
    
  protected:
    sfloat32 * m_data;
};

#endif
