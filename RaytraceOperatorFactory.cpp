//----------------------------------------------------------------------
/// Filename: RaytraceOperatorFactory.cpp
/// Group:    20
/// \brief : factory for producing the raytracer operators
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#include "RaytraceOperatorFactory.h"
#include "SphereOperator.h"
#include "RenderOperator.h"
#include "TranslateOperator.h"
#include "RotateyOperator.h"
#include "RotatezOperator.h"
#include "RotatexOperator.h"
#include "ScaleOperator.h"
#include "SceneDescription.h"
#include "LightOperator.h"
#include "PlaneOperator.h"
#include "UnionOperator.h"
#include "CubeOperator.h"
#include "UscaleOperator.h"
#include "PointLightOperator.h"

#include "CalculateColorStrategy.h"
#include "RayShootingStrategy.h"

using std::string;

//----------------------------------------------------------------------
RaytraceOperatorFactory::RaytraceOperatorFactory(
    GMLInterpreter &interpreter, SceneDescription &scene, CalculateColorStrategy &color, 
    RayShootingStrategy &shooting) :
  GMLOperatorFactory(interpreter), m_scene(scene), m_color(color),
    m_shooting(shooting)
{
}

//----------------------------------------------------------------------
int RaytraceOperatorFactory::createOperator(
    const string &gml_operator)
{
  if (gml_operator.compare("sphere") == 0)
  {
    return m_interpreter.registerOperator(new SphereOperator(m_interpreter, m_scene));
  }
  else if (gml_operator.compare("render") == 0)
  {
    return m_interpreter.registerOperator(new RenderOperator(m_interpreter, m_scene, m_color, m_shooting));
  }
  else if (gml_operator.compare("plane") == 0)
  {
    return m_interpreter.registerOperator(new PlaneOperator(m_interpreter, m_scene));
  }
  else if (gml_operator.compare("translate") == 0)
  {
    return m_interpreter.registerOperator(new TranslateOperator(m_interpreter.m_stack, m_scene));
  }
  else if (gml_operator.compare("rotatex") == 0)
  {
    return m_interpreter.registerOperator(new RotatezOperator(m_interpreter.m_stack, m_scene));
  }
  else if (gml_operator.compare("rotatey") == 0)
  {
    return m_interpreter.registerOperator(new RotateyOperator(m_interpreter.m_stack, m_scene));
  }
  else if (gml_operator.compare("rotatez") == 0)
  {
    return m_interpreter.registerOperator(new RotatezOperator(m_interpreter.m_stack, m_scene));
  }
  else if (gml_operator.compare("scale") == 0)
  {
    return m_interpreter.registerOperator(new ScaleOperator(m_interpreter.m_stack, m_scene));
  }
  else if (gml_operator.compare("uscale") == 0)
  {
    return m_interpreter.registerOperator(new UscaleOperator(m_interpreter.m_stack, m_scene));
  }
  else if (gml_operator.compare("light") == 0)
  {
    return m_interpreter.registerOperator(new LightOperator(m_interpreter.m_stack, m_scene));
  }
  else if (gml_operator.compare("union") == 0)
  {
    return m_interpreter.registerOperator(new UnionOperator(m_interpreter.m_stack, m_scene));
  }
  else if (gml_operator.compare("cube") == 0)
  {
    return m_interpreter.registerOperator(new CubeOperator(m_interpreter, m_scene));
  }
  else if (gml_operator.compare("pointlight") == 0)
  {
    return m_interpreter.registerOperator(new PointLightOperator(m_interpreter.m_stack, m_scene));
  }
  return -1;
}

