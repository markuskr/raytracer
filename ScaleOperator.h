//----------------------------------------------------------------------
/// Filename: ScaleOperator.h
/// Group:    20
/// \brief : scale operator
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef SCALEOPERATOR_H_
#define SCALEOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include "Primitive.h"
#include "ScaleDecorator.h"
#include "SceneDescription.h"

#include "Matrix4x4.h"

#include <cmath>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

class ScaleOperator : public GMLOperator 
{
public:
  ScaleOperator(std::vector<GMLToken> &stack,SceneDescription &scene): GMLOperator(stack), m_scene(scene)		
  {
    m_name = "scale";
  };

  ~ScaleOperator(){};
  void execute() const
  {
    GMLToken s_x  = m_stack.back(); m_stack.pop_back();        
    GMLToken s_y  = m_stack.back(); m_stack.pop_back();        
    GMLToken s_z  = m_stack.back(); m_stack.pop_back();
    GMLToken object = m_stack.back(); m_stack.pop_back();
    Primitive *primitive = m_scene.getPrimitive(object.m_int[0]);
    Matrix4x4 matrix = 
    Matrix4x4::createScale(
      (float) s_x.m_float[0],
      (float) s_y.m_float[0],
      (float) s_z.m_float[0]);
    Primitive *scale = new ScaleDecorator(primitive, matrix);

    int index = m_scene.addPrimitive(scale);
    GMLToken token;
    token.m_type  = PRIMITIVE;
    token.m_int[0]= index;
    m_stack.push_back(token);
  };
private:
  SceneDescription &m_scene;
};


#endif /*SCALEOPERATOR_H_*/

