#include "../../lib/numeric_types.h"
#include "BitArray.h"

#include <cstdio>
#include <cstdlib>

BitArray::BitArray()
{
  reset();
}

BitArray::BitArray( const BitArray& B )
{
  m_int_size = B.m_int_size;
  m_bit_size = B.m_bit_size;
  
  m_data = (uint8*)calloc( m_int_size, sizeof(uint8) );
  
  for ( uint32 i = 0; i < m_int_size; i++ )
    m_data[i] = B.m_data[i];
}

// size is in number of BITS desired
// size < UINT32_MAX / 8
BitArray::BitArray( const uint32& size )
{
  set_size( size );
}

BitArray::~BitArray()
{
}

// size < UINT32_MAX / 8
void BitArray::set_size( const uint32& size )
{
  m_int_size = (size / 8) + 1;
  m_bit_size = size;
  
  m_data = (uint8*)calloc( m_int_size, sizeof(uint8) );
  
  return;
}

uint32 BitArray::int_size()
{
  return m_int_size;
}

uint32 BitArray::bit_size()
{
  return m_bit_size;
}

uint32 BitArray::size()
{
  return m_bit_size;
}

void BitArray::clear()
{
  m_data = (uint8*)calloc( m_int_size, sizeof(uint8) );
  
  return;
}

void BitArray::reset()
{
  m_int_size = 0;
  m_bit_size = 0;
  m_data = (uint8*)calloc( m_int_size, sizeof(uint8) );
  
  return;
}

void BitArray::flip( const uint32& i )
{
  
  
  return;
}

const uint8& BitArray::operator[]( const uint32& i ) const
{
  return m_data[0];

  // return 0;
}

uint8& BitArray::operator[]( const uint32& i )
{
  // call looks like BitArray[21] = 0 or BitArray[21] = 1;
  // or              BitArray[21]
  
      // int div
  // m_data[ 21/8 ] & 

  return m_data[0];
  
  // return 0;
}

void BitArray::set_all( const uint8 i )
{
  
  return;
}

void BitArray::print() const
{
  // for ( uint32 i = 0; i < 

  return;
}
