//----------------------------------------------------------------------
/// Filename: TranslateOperator.h
/// Group:    20
/// \brief : translate operator
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef TRANSLATEOPERATOR_H_
#define TRANSLATEOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include "Primitive.h"
#include "TranslateDecorator.h"
#include "SceneDescription.h"

#include "Matrix4x4.h"

#include <cmath>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

class TranslateOperator : public GMLOperator  
{
public:

  TranslateOperator(std::vector<GMLToken> &stack, SceneDescription &scene) 
    : GMLOperator(stack), m_scene(scene) 
  {
    m_name = "translate";
  };

  ~TranslateOperator(){};

  void execute() const
  {      
    GMLToken z_dir  = m_stack.back(); m_stack.pop_back();        
    GMLToken y_dir  = m_stack.back(); m_stack.pop_back();        
    GMLToken x_dir  = m_stack.back(); m_stack.pop_back();
    GMLToken object = m_stack.back(); m_stack.pop_back();
    Primitive *primitive = m_scene.getPrimitive(object.m_int[0]);
    Matrix4x4 matrix = 
    Matrix4x4::createTranslation(
      (float) x_dir.m_float[0],
      (float) y_dir.m_float[0],
      (float) z_dir.m_float[0]);
    Primitive *translate = new TranslateDecorator(primitive, matrix);

    int index = m_scene.addPrimitive(translate);
    GMLToken token;
    token.m_type  = PRIMITIVE;
    token.m_int[0]= index;
    m_stack.push_back(token);
  };

private:
  SceneDescription &m_scene;
};


#endif 

