//----------------------------------------------------------------------
/// \author Markus Krallinger 0630748, Group: 20
/// \brief Cube operator to add a cube to the scene
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef CUBEOPERATOR_H_
#define CUBEOPERATOR_H_

#include "GMLOperator.h"
#include "SceneDescription.h"

#include "CubePrimitive.h"
#include "Primitive.h"

#include <cmath>
#include <vector>
#include <string>
#include <memory>

#include <iostream>

class CubeOperator : public GMLOperator
{
public:
  
  //--------------------------------------------------------------------
  /// \param interpreter The interpreter 
  /// \param scene          The SceneDescption with the CSGTree
    
  CubeOperator(GMLInterpreter &interpreter, SceneDescription &scene) :
    GMLOperator(interpreter.m_stack), m_scene_(scene),
        m_interpreter_(interpreter)
  {
    m_name = "cube";
  };

  //--------------------------------------------------------------------
  
  ~CubeOperator()
  {};

  //-------------------------------------------------------------------- 
  /// \brief generates new cube-primitive and puts it on the stack
  
  void execute() const
  {

    GMLToken token = m_stack.back();
    m_stack.pop_back();

    Material &material = *(new Material(token, m_interpreter_));

    Primitive *cube = new CubePrimitive( (material) );

    int index = m_scene_.addPrimitive(cube);

    GMLToken new_token;

    new_token.m_type = PRIMITIVE;
    new_token.m_int[0]= index;

    m_interpreter_.m_stack.push_back(new_token);

  };

  //-------------------------------------------------------------------- 
  
private:

  SceneDescription &m_scene_;
  GMLInterpreter &m_interpreter_;
};

#endif /*CUBEOPERATOR_H_*/

