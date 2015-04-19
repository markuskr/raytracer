//----------------------------------------------------------------------
/// Filename: UnionOperator.h
/// Group:    20
/// \brief : union operator
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef UNIONOPERATOR_H_
#define UNIONOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include "Primitive.h"
#include "UnionPrimitiveDecorator.h"
#include "SceneDescription.h"

#include "Matrix4x4.h"

#include <cmath>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

class UnionOperator : public GMLOperator  
{
public:
  UnionOperator(std::vector<GMLToken> &stack, SceneDescription &scene) 
    : GMLOperator(stack), m_scene(scene)
  {
    m_name = "union";
  };

  ~UnionOperator(){};

  void execute() const
  {      
    GMLToken obj1   = m_stack.back(); m_stack.pop_back();        
    GMLToken obj2  = m_stack.back(); m_stack.pop_back();     
    Primitive *primitive1 = m_scene.getPrimitive(obj1.m_int[0]);
    Primitive *primitive2 = m_scene.getPrimitive(obj2.m_int[0]);
    Primitive *union_operat = new UnionPrimitiveDecorator(primitive1, primitive2);
    
		int index = m_scene.addPrimitive(union_operat);
    GMLToken token;
    token.m_type  = PRIMITIVE;
    token.m_int[0]= index;
    m_stack.push_back(token);
  };
private:
  SceneDescription &m_scene;
};


#endif 

