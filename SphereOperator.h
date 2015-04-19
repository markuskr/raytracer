//----------------------------------------------------------------------
/// Filename: SphereOperator.h
/// Group:    20
/// \brief : sphere operator
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef SPHEREOPERATOR_H_
#define SPHEREOPERATOR_H_

#include "GMLOperator.h"
#include "SceneDescription.h"

#include "SpherePrimitive.h"
#include "Primitive.h"

class SphereOperator : public GMLOperator
{
public:
//--------------------------------------------------------------------
  SphereOperator(GMLInterpreter &interpreter, SceneDescription &scene) :
      GMLOperator(interpreter.m_stack), 
      m_interpreter(interpreter)      , 
      m_scene      (scene)            
      
  {
    m_name = "sphere";
  };
//--------------------------------------------------------------------
  ~SphereOperator()
  {
  };
//--------------------------------------------------------------------
  void execute() const
  {   
    GMLToken token = m_stack.back();
    m_stack.pop_back();

    Material *material = new Material(token, m_interpreter);

    Primitive *sphere = new  SpherePrimitive( (*material) );

    int index = m_scene.addPrimitive(sphere);
    
    GMLToken new_token;
    
    new_token.m_type  = PRIMITIVE;
    new_token.m_int[0]= index;

    m_interpreter.m_stack.push_back(new_token);

  };
private:
  GMLInterpreter   &m_interpreter;
  SceneDescription &m_scene;    
};

#endif

