// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @auth Gary Steelman
/// @file matrix.h
/// @edit 13 Nov 2009
/// @brief Contains the declarations for the Matrix class
/// @note Row and column addressing and indexing start at number 0, not 1
///   Therefore to get the first row of data, do get_row(0)
///   Or to get the very top-left element of the Matrix, matrix[0][0]
/// @note Column operations are slightly slower than row operations. 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @class Matrix<T>
/// @brief Creates a Matrix object of the specified type and contains
///   functionality for doing matrix operations on a Matrix object.
/// @note The majority of these functions work just like you would expect them
///   to for a mathematical matrix. 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Matrix()
/// @brief The default constructor for the Matrix class. 
/// @pre Type T must exist.
/// @post Creates a Matrix object of size 0x0.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrix( const unsigned long int& rows, const unsigned long int& cols )
/// @brief Creates a Matrix of the specified number of rows and columns.
/// @pre Type T must exist. 
/// @pre Type T must have a default constructor.
/// @pre Type T must have an assignment (=) operator. 
/// @param const unisgned long int& rows -- The number of rows to have.
/// @param const unsigned long int& cols -- The number of columns to have.
/// @post Creates a Matrix of the specified dimension, filling each element.
///   with a default T.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrix( const Vector<T>& v )
/// @brief Creates a single column Matrix from the Vector.
/// @pre Type T is defined.
/// @pre Type T must have a default constructor. 
/// @pre Type T for parameter and for Matrix must match.
/// @pre Type T must have an assignment (=) operator.
/// @param const Vector<T>& v -- The Vector to create a 1-column Matrix from
/// @post Creates a 1 column Matrix containing the same data as v.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrix( const Vector<Vector<T> >& v )
/// @brief Creates a Matrix object from the Vector of Vectors.
/// @pre Type T is defined.
/// @pre Type T must have a default constructor. 
/// @pre Type T for parameter and for Matrix must match.
/// @pre Type T must have an assignment (=) operator.
/// @pre Each index of v must contain the same number of elements and each 
///   element must be defined.
/// @param const Vector<Vector<T> >& v -- The Vector of Vectors to turn into
///   a Matrix. The inner Vectors must contain the row data. That is, v[0] is
///   row 0, v[1] is row 1 and each row must contain a single element in each
///   position. 
/// @post Creates a Matrix object from the Vector of Vectors.
/// @return N/A.
/// @note The Matrix copies v[0][0] to Matrix[0][0], v[0][1] to Matrix[0][1]
///   and continues until all rows are filled. 
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrix( const File& f )
/// @brief Creates a Matrix from f's data.
/// @pre f contains data in the specified format.
/// @param const File& f -- The File to create a Matrix from.
/// @post Creates a Matrix from f's data. 
/// @return N/A.
/// @note Automatically converts File data to type <double> when creating Matrix
///   Therefore this only works with a Matrix<double> object!
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrix( const Matrix<T>& M )
/// @brief The copy constructor for a Matrix object. 
/// @pre M exists.
/// @pre Type T is defined.
/// @pre Type T must have a default constructor. 
/// @pre Type T for parameter and for Matrix must match.
/// @pre Type T must have an assignment (=) operator.
/// @param const Matrix<T>& M -- The Matrix to copy.
/// @post Copies M into the calling object.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////
/// @fn ~Matrix()
/// @brief The default destructor for a Matrix object. 
/// @pre A Matrix object exists.
/// @post Destroys a Matrix object.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////
/// @fn unsigned long int width() const
/// @brief Returns the number of columns, or width, of the Matrix
/// @pre A Matrix object exists.
/// @post Returns the number of columns in the Matrix.
/// @return unsigned long int -- The number of columns in the Matrix. 
///////////////////////////////////////////////////////////////////////////////
/// @fn unsigned long int height() const
/// @brief Returns the number of rows, or height, of the Matrix
/// @pre A Matrix object exists.
/// @post Returns the number of rows in the Matrix.
/// @return unsigned long int -- The number of rows in the Matrix. 
///////////////////////////////////////////////////////////////////////////////
/// @fn unsigned long int size() const
/// @brief Returns the number of elements in the Matrix.
/// @pre A Matrix object exists.
/// @post Returns the number of elements in the Matrix.
/// @return unsigned long int -- The number of elements in the Matrix. 
/// @note This number is width()*height().
///////////////////////////////////////////////////////////////////////////////
/// @fn void set_width( const unsigned long int& n )
/// @brief Sets the width of the Matrix to n.
/// @pre A Matrix object exists.
/// @pre Type T is defined.
/// @pre Type T must have an assignment (=) operator.
/// @pre Type T must have a default constructor. 
/// @param const unsigned long int& n -- The number of columns to make the 
///   Matrix have. 
/// @post Sets the width of the Matrix to n.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void set_height( const unsigned long int& n )
/// @brief Sets the height of the Matrix to n.
/// @pre A Matrix object exists.
/// @pre Type T is defined.
/// @pre Type T must have an assignment (=) operator.
/// @pre Type T must have a default constructor. 
/// @param const unsigned long int& n -- The number of rows to make the 
///   Matrix have. 
/// @post Sets the height of the Matrix to n.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void set_all( const T& to_set )
/// @brief Sets all elements of the Matrix to to_set.
/// @pre A Matrix object must exist. 
/// @pre Type T is defined.
/// @pre Type T for parameter and for Matrix must match.
/// @pre Type T must have an assignment (=) operator.
/// @param const T& to_set -- The value to set all elements in the Matrix to.
/// @post Sets all elements of the Matrix to to_set.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T> get_row( const unsigned long int& n )
/// @brief Returns a Vector containing all of the elements in row n.
/// @pre Type T is defined.
/// @pre A Matrix object must exist.
/// @param const unsigned long int& n --  The row number to get. 
/// @post Returns a Vector containing all of the elements in row n.
/// @return Vector<T> -- The Vector containing all elements of row n.
///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T> get_col( const unsigned long int& n )
/// @brief Returns a Vector containing all of the elements in column n.
/// @pre Type T is defined.
/// @pre A Matrix object must exist.
/// @param const unsigned long int& n --  The column number to get. 
/// @post Returns a Vector containing all of the elements in column n.
/// @return Vector<T> -- The Vector containing all elements of column n.
///////////////////////////////////////////////////////////////////////////////
/// @fn void set_row( const unsinged long int& n, const T& to_set )
/// @brief Sets all elements of row n to to_set.
/// @pre A Matrix object must exist. 
/// @pre Type T is defined.
/// @pre Type T for parameter and for Matrix must match.
/// @pre Type T must have an assignment (=) operator.
/// @param const unsigned long int& n -- The row to set all elements to to_set.
/// @param const T& to_set -- The value to set all elements of row n to.
/// @post Sets all elements of row n to to_set.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void set_col( const unsinged long int& n, const T& to_set )
/// @brief Sets all elements of column n to to_set.
/// @pre A Matrix object must exist. 
/// @pre Type T is defined.
/// @pre Type T for parameter and for Matrix must match.
/// @pre Type T must have an assignment (=) operator.
/// @param const unsigned long int& n -- The column to set all elements to to_set.
/// @param const T& to_set -- The value to set all elements of column n to.
/// @post Sets all elements of column n to to_set.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void set_row( const unsinged long int& n, const Vector<T>& to_set )
/// @brief Sets row n equal to to_set. 
/// @pre A Matrix object must exist. 
/// @pre Type T is defined.
/// @pre to_set.size() == width().
/// @pre Type T for parameter and for Matrix must match.
/// @pre Type T must have an assignment (=) operator.
/// @param const unsigned long int& n -- The row to set to to_set.
/// @param const Vector<T>& to_set -- The Vector to store in row n.
/// @post Sets row n equal to to_set. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void set_col( const unsinged long int& n, const Vector<T>& to_set )
/// @brief Sets column n equal to to_set. 
/// @pre A Matrix object must exist. 
/// @pre Type T is defined.
/// @pre to_set.size() == height().
/// @pre Type T for parameter and for Matrix must match.
/// @pre Type T must have an assignment (=) operator.
/// @param const unsigned long int& n -- The column to set to to_set.
/// @param const Vector<T>& to_set -- The Vector to store in column n.
/// @post Sets column n equal to to_set. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void insert_row( const unsigned long int& loc, const Vector<T>& v )
/// @brief Inserts v into the Matrix at row loc.
/// @pre A Matrix object must exist. 
/// @pre Type T is defined.
/// @pre to_set.size() == width().
/// @pre Type T for parameter and for Matrix must match.
/// @pre Type T must have an assignment (=) operator.
/// @param const unsigned long int& loc -- The row to insert at. 
/// @param const Vector<T>& v -- The Vector to store in row loc.
/// @post Inserts v into the Matrix at row loc.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void insert_col( const unsigned long int& loc, const Vector<T>& v )
/// @brief Inserts v into the Matrix at column loc.
/// @pre A Matrix object must exist. 
/// @pre Type T is defined.
/// @pre to_set.size() == height().
/// @pre Type T for parameter and for Matrix must match.
/// @pre Type T must have an assignment (=) operator.
/// @param const unsigned long int& loc -- The column to insert at. 
/// @param const Vector<T>& v -- The Vector to store in column loc.
/// @post Inserts v into the Matrix at column loc.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void delete_row( const unsigned long int& loc )
/// @brief Deletes row loc from the Matrix. 
/// @pre Type T must have an assignment (=) operator.
/// @param const unsigned long int& loc -- The row number to delete. 
/// @post Deletes row loc from the Matrix. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void delete_col( const unsigned long int& loc )
/// @brief Deletes column loc from the Matrix. 
/// @pre Type T must have an assignment (=) operator.
/// @param const unsigned long int& loc -- The column number to delete. 
/// @post Deletes column loc from the Matrix. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void swap_row( const unsigned long int& first, 
///                    const unsigned long int& second )
/// @brief Swaps the 2 specified rows.
/// @pre Type T must have an assignment (=) operator.
/// @pre Type T must have a default constructor. 
/// @param const unsigned long int& first -- The row number of the first row.
/// @param const unsigned long int& second -- The row number of the second row.
/// @post Swaps the 2 specified rows. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void swap_col( const unsigned long int& first, 
///                    const unsigned long int& second )
/// @brief Swaps the 2 specified columns.
/// @pre Type T must have an assignment (=) operator.
/// @pre Type T must have a default constructor. 
/// @param const unsigned long int& first -- The row number of the first column.
/// @param const unsigned long int& second -- The row number of the second column.
/// @post Swaps the 2 specified columns. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void app_row( const Vector<T>& v )
/// @brief Appends v as a row to the Matrix.
/// @pre Type T must have an assignment (=) operator.
/// @pre Type T must have a default constructor. 
/// @pre v.size() == width().
/// @param const Vector<T>& v -- The row to append to the Matrix.
/// @post Appens v as a row to the Matrix. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void app_col( const Vector<T>& v )
/// @brief Appends v as a column to the Matrix.
/// @pre Type T must have an assignment (=) operator.
/// @pre Type T must have a default constructor. 
/// @pre v.size() == height().
/// @param const Vector<T>& v -- The column to append to the Matrix.
/// @post Appens v as a column to the Matrix. 
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void ref()
/// @brief Reduces the Matrix to Reduced Echelon Form.
/// @pre Type T must have an assignment (=) operator. 
/// @pre Type T must have a multiplication (*) operator.
/// @pre Type T must have an addition (+) operator.
/// @post Reduces the Matrix to Reduced Echelon Form.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn void rref()
/// @brief Reduces the Matrix to Row Reduced Echelon Form.
/// @pre Type T must have an assignment (=) operator. 
/// @pre Type T must have a multiplication (*) operator.
/// @pre Type T must have an addition (+) operator.
/// @post Reduces the Matrix to Row Reduced Echelon Form.
/// @return None.
///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T>& operator[]( const unsigned long int& n )
/// @brief Returns the row at index n.
/// @pre A Matrix ojbect exists.
/// @param const unsigned long int& n -- The row number to return.
/// @post Returns the row at index n.
/// @return Vector<T>& -- The row at index n.
/// @note The const version of this operator performs the same functions.
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrx<T>& operator=( const Matrix<T>& rhs )
/// @brief Sets the calling object equal to rhs. 
/// @pre A Matrix ojbect exists.
/// @pre Type T has an assignment (=) operator. 
/// @param const Matrix<T>& rhs -- The right hand side of the operator =.
/// @post Sets the calling object equal to rhs. 
/// @return Matrix<T>& -- The result of the operation.
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrx<T> operator+( const Matrix<T>& rhs )
/// @brief Adds rhs and the calling object. 
/// @pre A Matrix ojbect exists.
/// @pre Type T has an assignment (=) operator. 
/// @pre Type T has an addition (+) operator. 
/// @param const Matrix<T>& rhs -- The right hand side of the operator +.
/// @post Adds rhs and the calling ojbect. 
/// @return Matrix<T> -- The result of the operation.
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrx<T>& operator+=( const Matrix<T>& rhs )
/// @brief Adds rhs to the calling object. 
/// @pre A Matrix ojbect exists.
/// @pre Type T has an assignment (=) operator. 
/// @pre Type T has an addition (+) operator. 
/// @param const Matrix<T>& rhs -- The right hand side of the operator +=.
/// @post Adds rhs to the calling object. 
/// @return Matrix<T>& -- The result of the operation.
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrx<T> operator-( const Matrix<T>& rhs )
/// @brief Subtracts rhs and the calling object. 
/// @pre A Matrix ojbect exists.
/// @pre Type T has an assignment (=) operator. 
/// @pre Type T has an addition (-) operator. 
/// @param const Matrix<T>& rhs -- The right hand side of the operator -.
/// @post Subtracts rhs and the calling ojbect. 
/// @return Matrix<T> -- The result of the operation.
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrx<T>& operator-=( const Matrix<T>& rhs )
/// @brief Subtracts rhs from the calling object. 
/// @pre A Matrix ojbect exists.
/// @pre Type T has an assignment (=) operator. 
/// @pre Type T has an addition (-) operator. 
/// @param const Matrix<T>& rhs -- The right hand side of the operator -=.
/// @post Subtracts rhs from the calling object. 
/// @return Matrix<T>& -- The result of the operation.
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrx<T> operator*( const Matrix<T>& rhs )
/// @brief Multiplies rhs and the calling object. 
/// @pre A Matrix ojbect exists.
/// @pre Type T has an assignment (=) operator. 
/// @pre Type T has an multiplication (*) operator. 
/// @param const Matrix<T>& rhs -- The right hand side of the operator *.
/// @post Multiplies rhs and the calling ojbect. 
/// @return Matrix<T> -- The result of the operation.
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrx<T>& operator*=( const Matrix<T>& rhs )
/// @brief Multiplies rhs into the calling object. 
/// @pre A Matrix ojbect exists.
/// @pre Type T has an assignment (=) operator. 
/// @pre Type T has an multication (*) operator. 
/// @param const Matrix<T>& rhs -- The right hand side of the operator *=.
/// @post Multiplies rhs into the calling object. 
/// @return Matrix<T>& -- The result of the operation.
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrx<T> operator*( const Vector<T>& rhs )
/// @brief Multiplies rhs and the calling object. 
/// @pre A Matrix ojbect exists.
/// @pre Type T has an assignment (=) operator. 
/// @pre Type T has an multiplication (*) operator. 
/// @param const Vector<T>& rhs -- The right hand side of the operator *.
/// @post Multiplies rhs and the calling ojbect. 
/// @return Matrix<T> -- The result of the operation.
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrx<T>& operator*=( const Vector<T>& rhs )
/// @brief Multiplies rhs into the calling object. 
/// @pre A Matrix ojbect exists.
/// @pre Type T has an assignment (=) operator. 
/// @pre Type T has an multiplication (*) operator. 
/// @param const Vector<T>& rhs -- The right hand side of the operator *=.
/// @post Multiplies rhs into the calling object. 
/// @return Matrix<T>& -- The result of the operation.
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrix<T> operator*( const T& rhs )
/// @brief Multiples the Matrix by rhs.
/// @pre A Matrix ojbect exists.
/// @pre Type T has an assignment (=) operator. 
/// @pre Type T has an mulitplication (*) operator. 
/// @param const T& rhs -- The right hand side of the operator *.
/// @post Multiplies rhs into the calling object. 
/// @return Matrix<T> -- The result of the operation.
///////////////////////////////////////////////////////////////////////////////
/// @fn Matix<T> scale( const T& scalar )
/// @brief Multiplies all elements in the Matrix by scalar. 
/// @pre A Matrix ojbect exists.
/// @pre Type T has an assignment (=) operator. 
/// @pre Type T has an multiplication (*) operator. 
/// @param const T& rhs -- The number to scale by. 
/// @post Multiplies rhs into the calling object. 
/// @return Matrix<T> -- The result of the operation.
///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T> scale_row( const unsigned long int& loc, const T& scalar )
/// @brief Multiplies all elements in row loc by scalar.
/// @pre Type T has an assignment (=) operator. 
/// @pre Type T has an multiplication (*) operator. 
/// @pre Type T for parameter and for Matrix must match.
/// @param const unsigned long int& loc -- The row to multiply.
/// @param const T& scalar -- The number to multiply the row by.
/// @post Multiplies all elements in row loc by scalar.
/// @return Vector<T> -- The result of the operation.
///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T> scale_col( const unsigned long int& loc, const T& scalar )
/// @brief Multiplies all elements in column loc by scalar.
/// @pre Type T has an assignment (=) operator. 
/// @pre Type T has an multiplication (*) operator. 
/// @pre Type T for parameter and for Matrix must match.
/// @param const unsigned long int& loc -- The column to multiply.
/// @param const T& scalar -- The number to multiply the column by.
/// @post Multiplies all elements in column loc by scalar.
/// @return Vector<T> -- The result of the operation.
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrix<T>& operator~()
/// @brief Sets all elements in the Matrix to default T values. 
/// @pre Type T has an assignment (=) operator.
/// @pre Type T must have a default constructor. 
/// @post Sets all elements in the Matrix to default T values. 
/// @return Matrix<T>& -- The result of the operation. 
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrix<T> operator-()
/// @brief Negates all elements in the Matrix.
/// @pre Type T has an assignment (=) operator.
/// @pre Type T has a multiplication (*) operator. 
/// @pre Type T must accept multiplication by -1 as a valid operation.
/// @post Negates all elements in the Matrix.
/// @return Matrix<T> -- The result of the operation. 
/// @note Negation here just means "multiply by -1"
///////////////////////////////////////////////////////////////////////////////
/// @fn Matrix<T> operator!()
/// @brief Takes the transpose of the calling object. 
/// @pre Type T has an assignment (=) operator.
/// @post Returns the transpose of the calling object. 
/// @return Matrix<T> -- The transpose of the calling object.
///////////////////////////////////////////////////////////////////////////////
/// @fn bool operator==( const Matrix<T>& rhs ) const
/// @brief Returns true if rhs is equal to the calling object. False otherwise.
/// @pre Type T has an equality (==) operator. 
/// @param const Matrix<T>& rhs -- The right hand side of the == operator.
/// @post Returns true if rhs == calling object.
/// @return bool -- True is all elements in rhs are equal to the calling obj's.
/// @return bool -- False if not all elements in rhs are equal to the calling obj's.
///////////////////////////////////////////////////////////////////////////////
/// @fn bool operator!=( const Matrix<T>& rhs ) const
/// @brief Returns false if rhs is equal to the calling object. True otherwise.
/// @pre Type T has an equality (==) operator. 
/// @param const Matrix<T>& rhs -- The right hand side of the != operator.
/// @post Returns true if rhs != calling object.
/// @return bool -- False is all elements in rhs are equal to the calling obj's.
/// @return bool -- True if not all elements in rhs are equal to the calling obj's.
///////////////////////////////////////////////////////////////////////////////
/// @fn std::ostream& operator<<( std::ostream& os, const Matrix<T>& M )
/// @brief The extraction operator for the Matrix object. 
/// @pre Type T has extraction (<<) defined.
/// @param std::ostream& os -- The output stream to modify with M.
/// @param const Matrix<T>& M -- The Matrix object to output.
/// @post Output M to the output stream.
/// @return The modified output stream.
///////////////////////////////////////////////////////////////////////////////
/// @fn std::istream& operator>>( std::istream& is, Matrix<T>& M )
/// @brief The insertion operator for the Matrix. 
/// @pre Type T for the Matrix is <double>.
/// @param std::istream& is -- The input stream to put into M.
/// @param Matrix<T>& M -- The Matrix to put is into.
/// @post Parses is into M.
/// @return The leftover istream object. 
/// @note There is a specific file format for reading a Matrix from a file:
///   size
///
///   row 1 numbers separated by 2 spaces
///   row 2 numbers separated by 2 spaces
///     ...
///   row n numbers separated by 2 spaces
///   
///   the right hand side of the matrix, each number separated by 2 spaces
///////////////////////////////////////////////////////////////////////////////
/// @fn bool closeTo( const T& value, const T& target, const T& tolerance )
/// @brief Returns true if value is withing tolerance range of target.
/// @pre Type T on all parameters is the same.
/// @pre Type T has subtraction (-) operator defined.
/// @pre Type T has addition (+) operator defined.
/// @pre Type T has greater than (>) operator defined.
/// @pre Type T has less than operator (<) defined. 
/// @param const T& value -- The current value you want to check.
/// @param const T& target -- The target value to see if value is close to.
/// @param const T& tolerance -- How far from target value can be while still
///   being close to target.
/// @post Returns true if value is withing tolerance range of target.
/// @return bool -- true if value is within tolerance range of target.
/// @return bool -- false if value is not within tolerance range of target.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @throws
///  Exception( 23, "Out of bounds access. Matrix::<function>" )
///   An attempt was made to access a row, column, or element that doesn't exist
///   in in the current bounds of the Matrix. 
///  Exception( 24, "Size mismatch. Matrix::<function>" )
///   An attempt was made to multiply one row, column, or element by another and
///   the sizes of the items didn't match.
///  Exception( 25, "Dimenion mismatch. Matrix::<function>" )
///   An attempt was made to multiply one Matrix or Vector by another and the
///   dimensions did not match. 
///////////////////////////////////////////////////////////////////////////////

