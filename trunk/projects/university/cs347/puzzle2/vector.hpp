// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file Vector.hpp
/// @author Gary Steelman
/// @edit 5 Nov 2009
/// @brief Contains definitions for the vector class
///////////////////////////////////////////////////////////////////////////////

#pragma once //Ensures this file is only included once during compilation
#include "exception.h"
#include "str_manip.h"
#include <iostream>
using std::cout;
using std::endl;

//Default constructor
template <typename T>
Vector<T>::Vector() 
{
  m_size = 0;
  m_max_size = 1;
  m_data = new T[m_max_size];
}

//Constructor with specified size and data
template <typename T>
Vector<T>::Vector( const unsigned int& n, T to_fill = T() )
{
  m_size = 0;
  m_max_size = 1;
  m_data = new T[m_max_size];
  for ( unsigned long int i = 0; i < n; i++ )
    push_back( to_fill );
}

//Copy constructor
template <typename T>
Vector<T>::Vector( const Vector<T>& v )
{
  m_size = v.m_size;
  m_max_size = v.m_max_size;
  m_data = new T[m_max_size];
  
  //Copy all the data from v into current
  for ( unsigned long int i = 0; i < v.size(); i++ )
    m_data[i] =  v.m_data[i];

}

//Destructor
template <typename T>
Vector<T>::~Vector() { delete [] m_data; }

//Get size
template <typename T>
unsigned long int Vector<T>::size() const { return m_size; }

//Get max size
template <typename T>
unsigned long int Vector<T>::max_size() const { return m_max_size; }

//Appends an element to the Vector
template <typename T>
void Vector<T>::push_back( const T& to_push )
{
  //If we have enough room in the Vector still, just append the item
  if( m_size < m_max_size )
  {
    m_data[m_size] = to_push;
    m_size++;
  }
  
  //We don't have room in the Vector, so make it bigger and then add the item
  else
  {
    T * temp = m_data;
    m_max_size *= 2;
    m_data = new T[m_max_size];
    
    for( unsigned long int i = 0; i < m_size; i++ )
    {
      m_data[i] = temp[i];
    }
  
    delete [] temp;
    
    m_data[m_size] = to_push;
    m_size++;
  }
  
  return;
}

//Removes the last element in the Vector
template <typename T>
void Vector<T>::pop_back()
{
  //Make sure there's something in the Vector to remove
  if ( m_size == 0 )
    throw( Exception(1, "Attempted to pop an empty vector.") );
  
  //Just drop the size of the Vector by 1
  m_size--;
  
  //If there is something in the Vector and we've dropped below the memory
  //usage threshold so we can decrease the overall size of the Vector and free
  //some memory up
  if ( m_size <= (m_max_size * .25) )
  {
    m_max_size /= 2;
    T * temp = m_data;
    m_data = new T[m_max_size];
    
    for( unsigned long int i = 0; i < m_size; i++)
    {
      m_data[i] = temp[i];
    }
    
    delete [] temp;
  }
}

template <typename T>
void Vector<T>::insert( const unsigned long int& n, const T& to_insert )
{
  if ( n > m_size )
    throw( Exception( 2, "Out of bounds access. Vector insert()." ) );
    
  Vector<T> temp;
  
  //copy in the left part of the vector
  for ( unsigned long int i = 0; i < n; i++ )
    temp.push_back( m_data[i] );
    
  temp.push_back( to_insert );
  
  for ( unsigned long int i = n+1; n < m_size; i++ )
    temp.push_back( m_data[i] );
    
  *this = temp;
}

template <typename T>
void Vector<T>::remove( const unsigned long int& n )
{
  if ( n > m_size )
    throw( Exception( 2, "Out of bounds access. Vector remove()." ) );
    
  for ( unsigned long int i = n; i < (m_size-1); i++ )
    m_data[i] = m_data[i+1];
    
  pop_back();
  
  return;
}

//Resets the Vector to default specs
template <typename T>
void Vector<T>::clear()
{
  m_size = 0;
  m_max_size = 1;
  delete [] m_data;
  m_data = new T[m_max_size];
}

