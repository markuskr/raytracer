//----------------------------------------------------------------------
/// Filename: SceneDescription.h
/// Group:    20
/// \brief : describes the scene of a raytracer(lights, primitves)
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef SCENEDESCRIPTION_H_
#define SCENEDESCRIPTION_H_

#include "CSGTree.h"
#include "Primitive.h"
#include "Light.h"
#include <vector>

class SceneDescription
{
public:

  ~SceneDescription()
  {
    std::vector<Light *>::iterator it = m_lights.begin();
    for (;it < m_lights.end(); it ++)
      delete (*it); 
  }
  int addPrimitive( Primitive *primitive)
  {
    return m_tree.addPrimitive(primitive);
  };
  Primitive* getPrimitive(int index)
  {
    return m_tree.getPrimitve(index);
  };

  Light* getLight(int index)
  {
    return m_lights.at(index);
  };

  int addLight(Light *light)
  {
    m_lights.push_back(light);
    return m_lights.size() - 1;
  }

private:
  CSGTree              m_tree;
  std::vector<Light *> m_lights;
};

#endif

