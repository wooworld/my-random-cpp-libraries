//////////////////////////////////////////////////////////////////////
/// @file snode.hpp
/// @author Jeremy Davidson
/// @brief Generic single-linked node
//////////////////////////////////////////////////////////////////////

#ifndef SNODE_H
#define SNODE_H

template <class Generic>
struct Snode {

  Snode<Generic> * forward;
  
  Generic data;
  
};

#endif
