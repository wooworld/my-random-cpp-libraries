#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include "dataset.h"
#include "dnode.h"
#include "d_tree_heuristic.h"

using namespace std;

template <class T>
DecisionTree<T>::DecisionTree() : m_size(0)
{
  m_root = NULL; 
  m_heuristic = NULL; 
}

template <class T>
DecisionTree<T>::~DecisionTree()
{
  f_deleteTree( m_root );
  delete m_root;
}

// TODO FIX
template <class T>
void DecisionTree<T>::f_deleteTree( DNode<T>* root )
{
  if ( root == NULL || isLeaf( root ) )
  {
    return;
  }

  // Depth-first search to bottom-left of the tree
  for ( unsigned int i = 0; i < root->m_branches.size(); i++ )
  {
    f_deleteTree( root->m_branches[i].first );
  }

  // Delete this node's children
  for ( unsigned int i = 0; i < root->m_branches.size(); i++ )
  {
    delete root->m_branches[i].first;
  }

  root->m_branches.clear();
}

template <class T>
void DecisionTree<T>::ID3( const DataSet<T>& data, unsigned int target )
{
  // Check any obvious conditions that will cause ID3 algorithm to fail.
  if ( data.m_d.empty() )
  {
    cout << "DataSet is empty." << endl;
    return;
  }

  else if ( data.m_n.empty() )
  {
    cout << "DataSet headers are empty." << endl;
    return;
  }

  else if ( target > data.m_n.size()-1 )
  {
    cout << "Target class attribute is not within range of data set." << endl;
    cout << "Attribute column = " << target << " and range is [0, " 
      << data.m_n.size()-1 << ")." << endl;
    return;
  }

  else if ( data.m_d[0].size() != data.m_n.size() )
  {
    cout << "Data width does not match number of headers." << endl;
    cout << "Data width (columns) = " << data.m_d.size() << endl;
    cout << "Header width (columns) = " << data.m_n.size() << endl;
    return;
  }

  else if ( m_heuristic == NULL )
  {
    cout << "No heuristic has been set." << endl;
    return;
  }

  // Generate a list of available attributes (by index) in data for ID3 to
  // branch on. Disclude the target (class) attribute (column).
  vector<unsigned int> attrAvail;
  for ( unsigned int i = 0; i < data.m_n.size(); i++ )
  {
    if ( i != target )
    {
      attrAvail.push_back( i ); 
    }
  }

  // Clear any previously generated tree.
  if ( m_root != NULL )
  {
    clear();
    delete m_root;
    m_root = NULL;
  }

  // Create a new root node whose parent is NULL.
  m_root = new DNode<T>( NULL );
  m_size++;

  // Execute real ID3.
  f_ID3( data, target, attrAvail, m_root );
}

template <class T>
void DecisionTree<T>::f_ID3( const DataSet<T>& data, 
                            unsigned int target, 
                            const vector<unsigned int>& attrAvail,
                            DNode<T>* root )
{
  /* root has previously been created as a DNode<T>* and been given a parent.
   So we just need to populate its label, attributes available, and its children. */

  /* Base cases */
  // All feature vectors are positive.
  cout << "Pure POS?" << endl;
  if ( data.pure( target, data.POS ) )
  {
    cout << "  Pure POS!" << endl;
    convertToLeaf( root, data.POS );
    return;
  }

  cout << "Pure NEG?" << endl;
  // All feature vectors are negative.
  if ( data.pure( target, data.NEG ) )
  {
    cout << "  Pure NEG!" << endl;
    convertToLeaf( root, data.NEG );
    return;
  }

  cout << "Available attributes > 0?" << endl;
  // No additional attributes to choose to branch on.
  if ( attrAvail.empty() )
  {
    cout << "  No attributes!" << endl;
    convertToLeaf( root, data.getMostCommonValue( target ) );
    return;
  }

  cout << "Making children..." << endl;
  /* Data for this node requires child generation. */
  // Choose next attribute to branch on, store in label.
  root->m_label = m_heuristic->evaluate( data, target, attrAvail );
  cout << "  Branching attribute = " << root->m_label << endl;

  // Get possible attribute values for chosen branch attribute.
  vector<T> uniqueAttrVals;
  data.getUniqueValues( root->m_label, uniqueAttrVals );
  cout << "  Number of values for branch = " << uniqueAttrVals.size() << endl;

  // Create child as branch for each possible value.
  for ( unsigned int i = 0; i < uniqueAttrVals.size(); i++ )
  {
    // Add a branch from root to a new, emptpy child, branching on 
    // the possible value i for the chosen attribute.
    DNode<T>* newChild = addBranch( root, uniqueAttrVals[i] );
    cout << "    Created child branching on value = " << uniqueAttrVals[i] << endl;

    m_size++;

    // Populate new node as either leaf or child.
    DataSet<T> dataMatch;
    data.getMatchingVectors( dataMatch, root->m_label, uniqueAttrVals[i] );
    dataMatch.copyHeaders( data );
    cout << "    Size of partitioned data = " << dataMatch.m_d.size() << endl;

    if ( dataMatch.m_d.empty() )
    {
      // No matching feature vectors, no more solid data to use. 
      // Guess using majority vote.
      convertToLeaf( newChild, data.getMostCommonValue( target ) );  
      return;
    }

    else
    {
      // More data matching the chosen attribute. Populate child.
      // Remove chosen attribute from available attributes.
      vector<unsigned int> updatedAttrAvail( attrAvail );
      vector<unsigned int>::iterator it;
      for ( it = updatedAttrAvail.begin(); it != updatedAttrAvail.end(); ++it )
      {
        if ( *it == root->m_label )
        {
          updatedAttrAvail.erase( it );
        }
        break;
      }      
      f_ID3( dataMatch, target, updatedAttrAvail, newChild );
    }
  }
}