#pragma once //Ensures this file is only included once during compilation
#include "vector.h"
#include "file.h"
#include <iostream>

//Pre-delcarations
template <class T>
class Matrix;

template <typename T>
std::ostream& operator<<( std::ostream& os, const Matrix<T>& M );

template <typename T>
std::istream& operator>>( std::istream& is, Matrix<T>& M );

template <class T>
class Matrix
{
  public:
    Matrix();
    Matrix( const unsigned long int& rows, const unsigned long int& cols );
    Matrix( const Vector<T>& v );
    Matrix( const Vector<Vector<T> >& v );
    Matrix( const File& f );
    Matrix( const Matrix<T>& m );
    ~Matrix();
    
    unsigned long int width() const;
    unsigned long int height() const;
    unsigned long int size() const;
    void set_width( const unsigned long int& n );
    void set_height( const unsigned long int& n );
    void set_all( const T& to_set );
    
    Vector<T> get_row( const unsigned long int& n ) const;
    Vector<T> get_col( const unsigned long int& n ) const;
    void set_row( const unsigned long int& n, const T& to_set );
    void set_col( const unsigned long int& n, const T& to_set );
    void set_row( const unsigned long int& n, const Vector<T>& to_set );
    void set_col( const unsigned long int& n, const Vector<T>& to_set );
    
