// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file Vector.h
/// @author Gary Steelman
/// @edit 5 Nov 2009
/// @brief Contains declaraions for the Vector
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @class Vector 
/// @brief Contains functionality for a Vector object and performing oprations
///   on it. 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector()
/// @brief Default constructor for the Vector object.
/// @pre A constructor for type T exists. 
/// @post Creates a Vector object with size 0. 
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector( const unsigned int& n, T to_fill = T() )
/// @brief A constructor that creates a Vector of size n and fills each element
///   with the value to_fill.
/// @pre A constructor for type T exists. 
/// @pre The assignment operator (=) is defined for type T.
/// @param const int& n - The desired size for the Vector object.
/// @param const T& to_fill - The desired value for each element of the Vector.
/// @post Creates a Vector object with size n and each element = to to_fill.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn ~Vector
/// @brief Destructor for the Vector class.
/// @pre A Vector object exists. 
/// @post Frees the memory used by the Vector object.
/// @return N/A.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn unsigned long int size() const
/// @brief Returns the number of elements occupied in the Vector object.
/// @pre A Vector object exists.
/// @post Returns the number of elements occupied in the Vector object.
/// @return unsigned long int: the number of elements occupied in the Vector
///   object.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn unsigned long int max_size() const 
/// @brief Returns the max number of elements available to the Vector object.
/// @pre A Vector object exists.
/// @post Returns the max number of elements available to the Vector object.
/// @return unsigned long int: the max number of elements available to
///   the Vector object.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn push_back( const T& to_push )
/// @brief Appends to_push to the end of the Vector.
/// @pre A Vector object exists.
/// @pre The assignment operator (=) is defined for type T.
/// @param const T& to_push - The object to append to the Vector. 
/// @post Appends to_push to the end of the Vector. 
/// @return None. 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn pop_back()
/// @brief Removes the last element in the Vector.
/// @pre A Vector object exists and has at least 1 element in it.
/// @post Removes the last element in the Vector. 
/// @return None.
/// @throw Exception(1, "Attempted to pop an empty vector.")
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn clear()
/// @brief Clears all data in the Vector, resetting it to default values.
/// @pre A Vector object exists.
/// @post Clears all data in the Vector, resetting it to default as if it were
///   just constructed. 
/// @return None. 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool empty() const
/// @brief Returns true if the Vector is empty, false otherwise.
/// @pre A Vector object exists.
/// @post Returns true if the Vector is empty, false otherwise.
/// @return bool: true if the Vector is empty.
/// @return bool: false if the Vector is not empty.

