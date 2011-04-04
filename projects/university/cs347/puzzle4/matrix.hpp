// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @auth Gary Steelman
/// @file matrix.hpp
/// @edit 13 Nov 2009
/// @brief Contains the implementation for the Matrix templated class
/// @note Also, column operations are much slower than row operations, due to
///   the nature of the way the Matrix data is stored.
///////////////////////////////////////////////////////////////////////////////

#include "vector.h"
#include "str_manip.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

template <typename T>
Matrix<T>::Matrix():m_rows( 0 ), m_cols( 0 ) { }

template <typename T>
Matrix<T>::Matrix( const unsigned long int& rows, const unsigned long int& cols )
{
  m_rows = rows;
  m_cols = cols;
  m_data.set_size( m_rows );
  for ( unsigned long int i = 0; i < m_rows; i++ )
    m_data[i].set_size( m_cols );
}

template <typename T>
Matrix<T>::Matrix( const Vector<T>& v )
{
  //The following makes a horizontal vector matrix thing
  /*m_rows = 1;
  m_cols = v.size();
  m_data[0] = v;*/
  
  //The following makes a vertical vector matrix thing
  m_rows = v.size();
  m_cols = 1;
  m_data.set_size( m_rows );
  set_col( 0, v );
}

template <typename T>
Matrix<T>::Matrix( const Vector<Vector<T> >& v )
{
  for ( unsigned long int i = 0; i < v.size()-1; i++ )
    if ( v[i].size() != v[i+1].size() )
      throw Exception( 26, "Vectors containing data are not of equal size. Matrix::Matrix(Vector<Vector<T> >)." );
      
  m_data.set_size( v.size() );
  
  //Because this assignment has only square matrices...
  m_rows = v.size();
  
  for ( unsigned long int i = 0; i < m_rows; i++ )
    m_data[i] = v[i];
    
  m_cols = v[0].size();
}

template <typename T>
Matrix<T>::Matrix( const File& f )
{
  //loadFromFile( f );
}

template <typename T>
Matrix<T>::Matrix( const Matrix<T>& m )
{
  m_rows = m.height();
  m_cols = m.width();
  
  //Set the number of rows
  m_data.set_size( m_rows );
  
  //For each row expand it to m's size
  for ( unsigned long int i = 0; i < m_rows; i++ )
  {  
    m_data[i].set_size( m_cols );
    
    //and now copy over the data from m
    for ( unsigned long int j = 0; j < m_cols; j++ )
      m_data[i][j] = m.m_data[i][j];
  }
}

template <typename T>
Matrix<T>::~Matrix(){ }

template <typename T>
unsigned long int Matrix<T>::width() const { return m_cols; }

template <typename T>
unsigned long int Matrix<T>::height() const { return m_rows; }

template <typename T>
unsigned long int Matrix<T>::size() const { return ( m_cols * m_rows ); }

template <typename T>
void Matrix<T>::set_width( const unsigned long int& n )
{
  if ( n == m_cols)
    return;
  
  m_cols = n;
  
  //Just run through each row and expand its size to n
  for ( unsigned long int i = 0; i < m_rows; i++ )
    m_data[i].set_size( m_cols );
      
  return;
}

template <typename T>
void Matrix<T>::set_height( const unsigned long int& n )
{
  if ( n == m_rows )
    return;
  
  else if ( n < m_rows )
  {
    m_data.set_size( n );
    m_rows = n;
  }
  
  else if ( n > m_rows )
  {
    //Expand the number of rows by to n
    m_data.set_size( n );
    
    //Now expand those new rows to the correct number of columns
    for ( unsigned long int i = m_rows; i < n; i++ )
      m_data[i].set_size( m_cols );
    
    //And update our lonely variable
    m_rows = n;
  }
  
  return;
}

template <typename T>
void Matrix<T>::set_all( const T& to_set )
{
  for ( unsigned long int i = 0; i < m_rows; i++ )
    for ( unsigned long int j = 0; j < m_cols; j++ )
      m_data[i][j] = to_set;
  
  return;
}

template <typename T>
const Vector<T>& Matrix<T>::get_row( const unsigned long int& n ) const
{
  if ( n > m_rows )
    throw Exception( 23, "Out of bounds access. Matrix::get_row()" );
    
  return m_data[n];
}

template <typename T>
const Vector<T>& Matrix<T>::get_col( const unsigned long int& n ) const
{
  if ( n > m_cols )
    throw Exception( 23, "Out of bounds access. Matrix::get_col()" );
    
  Vector<T> v( m_rows );
  for ( unsigned long int i = 0; i < m_rows; i++ )
    v[i] = m_data[i][n];
  
  return v;
}

