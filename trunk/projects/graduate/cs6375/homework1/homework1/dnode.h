#pragma once
#include <vector>

using namespace std;

/**
 * \brief A node to use in the decision tree.
 */
template <class T>
class DNode
{
  public:
    /**
     * \brief Default constructor.
     */
    DNode<T>() : m_label(0)
    {
      m_parent = NULL;
    }

    /**
     * \brief Constructor specifying a parent node.
     * \param parent -- A pointer to the parent DNode. Must be of same data type.
     */
    DNode<T>( DNode<T>* parent )
    {
      m_parent = parent;
    }

    /**
     * \brief Constructor specifying a parent node and label.
     * \param parent -- A pointer to the parent DNode. Must be of same data type.
     * \param label -- The label to assign to this node. 
     */

    DNode<T>( DNode<T>* parent, unsigned int label ) : m_label(label)
    {
      m_parent = parent;
    }

    /**
     * \brief The label for this node. Corresponds directly to the attribute
     *  (column number) in the DataSet this node was generated from.
     * \note A label of -1 implies this is a leaf node.
     */
    unsigned int m_label;

    /**
     * \brief vector of possible values for the attribute label (above) at the
     *  time this node was generated.
     * \note An available vector of size 1 implies this is a leaf node. The value
     *  contained in av[0] is the value of the leaf node.
     */
    //vector<T> m_attrVals;

    /**
     * \brief A pointer to this node's parent node.
     */
    DNode<T> * m_parent;

    /**
     * \brief A vector of 2-tuples containing pointers to children and branching 
     *  values.
     * 
     * Each index of this vector contains a 2-tuple in the form of a
     * <DNode<T>*, unsigned int> std::pair. 
     *
     * The first element of each pair is a pointer to a child node of this node.
     * The second element of each pair is the index in m_attrAvail 
     * (above) for which this child was branched on. 
     */
    //vector<pair<DNode<T>*, unsigned int> > m_branches;     
    vector<pair<DNode<T>*, T> > m_branches;
};