template <class T>
DNode<T> * DecisionTree<T>::root()
{
  return m_root;
}

template <class T>
void DecisionTree<T>::setHeuristic( DTreeHeuristic<T>* h )
{
  m_heuristic = h;
}

template <class T>
void DecisionTree<T>::clear()
{
  f_deleteTree( m_root );
  delete m_root;

  m_root = NULL;  
  m_heuristic = NULL; 
  m_size = 0;
}

template <class T>
bool DecisionTree<T>::empty()
{
  return (m_size == 0);
}

template <class T>
unsigned int DecisionTree<T>::size()
{
  return m_size;
}

template <class T>
void DecisionTree<T>::print()
{
  if ( m_root == NULL )
  {
    cout << "Empty tree" << endl;
    return;
  }

  cout << "Tree generated using " << m_heuristic->m_label << endl;

  f_print( m_root, 0 );  
}

template <class T>
void DecisionTree<T>::f_print( DNode<T>* root, unsigned int depth )
{ 
  // Base case: Leaf node. Print the only attribute value, which is the class value.
  if ( isLeaf( root ) )
  {
    cout << root->m_branches[0].second;
  }

  // Non-leaf node. Print spaces, label (index) XE, value used to branch to next child.
  else
  {
    for ( unsigned int i = 0; i < root->m_branches.size(); i++ )
    {
      cout << endl;
      //cout << repeat( "| ", depth ) << nameLookup( ptr->label ) << " = " << ptr->c[i].second << " : ";
      cout << repeat( "| ", depth ) << root->m_label << " = " 
        << root->m_branches[i].second << " : ";
      f_print( root->m_branches[i].first, depth+1 );
      //cout << endl;
    }      
  }
}

string repeat( string s, unsigned int n )
{
  string r("");
  for ( unsigned int i = 0; i < n; i++ )
  {
    r += s;
  }
  return r;
}

template <class T>
DNode<T>* DecisionTree<T>::addBranch( DNode<T>* parent )
{
  // Create a new branch containing a new node with this node as parent.
  pair<DNode<T>*, unsigned int> newBranch( new DNode<T>( parent, 0 ), 0 );

  // Push the new branch onto the parent's branches.
  parent->m_branches.push_back( newBranch );

  return newBranch.first;
}

template <class T>
DNode<T>* DecisionTree<T>::addBranch( DNode<T>* parent, T attrBranch )
{
  // Create a new branch containing a new node with this node as parent.
  pair<DNode<T>*, unsigned int> newBranch( new DNode<T>( parent, 0 ), attrBranch );

  // Push the new branch onto the parent's branches.
  parent->m_branches.push_back( newBranch );

  return newBranch.first;
}

template <class T>
DNode<T>* DecisionTree<T>::addBranch( DNode<T>* parent, DNode<T>* child )
{
  // Create a new branch containing the child node.
  pair<DNode<T>*, unsigned int> newBranch( child, 0 );

  // Push the new branch onto the parent's branches.
  parent->m_branches.push_back( newBranch );

  return child;
}

template <class T>
void DecisionTree<T>::convertToLeaf( DNode<T>* node, T value )
{
  node->m_label = -1;

  pair<DNode<T>*, T> newBranch( NULL, value );

  node->m_branches.push_back( newBranch );

  return;
}

template <class T>
bool DecisionTree<T>::isLeaf( DNode<T>* node )
{
  if ( node == NULL )
  {
    return false;
  }

  else if ( (node->m_label == -1)
    && (node->m_branches.size() == 1)
    && (node->m_branches[0].first == NULL) )
  {
    return true;
  }

  return false;
}