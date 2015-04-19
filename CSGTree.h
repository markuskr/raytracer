//----------------------------------------------------------------------
/// \author Markus Krallinger 0630748, Group: 20
/// \brief Represents the CSGTree
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef CSGTREE_H
#define CSGTREE_H

#include "Primitive.h"
#include "ResultIntersect.h"
#include "Ray.h"
#include <vector>

using std::vector;

class CSGTree
{
public:

  CSGTree(){};
  ~CSGTree()
  {
    delete m_tree.back();
  };
  //--------------------------------------------------------------------
  /// \param primitive The primitive to add to the tree
  /// \return          Index of the primitive in the tree
   
  int addPrimitive( Primitive *primitive )
  {
    m_tree.push_back(primitive);
    return m_tree.size() - 1;
  };
  
  //--------------------------------------------------------------------
  /// \return primitive The primitive in the tree
  /// \param            Index of the primitive in the tree
  
  Primitive* getPrimitve(int index)
  {
    return m_tree[index];
  };
//-------------------------------------------------------------------
  
private:
  vector<Primitive *> m_tree;
    
};

#endif
