// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @file sort.h
/// @author Gary Steelman
/// @edit 20 Jan 2010
/// @brief Contains different sort functionality.
/// @note Uses my custom Vector class.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void bubble_sort( Vector<T>& v )
/// @brief Sorts v from minimum to maximum.
/// @pre v must exist.
/// @pre The > operator is defined for type T.
/// @pre The = operator is defined for type T.
/// @param Vector<T>& v - The Vetor to sort.
/// @post Sorts v from minimum to maximum.
/// @return None.
/// @throw None.
///////////////////////////////////////////////////////////////////////////////

#pragma once //Ensures this file is included only once during compilation
#include "Vector.h"

template <typename T>
void bubble_sort( Vector<T>& v);

template <typename T>
void select_sort( Vector<T>& v);

template <typename T>
void insertion_sort( Vector<T>& v);

template <typename T>
void quick_sort( Vector<T>& v);

template <typename T>
void merge_sort( Vector<T>& v);

template <typename T>
void quick_sort_r( Vector<T>& v);

template <typename T>
void merge_sort_r( Vector<T>& v);

#include "sort.hpp"
// END OF FILE ----------------------------------------------------------------