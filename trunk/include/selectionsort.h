// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @auth Gary Steelman
/// @file selectionsort.h
/// @edit 4 Oct 2009
/// @brief Contains the function definition and declaration for a bubble sort.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void selectSort( T& source, const C& size )
/// @brief Sorts array of size C from least to greatest
/// @pre Source has elements of value in all spots up to size
/// @pre Operator > is defined for type T.
/// @pre Operator < is defined for type T.
/// @pre Operator = (assignment) is defined for type T.
/// @pre C <= size of source.
/// @param T& source - The array to sort.
/// @param const C& size - The size of parameter source.
/// @post Sorts source from least to greatest.
/// @return None. 
/// @note This sort can actually sort from least to greatest or greatest to
///   least. Read the function comments in the actual code to see how to 
///   change it. 
/// @note This is a fairly slow sorting algorithm, please use a different one.
///////////////////////////////////////////////////////////////////////////////

template<typename T, typename C>
void selectSort( T& source, const C& size ) 
{
	int nextsmallest = 0, i = 0;
  
	for (i = 0; i < size; i++) 
  {
		int j, k = i;
		T min = source[i];
		
		for (j = i + 1; j < size; j++) 
    {
			//Change the following < to > for a greatest to least sort
			if (source[j] < min) 
      {
				min = array[j];
				k = j;
			}
		}
    
		nextsmallest = k;
		T temp = array[i];
		array[i] = array[nextsmallest];
		array[nextsmallest] = temp;
	}
}

// END OF FILE ----------------------------------------------------------------
