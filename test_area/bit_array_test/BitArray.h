#ifndef BITARRAY_H
#define BITARRAY_H

#include "../../lib/numeric_types.h"

class BitArray
{
  public:
    BitArray();
    BitArray( const BitArray& B );
    BitArray( const uint32& size );
    ~BitArray();
    
    void set_size( const uint32& size );
    uint32 int_size();
    uint32 bit_size();
    uint32 size();
    void clear();
    void reset();
    
    void flip( const uint32& i );
    const uint8& operator[]( const uint32& i ) const;
          uint8& operator[]( const uint32& i );
    
    void set_all( const uint8 i );
    
    void print() const;
  
  protected:
    uint8  *m_data;
    uint32  m_int_size;
    uint32  m_bit_size;
};

#endif
