//----------------------------------------------------------------------
/// Filename: RotateyOperator.h
/// Group:    20
/// \brief : rotatey operator
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef ROTATEYOPERATOR_H_
#define ROTATEYOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include "Primitive.h"
#include "RotateDecorator.h"
#include "SceneDescription.h"

#include "Matrix4x4.h"

#include <cmath>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

class RotateyOperator : public GMLOperator  
{
public:
  RotateyOperator(std::vector<GMLToken> &stack, SceneDescription &scene) 
    : GMLOperator(stack), m_scene(scene)
  {
    m_name = "rotatey";
  };

  ~RotateyOperator(){};

//----------------------------------------------------------------------
  void execute() const
  {      
    GMLToken angle_deg  = m_stack.back(); m_stack.pop_back();        
    GMLToken object = m_stack.back(); m_stack.pop_back();
    Primitive *primitive = m_scene.getPrimitive(object.m_int[0]);
    float angle_rad  = (float)(angle_deg.m_float[0] * ( 3.1415f / 180.0f));
    Matrix4x4 matrix = 
      Matrix4x4::createRotY(angle_rad);
    Primitive *rotate = new RotateDecorator(primitive, matrix);
    int index = m_scene.addPrimitive(rotate);
    GMLToken token;
    token.m_type  = PRIMITIVE;
    token.m_int[0]= index;
    m_stack.push_back(token);
  };
private:
  SceneDescription &m_scene;
};


#endif 