//Returns if the Vector is empty or not
template <typename T>
bool Vector<T>::empty() const { return ( m_size == 0 ); }

//Gets a specific element of the Vector
template <typename T>
T& Vector<T>::operator[]( const unsigned long int& n )
{
  if ( n > m_max_size )
    throw( Exception( 2, "Out of bounds access. Vector operator[]." ) );
  
  //Otherwise, we're good
  return m_data[n];
}

//indexing operator for a vector
template <typename T>
const T& Vector<T>::operator[]( const unsigned long int& n ) const
{
  if ( n > m_max_size )
    throw( Exception( 2, "Out of bounds access. Vector operator[]." ) );
  
  //Otherwise, we're good
  return m_data[n];
}

//assign one vector to another
template <typename T>
Vector<T>& Vector<T>::operator=( const Vector<T>& rhs )
{
  if ( this == &rhs )
    return *this;
    
  m_size = rhs.m_size;
  m_max_size = rhs.m_max_size;
  m_data = new T[m_max_size];
  
  //Copy all the data from v into current
  for ( unsigned long int i = 0; i < rhs.size(); i++ )
    m_data[i] =  rhs.m_data[i];
  
  return *this;
}

//assign a STL vector to our Vector
template <typename T>
Vector<T>& Vector<T>::operator=( const std::vector<T>& rhs )
{
  /*if ( this == &rhs )
    return *this;*/
  //cout << "vector -> Vector operator = " << endl;
  //cout << "rhs.size() " << rhs.size() << endl;
  m_size = rhs.size();
  
  //cout << "rhs.capacity() " << rhs.capacity() << endl;
  m_max_size = rhs.capacity();
  m_data = new T[m_max_size];
  
  //Copy all the data from v into current
  for ( unsigned long int i = 0; i < rhs.size(); i++ )
    m_data[i] =  rhs[i];
  
  return *this;
}

//Change vector size to specific size
template <typename T>
void Vector<T>::set_size( const unsigned int& n, T c = T() )
{
  if ( n == size() )
    return;
    
  else if ( n == 0 )
    clear();
    
  else if ( n < size() )
    for ( unsigned long int i = size(); i > n; i-- )
      pop_back();
      
  else
    for ( unsigned long int i = size(); i < n; i++ )
      push_back( c );
 
  return;
}

//output
template <typename T>
std::ostream& operator<<( std::ostream& os, const Vector<T>& v )
{
  for ( unsigned long int i = 0; i < v.size(); i++ )
  {
    os << v[i] << " ";
    //os << v[i] << " ";
  }
  
  return os;
}

//input
template <typename T>
std::istream& operator>>( std::istream& is, Vector<T>& v )
{
  for ( unsigned long int i = 0; i < v.size(); i++ )
  {
    v[i] = is;
  }
  
  return is;
} 

//addition
template <typename T>
Vector<T> Vector<T>::operator+( const Vector<T>& rhs )
{
  if ( m_size != rhs.size() )
    throw Exception( 3, "Size mismatch. Vector operator+()." );
    
  Vector<T> v( m_size );
  for ( unsigned long int i = 0; i < m_size; i++ )
    v.m_data[i] =  m_data[i] + rhs.m_data[i];
    
  return v;
}

//self-assigned addition
template <typename T>
Vector<T>& Vector<T>::operator+=( const Vector<T>& rhs )
{
  if ( m_size != rhs.size() )
    throw Exception( 3, "Size mismatch. Vector operator+=()." );
    
  for ( unsigned long int i = 0; i < m_size; i++ )
    m_data[i] = m_data[i] + rhs.m_data[i];
    
  return *this;
}

//subtraction
template <typename T>
Vector<T> Vector<T>::operator-( const Vector<T>& rhs )
{
  if ( m_size != rhs.size() )
    throw Exception( 3, "Size mismatch. Vector operator-()." );
    
  Vector<T> v( m_size );
  for ( unsigned long int i = 0; i < m_size; i++ )
    v.m_data[i] =  m_data[i] - rhs.m_data[i];
    
  return v;
}

