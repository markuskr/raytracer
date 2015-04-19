//----------------------------------------------------------------------
/// Filename: RaytraceOperatorFactory.h
/// Group:    20
/// \brief : factory for producing the raytracer operators
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef RAYTRACE_OPERATOR_FACTORY_
#define RAYTRACE_OPERATOR_FACTORY_

#include "GMLOperatorFactory.h"
#include "SceneDescription.h"
#include <string>
#include "Material.h"
#include "CalculateColorStrategy.h"
#include "RayShootingStrategy.h"

class RaytraceOperatorFactory : public GMLOperatorFactory
{
public:
//----------------------------------------------------------------------
	///creates Operator and registers the operator at the interpreter, returns index
  int createOperator(const std::string &);
  RaytraceOperatorFactory(GMLInterpreter &interpreter, SceneDescription &scene, 
    CalculateColorStrategy &color, RayShootingStrategy &shooting);

  ~RaytraceOperatorFactory(){};
  
private:
  SceneDescription &m_scene;
  CalculateColorStrategy &m_color;
  RayShootingStrategy    &m_shooting;
};

#endif


