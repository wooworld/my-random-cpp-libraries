// BEGINNING OF FILE ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/// @auth Gary Steelman
/// @file bubblesort.h
/// @edit 4 Oct 2009
/// @brief Contains the function definition and declaration for a bubble sort.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn void bubbleSort( T& source, const C& size )
/// @brief Sorts array of size C from least to greatest
/// @pre Source has elements of value in all spots up to size
/// @pre Operator > is defined for type T.
/// @pre Operator = (assignment) is defined for type T.
/// @pre C <= size of source.
/// @param T& source - The array to sort.
/// @param const C& size - The size of parameter source.
/// @post Sorts source from least to greatest.
/// @return None. 
/// @note This is a really slow sorting algorithm, please use a different one.
///////////////////////////////////////////////////////////////////////////////

template<typename T, typename C>
void bubbleSort( T& source, const C& size ) 
{
	T temp = 0, x = 0, y = 0;
  
	for (unsigned int i = 0; i < size; i++) 
  {
		for (unsigned int j = 0; j < size; j++) 
    {
			if (source[j] > source[j + 1])
			{	
				x = source[j];
				y = source[j + 1];
				temp = x;
				x = y;
				y = temp;
			}
		}
	}
  
	return;
}

// END OF FILE ----------------------------------------------------------------