///////////////////////////////////////////////////////////////////////////////
/// @fn T& operator[]( const unsigned long int& n )
/// @brief Returns a reference to element n of the Vector object. 
/// @pre A Vector object exists.
/// @pre The nth element of the Vector object exists. 
/// @param const int& n - The element to return the value of.
/// @post Returns a reference to element n in the Vector object. 
/// @return T&: the nth element of the Vector.
/// @throw Exception( 2, "Out of bounds access. Vector operator[]." )
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn const T& operator[]( const unsigned long int& n ) const
/// @brief Returns a reference to element n of the Vector object. 
/// @pre A Vector object exists.
/// @pre The nth element of the Vector object exists. 
/// @param const int& n - The element to return the value of.
/// @post Returns a reference to element n in the Vector object. 
/// @return T&: the nth element of the Vector.
/// @throw Exception( 2, "Out of bounds access. Vector operator[]." )
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T>& operator=( const Vector<T>& rhs )
/// @brief Sets the calling Vector object's values equal to right hand side's.
/// @pre Vector object rhs exists.
/// @param const Vector<T>& rhs - The Vector to set equal to. 
/// @post Sets the calling Vector object's values equal to right hand side's.
/// @return Vector<T>&: The edited calling object's address.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T>& operator=(  const std::vector<T>& rhs )
/// @brief Converts a STL vector to a Vector
/// @pre vector object rhs exists.
/// @param const vector<T>& rhs - The vector to set equal to. 
/// @post Sets the calling Vector object's values equal to right hand side's.
/// @return Vector<T>&: The edited calling object's address.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn set_size( const unsigned int& n, T c = T() )
/// @brief Changes the size of the calling Vector to n. Fills extra spaces with
///   c.
/// @pre A constructor for type T exists. 
/// @pre A Vector object exists.
/// @param const unsigned int& n - The size to change the Vector to.
/// @param T c - The object to fill extra spaces with if changing the size of
///   the vector to greater than the current size. 
/// @post Changes the size of the Vector to n and fills extra spaces with c.
/// @return None.
/// @note If decreasing the size of the vector, c is ignored.
/// @note If increasing the size of the vector, fills all indexes created past
///   current size() with c.
/// @note c can be specified OR c can be omitted and will just fill the indexes
///   with a default T. 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn friend std::ostream& operator<< <>( std::ostream& os, const Vector<T>& v )
/// @brief The output stream operator for the Vector class. 
/// @pre A Vector object exists. 
/// @param ostream& os is the left hand side of the operator, the stream to be
///   output to
/// @param const Vector& v is the right hand side of the op, the polarNum to
///   be output
/// @return A stream containing each element of v, in order, separated by a
///   newline character ( \n ).
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn friend std::istream& operator>> <>( std::istream& is, Vector<T>& v );
/// @brief The intput stream operator for the Vector class. 
/// @pre A Vector object exists. 
/// @pre The assignment operator is defined and functional for type istream
///   to type T.
/// @param istream& is is the left hand side of the operator, the stream to be
///   input from
/// @param Vector& v is the right hand side of the op, the polarNum to
///   be inputted to
/// @return A stream object containing the data to be intput to the polarNum
/// @note Puts the data from is into each element of v. Every element will
///   contain is. 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T> operator+( const Vector<T>& rhs )
/// @brief Adds two Vector objects together.
/// @pre The addition (+) operator is defined for type T.
/// @pre The dimensions (size()) of the two vectors are the same. 
/// @param const Vector<T>& rhs - The right hand side vector.
/// @post Adds two Vector objects together. 
/// @return Vector<T>: The result of the addition.
/// @throw Exception( 3, "Size mismatch. Vector operator+()." )
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T>& operator+=( const Vector<T>& rhs )
/// @brief Adds one vector to another. 
/// @pre The addition (+) operator is defined for type T.
/// @pre The dimensions (size()) of the two vectors are the same. 
/// @param const Vector<T>& rhs - The right hand side vector.
/// @post Adds one vector to the other. 
/// @return Vector<T>&: The result of the addition.
/// @throw Exception( 3, "Size mismatch. Vector operator+=()." )
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T> operator-( const Vector<T>& rhs )
/// @brief Subtracts two Vector objects together.
/// @pre The subtraction (-) operator is defined for type T.
/// @pre The dimensions (size()) of the two vectors are the same. 
/// @param const Vector<T>& rhs - The right hand side vector.
/// @post Subtracts two Vector objects together. 
/// @return Vector<T>: The result of the subtraction.
/// @throw Exception( 3, "Size mismatch. Vector operator-()." )
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T>& operator-=( const Vector<T>& rhs )
/// @brief Subtracts two Vector to another. 
/// @pre The subtraction (-) operator is defined for type T.
/// @pre The dimensions (size()) of the two vectors are the same. 
/// @param const Vector<T>& rhs - The right hand side vector.
/// @post Subtracts one vector to the other. 
/// @return Vector<T>&: The result of the subtraction.
/// @throw Exception( 3, "Size mismatch. Vector operator-=()." )
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T> operator*( const Vector<T>& rhs )
/// @brief Multiplies two Vector objects together.
/// @pre The multiplication (*) operator is defined for type T.
/// @pre The dimensions (size()) of the two vectors are the same. 
/// @param const Vector<T>& rhs - The right hand side vector.
/// @post Multiplies two Vector objects together. 
/// @return Vector<T>: The result of the multiplication.
/// @throw Exception( 3, "Size mismatch. Vector operator*()." )
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T>& operator*=( const Vector<T>& rhs )
/// @brief Multiplies two Vectors together. 
/// @pre The multiplication (*) operator is defined for type T.
/// @pre The dimensions (size()) of the two vectors are the same. 
/// @param const Vector<T>& rhs - The right hand side vector.
/// @post Multiplies one vector to the other. 
/// @return Vector<T>&: The result of the multiplication.
/// @throw Exception( 3, "Size mismatch. Vector operator*=()." )
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T> operator/( const Vector<T>& rhs )
/// @brief Divides two Vector objects together.
/// @pre The division (/) operator is defined for type T.
/// @pre The dimensions (size()) of the two vectors are the same. 
/// @param const Vector<T>& rhs - The right hand side vector.
/// @post Divides two Vector objects together. 
/// @return Vector<T>: The result of the division.
/// @throw Exception( 3, "Size mismatch. Vector operator/()." )
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T>& operator/=( const Vector<T>& rhs )
/// @brief Divides two Vectors together. 
/// @pre The division (/) operator is defined for type T.
/// @pre The dimensions (size()) of the two vectors are the same. 
/// @param const Vector<T>& rhs - The right hand side vector.
/// @post Divides one vector to the other. 
/// @return Vector<T>&: The result of the division.
/// @throw Exception( 3, "Size mismatch. Vector operator/=()." )
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T>& operator~()
/// @brief The reset operator. Resets all indexes to their default T constructor
///   values. 
/// @pre The constructor for type T exists. 
/// @post Resets all values in the vector to their default constructor values. 
/// @return Vector<T>&: The reset vector.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Vector<T>& set_all( const T& set_to )
/// @brief Sets all values in the Vector to set_to
/// @pre A Vector object exists.
/// @pre set_to is of the same type as the Vector. 
/// @param const T& set_to - The value to set all values in the Vector to
/// @post Sets all values in the Vector to set_to
/// @return Vector<T>&: The edited vector.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool operator==( const Vector<T>& rhs ) const
/// @brief Returns true if all values in the 2 vectors are equal. Else false.
/// @pre The == operator is defined for type T. 
/// @pre The dimensions (size()) of the two vectors are the same. 
/// @param const Vector<T>& rhs - The right hand side vector.
/// @post Returns true if all values in the 2 vectors are equal. Else false.
/// @return bool: true if all values in both vectors are equal.
/// @return bool: false if not all values in both vectors are equal. 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn bool operator!=( const Vector<T>& rhs ) const
/// @brief Returns true if all values in the 2 vectors are not equal. Else false.
/// @pre The == operator is defined for type T. 
/// @pre The dimensions (size()) of the two vectors are the same. 
/// @param const Vector<T>& rhs - The right hand side vector.
/// @post Returns true if all values in the 2 vectors are not equal. Else false.
/// @return bool: true if all values in both vectors are not equal.
/// @return bool: false if not all values in both vectors are equal. 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn T innerProduct( const Vector<T>& lhs, const Vector<T>& rhs )
/// @brief Calculates the inner product (dot product) of lhs and rhs.
/// @pre The + operator is defined for type T.
/// @pre the = operator is defined for type T.
/// @param const Vector<T>& lhs - The first Vector.
/// @param const Vector<T>& rhs - The second Vector.
/// @post Returns the inner product of the 2 Vectors.
/// @return T - The The value of the inner product of the 2 Vectors. 
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @throws 
/// Exception( 1, "Attempted to pop an empty vector." )
/// Exception( 2, "Out of bounds access. Vector operator[]." )
/// Exception( 3, "Size mismatch. Vector <operator>." )
///////////////////////////////////////////////////////////////////////////////