    void insert_row( const unsigned long int& loc, const Vector<T>& v );
    void insert_col( const unsigned long int& loc, const Vector<T>& v );
    void delete_row( const unsigned long int& loc );
    void delete_col( const unsigned long int& loc );
    void swap_row(  const unsigned long int& first, 
                    const unsigned long int& second );
    void swap_col(  const unsigned long int& first, 
                    const unsigned long int& second );
    void app_row( const Vector<T>& v );
    void app_col( const Vector<T>& v );
    
    Matrix<T>& ref();
    Matrix<T>& rref();
    
    Vector<T>& operator[]( const unsigned long int& n );
    const Vector<T>& operator[]( const unsigned long int& n ) const;
    
    Matrix<T>& operator=(  const Matrix<T>& rhs ); 
    Matrix<T>  operator+(  const Matrix<T>& rhs ); 
    Matrix<T>& operator+=( const Matrix<T>& rhs ); 
    Matrix<T>  operator-(  const Matrix<T>& rhs ); 
    Matrix<T>& operator-=( const Matrix<T>& rhs ); 
    Matrix<T>  operator*(  const Matrix<T>& rhs ); 
    Matrix<T>& operator*=( const Matrix<T>& rhs );
    Matrix<T>  operator*(  const Vector<T>& rhs ); 
    Matrix<T>& operator*=( const Vector<T>& rhs );
    Matrix<T>  operator*(  const T& rhs );
    Matrix<T>& scale( const T& scalar );
    Vector<T> scale_row( const unsigned long int& loc, const T& scalar );
    Vector<T> scale_col( const unsigned long int& loc, const T& scalar );
    Matrix<T>& operator~();
    Matrix<T> operator-();
    Matrix<T> operator!();
    bool closeTo( const T& value, const T& target, const T& tolerance ); 
    
    bool operator==( const Matrix<T>& rhs ) const;
    bool operator!=( const Matrix<T>& rhs ) const;
    
    friend std::ostream& operator<< <>( std::ostream& os, const Matrix<T>& M );
    void print() const;
    friend std::istream& operator>> <>( std::istream& is, Matrix<T>& M );
  
  private:
    unsigned long int m_rows;   //The number of rows the Matrix has
    unsigned long int m_cols;   //The number of columsn the Matrix has
    Vector<Vector<T> > m_data;  //The data of the Matrix
    
};

#include "matrix.hpp"
// END OF FILE-----------------------------------------------------------------
