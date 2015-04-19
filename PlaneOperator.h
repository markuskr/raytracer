//----------------------------------------------------------------------
/// \author Group: 20
/// \brief The operator to create a plane
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef PLANEOPERATOR_H_
#define PLANEOPERATOR_H_

#include "GMLOperator.h"
#include "SceneDescription.h"

#include "PlanePrimitive.h"
#include "Primitive.h"

class PlaneOperator : public GMLOperator
{
public:
  //--------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter
  ///  \param scene scene to add the plane

  PlaneOperator(GMLInterpreter &interpreter, SceneDescription &scene) :
      GMLOperator(interpreter.m_stack), m_interpreter(interpreter) , m_scene(scene)
  {
    m_name = "plane";
  };

  //--------------------------------------------------------------------

  ~PlaneOperator(){};

  //-------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {   
    GMLToken token = m_stack.back();
    m_stack.pop_back();

    Material *material = new Material(token, m_interpreter);

    Primitive *plane = new  PlanePrimitive( (*material) );

    int index = m_scene.addPrimitive(plane);
    
    GMLToken new_token;
    
    new_token.m_type  = PRIMITIVE;
    new_token.m_int[0]= index;

    m_interpreter.m_stack.push_back(new_token);

  };

private:
  GMLInterpreter   &m_interpreter;
  SceneDescription &m_scene;
  
};

#endif /*PLANEOPERATOR_H_*/


