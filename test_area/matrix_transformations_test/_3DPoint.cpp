#include "_3DPoint.h"

_3DPoint::_3DPoint()
{
  m_data = (sfloat32*)calloc( 3, sizeof(sfloat32) );
}

_3DPoint::_3DPoint( const _3DPoint& P )
{
  m_data = (sfloat32*)calloc( 3, sizeof(sfloat32) );
  memcpy( m_data, P.m_data, 3 * sizeof(sfloat32) );
}

_3DPoint::_3DPoint( const sfloat32& x, const sfloat32& y, const sfloat32& z )
{
  m_data = (sfloat32*)calloc( 3, sizeof(sfloat32) );
  m_data[0] = x;
  m_data[1] = y;
  m_data[2] = z;
}

_3DPoint::~_3DPoint() {}

_3DPoint& _3DPoint::operator=( const _3DPoint& P )
{
  // Check for assignment against self
  if ( this == &P )
    return *this;
  
  // memcpy( m_data, P.m_data, 3 * sizeof(sfloat32) );
  m_data[0] = P.m_data[0];
  m_data[1] = P.m_data[1];
  m_data[2] = P.m_data[2];  
  
  return *this;
}

_3DPoint _3DPoint::operator+( const _3DPoint& P )
{
  _3DPoint Temp;
  
  Temp[0] = m_data[0] + P.m_data[0];
  Temp[1] = m_data[1] + P.m_data[1];
  Temp[2] = m_data[2] + P.m_data[2];
  
  return Temp;
}

_3DPoint _3DPoint::operator-( const _3DPoint& P )
{
  _3DPoint Temp;
  
  Temp[0] = m_data[0] - P.m_data[0];
  Temp[1] = m_data[1] - P.m_data[1];
  Temp[2] = m_data[2] - P.m_data[2];
  
  return Temp;
}

// dot product
sfloat32 _3DPoint::operator*( const _3DPoint& P )
{
  sfloat32 result = m_data[0] * P.m_data[0] + m_data[1] * P.m_data[1] + m_data[2] * P.m_data[2];

  return result;
}

sfloat32 _3DPoint::get_x()
{
  return m_data[0];
}

sfloat32 _3DPoint::get_y()
{
  return m_data[1];
}

sfloat32 _3DPoint::get_z()
{
  return m_data[2];
}

sfloat32* _3DPoint::get_points()
{
  return m_data;
}

void _3DPoint::set_x( const sfloat32& x )
{
  m_data[0] = x;
  
  return;
}

void _3DPoint::set_y( const sfloat32& y )
{
  m_data[1] = y;
  
  return;
}

void _3DPoint::set_z( const sfloat32& z )
{
  m_data[2] = z;
  
  return;
}

void _3DPoint::set_points( const sfloat32* v )
{
  // memcpy( m_data, V.m_data, 3 * sizeof(sfloat32) );
  m_data[0] = v[0];
  m_data[1] = v[1];
  m_data[2] = v[2]; 

  return;
}

sfloat32& _3DPoint::operator[]( const uint32& i )
{
  return m_data[i];
}

const sfloat32& _3DPoint::operator[]( const uint32& i ) const
{
  return m_data[i];
}

void _3DPoint::print()
{
  printf( "% 10.3f\n", m_data[0] );
  printf( "% 10.3f\n", m_data[1] );
  printf( "% 10.3f\n", m_data[2] );
  printf( "\n" );
  
  return;
}
