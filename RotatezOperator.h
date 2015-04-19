//----------------------------------------------------------------------
/// Filename: RotatezOperator.h
/// Group:    20
/// \brief : rotatez operator
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef ROTATEZOPERATOR_H_
#define ROTATEZOPERATOR_H_

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

class RotatezOperator : public GMLOperator  
{

public:
  RotatezOperator(std::vector<GMLToken> &stack, SceneDescription &scene) 
    : GMLOperator(stack), m_scene(scene)
  {
    m_name = "rotatey";
  };

  ~RotatezOperator(){};

  void execute() const
  {      
    GMLToken angle_deg  = m_stack.back(); m_stack.pop_back();         
    //calculate scaling factors
    float pi        = 2 * acos(0.0f);
    float to_radian = 2 * pi / 360.0f;
    GMLToken object = m_stack.back(); m_stack.pop_back();
    Primitive *primitive = m_scene.getPrimitive(object.m_int[0]);
    
		float angle_rad  = (float)(angle_deg.m_float[0] * to_radian);
    Matrix4x4 matrix = Matrix4x4::createRotZ(angle_rad);

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