template <typename T>
void Matrix<T>::set_row( const unsigned long int& n, const T& to_set )
{
  if ( n > m_rows )
    throw Exception( 23, "Out of bounds access. Matrix::set_row()" );
  
  for ( unsigned long int i = 0; i < m_cols; i++ )
    m_data[n][i] = to_set;
  
  return;
}

template <typename T>
void Matrix<T>::set_col( const unsigned long int& n, const T& to_set )
{
  if ( n > m_cols )
    throw Exception( 23, "Out of bounds access. Matrix::set_col()" );
    
  for ( unsigned long int i = 0; i < m_rows; i++ )
    m_data[i][n] = to_set;
    
  return;
}

template <typename T>
void Matrix<T>::set_row( const unsigned long int& n, const Vector<T>& to_set )
{
  if ( n > m_rows )
    throw Exception( 23, "Out of bounds access. Matrix::set_row()" );
  
  if ( to_set.size() != m_cols )
    throw Exception( 24, "Size mismatch. Matrix::set_row()" );
  
  for ( unsigned long int i = 0; i < m_cols; i++ )
    m_data[n][i] = to_set[i];
  
  return;
}

template <typename T>
void Matrix<T>::set_col( const unsigned long int& n, const Vector<T>& to_set )
{
  if ( n > m_cols )
    throw Exception( 23, "Out of bounds access. Matrix::set_col()" );
  
  if ( to_set.size() != m_rows )
    throw Exception( 24, "Size mismatch. Matrix::set_col()" );
  
  for ( unsigned long int i = 0; i < m_rows; i++ )
    m_data[i][n] = to_set[i];
  
  return;
}

template <typename T>
void Matrix<T>::insert_row( const unsigned long int& loc, const Vector<T>& v )
{
  if ( loc > m_rows )
    throw Exception( 23, "Out of bounds access. Matrix::insert_row()" );
  
  if ( v.size() != m_cols )
    throw Exception( 24, "Size mismatch. Matrix::insert_row()" );
    
  set_height( m_rows + 1 );
    
  //Copy all the rows down 1 row to make room for where we want to insert
  for ( unsigned long int i = m_rows; i > loc; i-- )
    m_data[i] = m_data[i-1];
  
  //Insert v
  m_data[loc] = v;
    
  return;
}

template <typename T>
void Matrix<T>::insert_col( const unsigned long int& loc, const Vector<T>& v )
{
  if ( loc > m_cols )
    throw Exception( 23, "Out of bounds access. Matrix::insert_col()" );
  
  if ( v.size() != m_rows )
    throw Exception( 24, "Size mismatch. Matrix::insert_col()" );
    
  //Expand the matrix size by 1
  set_width( m_cols + 1 );
  
  //move all the columns to the right 1
  for ( unsigned long int i = 0; i < m_rows; i++ )
    for ( unsigned long int j = m_cols; j > loc; j-- )
      m_data[i][j] = m_data[i][j-1];
      
  //now insert the column
  for ( unsigned long int i = 0; i < m_rows; i++ )
    m_data[i][loc] = v[i];
    
  return;
}

template <typename T>
void Matrix<T>::delete_row( const unsigned long int& loc )
{
  if ( loc > m_rows )
    throw Exception( 23, "Out of bounds access. Matrix::delete_row()" );
    
  //Shift all the rows below loc up one
  for ( unsigned long int i = loc; i < (m_rows-1); i++ )
    m_data[i] = m_data[i+1];
  
  //Delete the last row
  m_data.pop_back();
  
  m_rows-=1;
  
  return;
}

template <typename T>
void Matrix<T>::delete_col( const unsigned long int& loc )
{
  if ( loc > m_cols )
    throw Exception( 23, "Out of bounds access. Matrix::delete_col()" );
    
  //Shift all the cols to the right of loc left one
  for ( unsigned long int i = 0; i < m_rows; i++ )
  {
    for ( unsigned long int j = loc; j < (m_cols-1); j++ )
      m_data[i][j] = m_data[i][j+1];
  
    //Now that we've shifted all our data in the individual row left one, pop
    //the far right spot and we're good
    m_data[i].pop_back();
  }
  
  m_cols-=1;
  
  return;
}

