//----------------------------------------------------------------------
/// Filename: UscaleOperator.h
/// Group:    20
/// \brief : uscale operator
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef USCALEOPERATOR_H_
#define USCALEOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <cmath>
#include <vector>
#include <string>
#include <memory>

#include <iostream>

class UscaleOperator : public GMLOperator
{
public:
  UscaleOperator(std::vector<GMLToken> &stack,
    SceneDescription &scene) :
    GMLOperator(stack), m_scene(scene)
  {
    m_name = "uscale";
  };

  ~UscaleOperator()
  {
  };

  void execute() const
  {
    GMLToken s_x = m_stack.back();
    m_stack.pop_back();
    GMLToken object = m_stack.back();
    m_stack.pop_back();

    Primitive *primitive = m_scene.getPrimitive(object.m_int[0]);
    Matrix4x4 matrix = Matrix4x4::createScale(
    (float) s_x.m_float[0], (float) s_x.m_float[0],
    (float) s_x.m_float[0]);
    Primitive *scale = new ScaleDecorator(primitive, matrix);
    int index = m_scene.addPrimitive(scale);
    GMLToken token;
    token.m_type = PRIMITIVE;
    token.m_int[0]= index;
    m_stack.push_back(token);
  };
private:
  SceneDescription &m_scene;
};

#endif /*USCALEOPERATOR_H_*/

