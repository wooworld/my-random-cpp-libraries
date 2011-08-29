///////////////////////////////////////////////////////////////////////////////
/// @file list.h
/// @author Gary Steelman, CS153-B
/// @edited 20 Feb 08
/// @brief list class definition file
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn List()
/// @brief Constructor for a List class
/// @pre None.
/// @post Instantiates a List class
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn ~List()
/// @brief Destructor for a List class
/// @pre A List class exists
/// @post Clears the memory for the List class
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn push_front( generic x )
/// @brief Pushes the passed parameter onto the front of the list
/// @pre x and the List it is being pushed onto are of the same datatype
/// @post The list now has the passed parameter in front of every other node
/// @param x is the value to be pushed onto the front of the List
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn pop_front()
/// @brief Pops the front of the list off
/// @pre A List class exists
/// @post Removes the first element from the list
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn push_back( generic x )
/// @brief Pushes the passed parameter onto the back of the list
/// @pre x and the List it is being pushed onto are of the same datatype
/// @post The list now has the passed parameter behind every other node
/// @param x is the value to be pushed onto the back of the List
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn pop_back()
/// @brief Pops the back of the list off
/// @pre A List class exists
/// @post Removes the last element from the list
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn remove( generic x )
/// @brief Removes the passed value from the list
/// @pre x and the List it is being pushed onto are of the same datatype
/// @post Removes the passed value from the list
/// @param x is the value to be removed from the list
/// @note This will only remove the first instance of the passed value from the
///   list
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn front()
/// @brief Returns the front value of the list
/// @pre A List class exists
/// @post Returns the front value of the list
/// @return The front value in the list
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn back()
/// @brief Returns the back value of the list
/// @pre A List class exists
/// @post Returns the back value of the list
/// @return The back value in the list
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn size()
/// @brief Returns the current size of the list
/// @pre A List class exists
/// @post Returns the current size of the list
/// @return Returns the current size of the list
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn clear()
/// @brief Empties the list
/// @pre A List class exists
/// @post Empties the list
/// @return None.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @fn empty()
/// @brief Returns whether or not the List is empty
/// @pre A List class exists
/// @post Returns whether or not the List is empty
/// @return True if the list is empty, false if otherwise
///////////////////////////////////////////////////////////////////////////////

#ifndef LIST_H
#define LIST_H

#include "exception.h"
#include "node.h"

template <class generic>
class List
{
  public:
    List();
    ~List();
    
    void push_front( generic x );
    void pop_front();
    
    void push_back( generic x );
    void pop_back();
    
    void remove( generic x );
    
    generic & front();
    generic & back();
    unsigned int size();
    
    void clear();
    bool empty();
    
  private:
    //The following int contains the value of this node
    unsigned int m_size;
    
    //Following pointer contains location of pointer to next node
    Node<generic> * m_front;
    
    //Following pointer contains location of pointer to previous node
    Node<generic> * m_back;
};

#include "list.hpp"

#endif