template <typename T>
void Matrix<T>::swap_row( const unsigned long int& first, 
                          const unsigned long int& second )
{
  if ( (first > m_rows) || (second > m_rows) )
    throw Exception( 23, "Out of bounds access. Matrix::delete_row()" );
  
  if ( first == second )
    return;
  
  //Stores first location's row in a temp vector
  Vector<T> temp( get_row( first) );
  
  //Put's the second location's row in first's location
  set_row( first, get_row( second ) );
  
  //Puts temp into second's location
  set_row( second, temp );
  
  return;
}

template <typename T>
void Matrix<T>::swap_col( const unsigned long int& first, 
                          const unsigned long int& second )
{
  if ( (first > m_cols) || (second > m_cols) )
    throw Exception( 23, "Out of bounds access. Matrix::delete_row()" );
  
  if ( first == second )
    return;
    
  //Going to grab first's data and store it in a vector
  Vector<T> temp( get_col( first ) );
  
  //Put second's data in first's spot...
  set_col( first, get_col( second ) );
  
  //And now put temp into second's spot
  set_col( second, temp );
    
  return;
}

template <typename T>
void Matrix<T>::app_row( const Vector<T>& v )
{
  if ( v.size() != m_cols )
    throw Exception( 24, "Size mismatch. Matrix::app_row()" );
  
  //Make an extra row and set its data to the desired vector
  set_height( m_rows + 1 );
  set_row( m_rows - 1, v );
  
  return;
}

template <typename T>
void Matrix<T>::app_col( const Vector<T>& v )
{
  if ( v.size() != m_rows )
    throw Exception( 24, "Size mismatch. Matrix::app_cols()" );
    
  //Make an extra column and set its data to the desired vector
  set_width( m_cols + 1 );
  set_col( m_cols - 1, v );
  
  return;
}