//self-assigned subtraction
template <typename T>
Vector<T>& Vector<T>::operator-=( const Vector<T>& rhs )
{
  if ( m_size != rhs.size() )
    throw Exception( 3, "Size mismatch. Vector operator-=()." );
    
  for ( unsigned long int i = 0; i < m_size; i++ )
    m_data[i] = m_data[i] - rhs.m_data[i];
    
  return *this;
}

//multiplication
template <typename T>
Vector<T> Vector<T>::operator*( const Vector<T>& rhs )
{
  if ( m_size != rhs.size() )
    throw Exception( 3, "Size mismatch. Vector operator*()." );
    
  Vector<T> v( m_size );
  for ( unsigned long int i = 0; i < m_size; i++ )
    v.m_data[i] =  m_data[i] * rhs.m_data[i];
    
  return v;
}

//multiplication by a scalar
template <typename T>
Vector<T> Vector<T>::scale( const T& rhs )
{
  Vector<T> v( *this );
  for ( unsigned long int i = 0; i < v.m_size; i++ )
    v.m_data[i]  = v.m_data[i] * rhs;
    
  return v;
}

//self-assigned multiplication
template <typename T>
Vector<T>& Vector<T>::operator*=( const Vector<T>& rhs )
{
  if ( m_size != rhs.size() )
    throw Exception( 3, "Size mismatch. Vector operator*=()." );
    
  for ( unsigned long int i = 0; i < m_size; i++ )
    m_data[i] = m_data[i] * rhs.m_data[i];
    
  return *this;
}

//division
template <typename T>
Vector<T> Vector<T>::operator/( const Vector<T>& rhs )
{
  if ( m_size != rhs.size() )
    throw Exception( 3, "Size mismatch. Vector operator/()." );
    
  Vector<T> v( m_size );
  for ( unsigned long int i = 0; i < m_size; i++ )
  {
    if ( rhs.m_data[i] == 0 )
      throw Exception( 4, "Division by zero. Vector operator/()" );
    v.m_data[i] =  m_data[i] / rhs.m_data[i];
  } 
   
    
  return v;
}

//self-assigned division
template <typename T>
Vector<T>& Vector<T>::operator/=( const Vector<T>& rhs )
{
  if ( m_size != rhs.size() )
    throw Exception( 3, "Size mismatch. Vector operator/=()." );
    
  for ( unsigned long int i = 0; i < m_size; i++ )
  {
    if ( rhs.m_data[i] == 0 )
      throw Exception( 4, "Division by zero. Vector operator/()" );
    m_data[i] = m_data[i] / rhs.m_data[i];
  }
    
  return *this;
}

//reset
template <typename T>
Vector<T>& Vector<T>::operator~()
{
  for ( unsigned long int i = 0; i < m_size; i++ )
    m_data[i] = T();
  
  return *this;
}

//set all to 
template <typename T>
Vector<T>& Vector<T>::set_all( const T& set_to )
{
  for ( unsigned long int i = 0; i < m_size; i++ )
    m_data[i] = set_to;
  
  return *this;
}

//Equality
template <typename T>
bool Vector<T>::operator==( const Vector<T>& rhs ) const
{
  if ( this == &rhs )
    return true;
    
  for ( unsigned long int i = 0; i < m_size; i++ )
    if ( !(m_data[i] == rhs.m_data[i]) )
      return false;
  
  return true;
}

//Inequality
template <typename T>
bool Vector<T>::operator!=( const Vector<T>& rhs ) const
{
  return !( *this == rhs );
}

//inner producting
template <typename T>
T innerProduct( const Vector<T>& lhs, const Vector<T>& rhs )
{
  T result = T();
  if ( lhs.size() != rhs.size() )
    throw Exception( 3, "Size mismatch. Vector innerProduct()." );
  
  for ( unsigned long int i = 0; i < lhs.size(); i++ )
    result = result + ( lhs[i] * rhs[i] );
    
  return result;
}

