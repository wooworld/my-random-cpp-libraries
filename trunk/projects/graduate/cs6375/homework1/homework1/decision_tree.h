#pragma once
#include <vector>
#include <map>
#include "dnode.h"
#include "dataset.h"
#include "d_tree_heuristic.h"

using namespace std;

/**
 * \brief Contains storage and functions for creating a decision tree. 
 */
template <class T>
class DecisionTree
{
  public:
    /**
     * \brief Default constructor. Sets contained pointers to NULL.
     */
    DecisionTree();

    /** 
     * \brief Default destructor. Clears memory used by tree.
     */
    ~DecisionTree();

    /**
     * \brief Generates a decision tree using the ID3 algorithm. 
     * \pre target is in [0, data.m_d.size()).
     * \param data -- The DataSet to use as training data to generate the tree. 
     * \param target -- The target attribute in data to create the decision tree for. 
     * \note Assumes that all attributes in data are available for branching on.
     */
    void ID3( const DataSet<T>& data, unsigned int target );

    /**
     * \brief Returns the pointer to this object's root node.
     * \return Pointer to the tree's root node.
     */
    DNode<T>* root();

    /**
     * \brief Returns the pointer to this object's last touched node. 
     * \return Pointer to the tree's last touched node. 
     */
    //DNode<T>* last();

    /**
     * \brief Sets the heuristic to use for tree generation.
     * \param h -- The heuristic to use for tree generation. At each decision
     *  for branching, this will tell the tree which attribute to branch on.
     */
    void setHeuristic( DTreeHeuristic<T>* h );

    /** 
     * \brief Clears the memory used by the tree and resets everything to
     *  default values.
     */
    void clear();

    /** 
     * \brief Returns whether the tree has any nodes.
     * \retval true -- The tree has zero nodes.
     * \retval false -- The tree has at least one node.
     */
    bool empty();

    /**
     * \brief Returns the number of nodes in the tree.
     * \return The number of nodes in the tree.
     */
    unsigned int size();

    /**
     * \brief Prints the tree to standard out.
     */
    void print();
    
  protected:
    
    /**
     * \brief Clears the memory used by the tree and resets everything to
     *  default values.
     */
    void f_deleteTree( DNode<T>* root );

    /**
     * \brief Prints out the node pointed to by root and proceeds to print
     *  out any children root may have.
     * \param root -- The root node of tree to print. This may be a subtree.
     * \param depth -- The depth of the root node in a given tree.
     */
    void f_print( DNode<T>* root, unsigned int depth );

    /**
     * \brief Creates a new branch to an empty child node from the specified parent.
     * \param parent -- The node to treat as the parent. The new branch will
     *  be created in this node and the branch will point to a new, empty child.
     * \return A pointer to the newly created child.
     */
    DNode<T>* addBranch( DNode<T>* parent );

    /**
     * \brief Creates a new branch to an empty child node from the specified parent.
     * \param parent -- The node to treat as the parent. The new branch will
     *  be created in this node and the branch will point to a new, empty child.
     * \param attrBranch -- The index in m_attrAvail for which this child 
     *  was branched on. 
     * \return A pointer to the newly created child.
     */
    DNode<T>* addBranch( DNode<T>* parent, T attrBranch );

    /**
     * \brief Creates a new branch to the specified child from the specified parent.
     * \param parent -- The node to treat as the parent. The new branch will be
     *  created in this node and the branch will point to the specified child.
     * \param child -- The node to treat as the child. The branch will point
     *  from the parent to this child.
     * \return A pointer to the specified child. 
     */
    DNode<T>* addBranch( DNode<T>* parent, DNode<T>* child );

    /**
     * \brief Converts a node to a leaf node.
     * \param node -- Pointer to the node to be converted.
     * \param value -- The value for the leaf node to hold.
     * \note This assumes that node is a newly created node. Expects that 
     *  there are zero branches and the parent pointer has already been set.
     */
    void convertToLeaf( DNode<T>* node, T value );

    /**
     * \brief Tells whether a node is a leaf node or not.
     * \param node -- Pointer to the node to check.
     * \retval true If the node is a leaf node.
     * \retval false If the node is not a leaf node. 
     */
    bool isLeaf( DNode<T>* node );

    /**
     * \brief Generates a decision tree using the ID3 algorithm. 
     * \pre target is in [0, data.m_d.size()).
     * \param data -- The DataSet to use as training data to generate the tree. 
     * \param target -- The target attribute in data to create the decision tree for. 
     * \param attrAvail -- The list of attributes the ID3 algorithm will consider as
     *  available to create branches for.
     * \param root -- The node the ID3 algorithm will consider for labeling and 
     *  branching from.
     */
    void f_ID3( const DataSet<T>& data, 
      unsigned int target, 
      const vector<unsigned int>& attrAvail, 
      DNode<T>* root );

    /**
     * \brief A pointer to the root node of the tree.
     */
    DNode<T> * m_root;

    /**
     * \brief A pointer to the heuristic the tree will use when creating the
     *  tree.
     */
    DTreeHeuristic<T> * m_heuristic;
    
  private:

    /**
     * \brief The number of nodes in the tree.
     */
    unsigned int m_size;
};

#include "decision_tree.hpp"