template <typename T>
Matrix<T>& Matrix<T>::ref()
{

  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::rref()
{

  return *this;
}

template <typename T>
Vector<T>& Matrix<T>::operator[]( const unsigned long int& n )
{
  if ( n > m_rows )
    throw Exception( 23, "Out of bounds access. Matrix::operator[]" );
    
  return m_data[n];
}

template <typename T>
const Vector<T>& Matrix<T>::operator[]( const unsigned long int& n ) const
{
  if ( n > m_rows )
    throw Exception( 23, "Out of bounds access. Matrix::operator[]" );
    
  return m_data[n];
}

template <typename T>
Matrix<T>& Matrix<T>::operator=( const Matrix<T>& rhs )
{
  //make sure we aren't assigning to ourselves
  if ( this == &rhs )
    return *this;
    
  m_rows = rhs.height();
  m_cols = rhs.width();
  
  //Set the number of rows
  m_data.set_size( m_rows );
  
  //For each row expand it to m's size
  for ( unsigned long int i = 0; i < m_rows; i++ )
  {  
    m_data[i].set_size( m_cols );
    
    //and now copy over the data from m
    for ( unsigned long int j = 0; j < m_cols; j++ )
      m_data[i][j] = rhs.m_data[i][j];
  }
  
  return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+( const Matrix<T>& rhs )
{
  if ( (m_rows != rhs.height()) || (m_cols != rhs.width()) )
    throw Exception( 25, "Dimenion mismatch. Matrix::operator+" );
    
  //Set us up a temp matrix
  Matrix M( m_rows, m_cols );
  
  //Just add the vectors for each row, probably a little slower than adding
  //individual entries because of function calls
  for ( unsigned long int i = 0; i < m_rows; i++ )
    M[i] = m_data[i] + rhs.m_data[i];
  
  return M;
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=( const Matrix<T>& rhs )
{
  if ( (m_rows != rhs.height()) || (m_cols != rhs.width()) )
    throw Exception( 25, "Dimenion mismatch. Matrix::operator+=" );
  
  //Just add the vectors for each row, probably a little slower than adding
  //individual entries because of function calls
  for ( unsigned long int i = 0; i < m_rows; i++ )
    m_data[i] = m_data[i] + rhs.m_data[i];
 
  return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator-( const Matrix<T>& rhs )
{
  if ( (m_rows != rhs.height()) || (m_cols != rhs.width()) )
    throw Exception( 25, "Dimenion mismatch. Matrix::operator-" );
    
  //Set us up a temp matrix
  Matrix M( m_rows, m_cols );
  
  //Just add the vectors for each row, probably a little slower than adding
  //individual entries because of function calls
  for ( unsigned long int i = 0; i < m_rows; i++ )
    M[i] = m_data[i] - rhs.m_data[i];
  
  return M;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=( const Matrix<T>& rhs )
{
  if ( (m_rows != rhs.height()) || (m_cols != rhs.width()) )
    throw Exception( 25, "Dimenion mismatch. Matrix::operator-=" );
  
  //Just add the vectors for each row, probably a little slower than adding
  //individual entries because of function calls
  for ( unsigned long int i = 0; i < m_rows; i++ )
    m_data[i] = m_data[i] - rhs.m_data[i];
 
  return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator*( const Matrix<T>& rhs )
{
  //make sure the inner dimensions match
  if ( m_cols != rhs.m_rows )
    throw Exception( 25, "Dimenion mismatch. Matrix::operator*(Matrix)" );
  
  //set up the answer matrix
  Matrix<T> M( m_rows, rhs.m_cols );
  
  //To obtain the i,j entry of AB, multiply Row i of A by Column j of B.
  for ( unsigned long int i = 0; i < m_rows; i++ )
    for ( unsigned long int j = 0; j < rhs.m_cols; j++ )
      M[i][j] = innerProduct( m_data[i], rhs.get_col ( j ) ) ;
  
  return M;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=( const Matrix<T>& rhs )
{
  //make sure the inner dimensions match
  if ( m_cols != rhs.m_rows )
    throw Exception( 25, "Dimenion mismatch. Matrix::operator*=(Matrix)" );
  
  //set up the answer matrix
  Matrix<T> M( m_rows, rhs.m_cols );
  
  //To obtain the i,j entry of AB, multiply Row i of A by Column j of B.
  for ( unsigned long int i = 0; i < m_rows; i++ )
    for ( unsigned long int j = 0; j < rhs.m_cols; j++ )
      M[i][j] = M[i][j] + ( innerProduct( m_data[i], get_col ( j ) ) );
  
  *this = M;
  
  return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator*( const Vector<T>& rhs )
{
  if ( m_cols != rhs.size() )
    throw Exception( 25, "Dimenion mismatch. Matrix::operator*(Vector)" );
  
  Matrix rhsInMatrix( rhs );
  
  return ( *this * rhsInMatrix );
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=( const Vector<T>& rhs )
{
  if ( m_cols != rhs.size() )
    throw Exception( 25, "Dimenion mismatch. Matrix::operator*=(Vector)" );
    
  Matrix rhsInMatrix( rhs );
  
  *this*=rhsInMatrix;
  
  return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator*( const T& rhs )
{
  Matrix M( m_rows, m_cols );
  M.scale( rhs );
  return M;
}

template <typename T>
Matrix<T>& Matrix<T>::scale( const T& scalar )
{
  //Just run through each element and multiply it by scalar
  for ( unsigned long int i = 0; i < m_rows; i++ )
    for (unsigned long int j = 0; j < m_cols; j++ )
      m_data[i][j] = m_data[i][j] * scalar;
      
  return *this;
}

template <typename T>
Vector<T> Matrix<T>::scale_row( const unsigned long int& loc, const T& scalar )
{
  if ( loc > m_rows )
    throw Exception( 23, "Out of bounds access. Matrix::scale_row" );
  
  //Gets the row we want to work with
  Vector<T> v( get_row( loc ) );
  
  for ( unsigned long int i = 0; i < m_cols; i++ )
    v[i] = v[i] * scalar;
  
  return v;
}

template <typename T>
Vector<T> Matrix<T>::scale_col( const unsigned long int& loc, const T& scalar )
{
  if ( loc > m_cols )
    throw Exception( 23, "Out of bounds access. Matrix::scale_col" );
    
  //Gets the column we want to work with
  Vector<T> v( get_col( loc ) );
  
  for ( unsigned long int i = 0; i < m_rows; i++ )
    v[i] = v[i] * scalar;
    
  return v;  
}

//
template <typename T>
Matrix<T>& Matrix<T>::operator~()
{
  //Just run through each element and set it to 0
  for ( unsigned long int i = 0; i < m_rows; i++ )
    for ( unsigned long int j = 0; j < m_cols; j++ )
      m_data[i][j] = T();
      
  return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator-()
{
  Matrix M( m_rows, m_cols );
  
  //Just run through each element and multiply by -1
  for ( unsigned long int i = 0; i < m_rows; i++ )
    for ( unsigned long int j = 0; j < m_cols; j++ )
      M.m_data[i][j] = M.m_data[i][j] * -1;

  return M;
}

template <typename T>
Matrix<T> Matrix<T>::operator!()
{
  //Take each row and put it into a column
  //Creates a Matrix of opposite dimensions to dump into
  Matrix<T> M( m_cols, m_rows );
  for ( unsigned long int i = 0; i < m_rows; i++ )
    M.set_col( i, m_data[i] );

  return M;
}

template <typename T>
bool Matrix<T>::operator==( const Matrix<T>& rhs ) const
{
  for ( unsigned long int i = 0; i < m_data.size(); i++ )
    //Just compares each row, using the Vector's == operator
    if ( !(m_data[i] == rhs.m_data[i]) )
      return false;
      
  return true;
}

template <typename T>
bool Matrix<T>::operator!=( const Matrix<T>& rhs ) const
{
  return !( *this == rhs );
}

template <typename T>
std::ostream& operator<<( std::ostream& os, const Matrix<T>& M )
{  
  for ( unsigned long int i = 0; i < M.m_rows; i++ )
  {
    for ( unsigned long int j = 0; j < M.m_cols; j++ )
      os << M.m_data[i][j] << " ";
    
    os << endl;
  }
  os << M.m_rows << "x" << M.m_cols << endl;
  return os;
}

template <typename T>
void Matrix<T>::print() const
{
  for ( unsigned long int i = 0; i < m_rows; i++ )
  {
    for ( unsigned long int j = 0; j < m_cols; j++ )
      cout << m_data[i][j] << " ";
    
    cout << endl;
  }
  cout << m_rows << "x" << m_cols << endl;
  return;
}

template <typename T>
std::istream& operator>>( std::istream& is, Matrix<T>& M )
{
  /*std::string currLine = "";
  Vector<std::string> currSet;
  unsigned long int currLineNum = 0;
  
  //Get the first line to start us off
  getline( is, currLine );
  
  //Parse into dimension
  M.set_height( str_to_ulint( currLine ) );
  M.set_width( M.height() );
  getline( is, currLine ); //blank line
  
  //Thus starts the body of the matrix itself, keep reading lines
  //until we get to a line that is blank
  while ( getline( is, currLine ) )
  {
    if ( currLineNum > M.height() )
      throw Exception( 25, "Dimenion mismatch. Matrix::operator>>" );
      
    if ( currLine == "\n" || currLine == "" || currLine == char_to_str('\n') )
      break; 
   
    currSet = str_breakup( currLine, "  " );
    
    for ( unsigned long int i = 0; i < M.width(); i++ )
      M[currLineNum][i] = str_to_double( currSet[i] );

    currLineNum++;
  }
  
  getline( is, currLine ); //the last line  
  currSet = str_breakup( currLine, "  " );

  Vector<double> rhs( currSet.size() );
  
  for ( unsigned long int i = 0; i < currSet.size(); i++ )
    rhs[i] = str_to_double( currSet[i] );

  M.app_col( rhs );*/
  
  //For parsing the file
  std::string currLine = "";
  Vector<std::string> currSet;
  unsigned int numCities = 0;
  
  //Grab the first line, it just says "Cities:"
  getline( is, currLine );
  
  //Move onto the next line, tells us how many cities there are
  getline( is, currLine );
  numCities = str_to_int( currLine );
  //cout << "numCities = " << numCities << endl;
  
  //Set up our matrix to be the size we need
  M.set_height( numCities );
  M.set_width(  numCities );
  
  //Grab the next line, it just says "Edge Weights:"
  getline( is, currLine );
  
  //Now we start filling in our Matrix. Since it's a square matrix because
  //the graph is symmetric, we can just do it this way
  for ( unsigned int i = 0; i < numCities; i++ )
  {
    //Grabs the next line to work with, only if the next line exists
    if ( !is.eof() )
      getline( is, currLine );
      
    //cout << "i = " << i << endl;
    //cout << "  " << currLine << endl;
    //Breaks up the current line, delimited by a space
    currSet = str_breakup( currLine, " " );
    
    //Grabs each piece of the current set of items, turns them into doubles
    //Then stores them in the appropriate spot in the matrix
    for ( unsigned long int j = 0; j < M.width(); j++ )
    {
      //cout << "  j = " << j << endl;
      M[i][j] = str_to_double( currSet[j] );
    }

    
  }
  
  return is;
}

template <typename T>
bool Matrix<T>::closeTo( const T& value, const T& target, const T& tolerance )
{
        //within upper bound                  //within lower bound
  if ( ( value < ( target + tolerance ) ) && ( value > ( target - tolerance ) ) )
    return true;
  return false;
}

// END OF FILE ----------------------------------------------------------------