//finding max in a Vector
template <typename T>
T Vector<T>::max( const unsigned long int& start = 0, const unsigned long int& end = 0 ) const
{
  //stupidity check
  if ( start > end )
  {
    T temp = start;
    start = end;
    end = temp;
  }
  
  //if we want to start past the size or end before the start...
  if ( start > m_size )
    throw Exception( 2, "Out of bounds access. Vector max()." );
  
  //just end at the end if they want to end before the vector does
  if ( end > m_size )
    end = m_size;
    
  //The first element of the Vector
  T result = m_data[start];
  
  //Run through each element and find the largest one
  for ( unsigned long int i = start; i <= end; i++ )
    if ( m_data[i] > result )
      result = m_data[i];
  
  return result;
}

//finding min in a Vector
template <typename T>
T Vector<T>::min( const unsigned long int& start = 0, const unsigned long int& end = 0 ) const
{
  //stupidity check
  if ( start > end )
  {
    T temp = start;
    start = end;
    end = temp;
  }
  
  //if we want to start past the size or end before the start...
  if ( start > m_size )
    throw Exception( 2, "Out of bounds access. Vector min()." );
  
  //just end at the end if they want to end before the vector does
  if ( end > m_size )
    end = m_size;
    
  //The first element of the Vector
  T result = m_data[start];
  
  //Run through each element and find the largest one
  for ( unsigned long int i = start; i <= end; i++ )
    if ( m_data[i] < result )
      result = m_data[i];
  
  return result;
}

//finding max in a Vector
template <typename T>
T Vector<T>::max_index( const unsigned long int& start = 0, const unsigned long int& end = 0 ) const
{
  /*max_loc = start;
  max_val = m_data[start];
  
  for ( unsigned long int i = start; i < end; i++ )
  {
    if ( m_data[i] > max_val )
    {
      max_val = m_data[i];
      max_loc = i;
    }
  } 

  return max_loc;*/
  
  unsigned long int s = start;
  unsigned long int e = end;
  //stupidity check
  if ( s > e )
  {
    unsigned long int temp = s;
    s = e;
    e = temp;
  }
    
  //cout << "  s = " << s << " and e = " << e << endl;
  //if we want to s past the size or e before the s...
  if ( s > m_size )
    throw Exception( 2, "Out of bounds access. Vector max_index()." );
  
  //just e at the e if they want to e before the vector does
  if ( e > m_size )
    e = m_size;
   
  //The first element of the Vector
  T max = m_data[s];
  
  unsigned long int result = s;
  
  //Run through each element and find the largest one
  for ( unsigned long int i = s; i <= e; i++ )
  {
    if ( m_data[i] > max )
    {
      max = m_data[i];
      result = i;
    }
  }
  
  return result;
}

//finding max in a Vector
template <typename T>
T Vector<T>::min_index( const unsigned long int& start = 0, const unsigned long int& end = 0 ) const
{
  unsigned long int s = start;
  unsigned long int e = end;
  //stupidity check
  if ( s > e )
  {
    T temp = s;
    s = e;
    e = temp;
  }
  
  //if we want to s past the size or e before the s...
  if ( s > m_size )
    throw Exception( 2, "Out of bounds access. Vector min_index()." );
  
  //just e at the e if they want to e before the vector does
  if ( e > m_size )
    e = m_size;
   
  //The first element of the Vector
  T min = m_data[s];
  
  unsigned long int result = s;
  
  //Run through each element and find the largest one
  for ( unsigned long int i = s; i <= e; i++ )
  {
    if ( m_data[i] < min )
      min = m_data[i];
    
    result = i;
  }
  
  return result;
}

template <typename T>
Vector<T> absolute( const Vector<T>& v )
{
  Vector<T> u( v );
  
  for ( unsigned long int i = 0; i < u.size(); i++ )
    if ( u[i] < 0 )
      u[i] = u[i] * -1;
  
  return u;
}

// END OF FILE ----------------------------------------------------------------
