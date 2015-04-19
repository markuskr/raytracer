//----------------------------------------------------------------------
/// Filename: PointLightOperator.h
/// Group:    20
/// \brief :operator for crating a pointlight
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef POINTLIGHTOPERATOR_H_
#define POINTLIGHTOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>
#include <memory>

#include "PointLight.h"

#include <iostream>

class PointLightOperator  : public GMLOperator 
{
public:
  PointLightOperator(std::vector<GMLToken> &stack, SceneDescription &scene) :
    GMLOperator(stack), m_scene(scene)	
  {
    m_name = "pointlight";
  };

  ~PointLightOperator(){};

  void execute() const
  {
    GMLToken color      = m_stack.back(); m_stack.pop_back();
    GMLToken position  = m_stack.back(); m_stack.pop_back();
    Vec3 vec_color    ( color.m_float[0],    color.m_float[1],   color.m_float[2]);
    Vec3 vec_position ( position.m_float[0], position.m_float[1], position.m_float[2]);
    Light *light = new PointLight(vec_color, vec_position);
    int index = m_scene.addLight(light);
    GMLToken token;
    token.m_type  = LIGHT;
    token.m_int[0]= index;
    m_stack.push_back(token);
  };  
private:  
  SceneDescription &m_scene;
};



#endif /*GETZOPERATOR_H_*/