#pragma once //Ensures this file is only included once during compilation
#include <iostream>
#include <vector>

template <class T>
class Vector;

template <typename T>
std::ostream& operator<<( std::ostream& os, const Vector<T>& v );

template <typename T>
std::istream& operator>>( std::istream& is, Vector<T>& v );

template <typename T>
T innerProduct( const Vector<T>& lhs, const Vector<T>& rhs );

template <typename T>
Vector<T> absolute( const Vector<T>& v );

template <class T>
class Vector
{
  public:
    Vector(); 
    Vector( const unsigned int&n, T to_fill ); 
    Vector( const Vector<T>& v ); 
    ~Vector(); 
    
    unsigned long int size() const; 
    unsigned long int max_size() const; 
    void set_size( const unsigned int& n, T c );
    
    void push_back( const T& to_push ); 
    void pop_back(); 
    void insert( const unsigned long int& n, const T& to_insert );
    void remove( const unsigned long int& n );
    void clear(); 
    bool empty() const; 
    
    T max( const unsigned long int& start, const unsigned long int& end ) const;
    T min( const unsigned long int& start, const unsigned long int& end ) const;
    T max_index( const unsigned long int& start, const unsigned long int& end ) const;
    T min_index( const unsigned long int& start, const unsigned long int& end ) const;
    
    const T& operator[]( const unsigned long int& n ) const; 
    T& operator[]( const unsigned long int& n ); 
    
    Vector<T>& operator=(  const Vector<T>& rhs ); 
    Vector<T>& operator=(  const std::vector<T>& rhs );
    Vector<T>  operator+(  const Vector<T>& rhs ); 
    Vector<T>& operator+=( const Vector<T>& rhs ); 
    Vector<T>  operator-(  const Vector<T>& rhs ); 
    Vector<T>& operator-=( const Vector<T>& rhs ); 
    Vector<T>  operator*(  const Vector<T>& rhs ); 
    Vector<T>  scale( const T& rhs );
    Vector<T>& operator*=( const Vector<T>& rhs ); 
    Vector<T>  operator/(  const Vector<T>& rhs ); 
    Vector<T>& operator/=( const Vector<T>& rhs ); 
    
    Vector<T>& operator~(); 
    Vector<T>& set_all( const T& set_to );
    
    bool operator==( const Vector<T>& rhs ) const;
    bool operator!=( const Vector<T>& rhs ) const;
    
    friend std::ostream& operator<< <>( std::ostream& os, const Vector<T>& v ); 
    friend std::istream& operator>> <>( std::istream& is, Vector<T>& v ); 

  private:
    unsigned long int m_size;
    unsigned long int m_max_size;
    T * m_data;
};

#include "vector.hpp"
// END OF FILE ----------------------------------------------------------------
