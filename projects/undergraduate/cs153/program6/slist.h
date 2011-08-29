///////////////////////////////////////////////////////////////////////////////
/// @file slist.h
/// @author Gary Steelman, CS153-B
/// @edited 13 Feb 08
/// @brief Slist class prototype file
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn Slist
/// @brief the constructor for the Slist
/// @pre None.
/// @post creates an slist object
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn ~Slist
/// @brief the destructor for the Slist
/// @pre None.
/// @post destroys an slist object
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn push_front
/// @brief an Slist object exists
/// @pre x is of the same datatype as the list
/// @post adds the passed x to the front of the slist
/// @param x the object to be added to the slist's front
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn pop_front
/// @brief removes the first object in the slist
/// @pre An slist object of at least size 1 exists
/// @post removes the first object in the slist
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn remove
/// @brief removes the first instance of the passed value from the list
/// @pre an slist exists with the passed value in the list, x is of the same
///   datatype as the slist
/// @post removes the first instance of the passed value from the list
/// @param x the value to be removed from the slist
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn front
/// @brief returns the value of the first item in the slist
/// @pre an slist exists of at least size 1
/// @post returns the value of the first item in the slist
/// @return the value of the first item in the slist
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn clear
/// @brief clears out the list
/// @pre an slist object exists
/// @post deletes all values in the slist
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn size
/// @brief returns the size of the list currently
/// @pre an slist exists
/// @post returns the size of the list currently
/// @return returns the size of the list currently
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn empty
/// @brief returns whether or not the list is empty
/// @pre an slist exists
/// @post returns whether or not the list is empty
/// @return whether or not the list is empty
///////////////////////////////////////////////////////////////////////////////

#ifndef SLIST_H
#define SLIST_H

#include "exception.h"
#include "snode.h"

using namespace std;

template <class generic>
class Slist
{
  public:
    Slist();
    ~Slist();
    void push_front( generic x );
    void pop_front();
    void remove( generic x );
    generic & front();
    void clear();
    unsigned int size();
    bool empty();
    
  private:
    unsigned int m_size; ///The number of items in the list currently
    Snode<generic> * m_front; ///The part of the list that contains the pointer
};

#include "slist.hpp"

#endif
