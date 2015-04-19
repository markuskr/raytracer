//----------------------------------------------------------------------
/// Filename: Primitive.h
/// Group:    20
/// \brief : abstract class for primitves
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef PRIMITVE_H_
#define PRIMITVE_H_

#include <vector>
#include <memory>

#include "GMLInterpreter.h"
#include "ResultIntersect.h"
#include "Ray.h"

#include "Material.h"

class Primitive
{
public: 
  Primitive(Material &material) 
    :  m_material(material)
	{};
 
  virtual ~Primitive()
  {};

//----------------------------------------------------------------------
	///calculates the intersection with a ray
  virtual ResultIntersect intersect (Ray &ray) = 0;

  Material& getMaterial()
  {
    return m_material;
  }

protected:
	Material &m_material;
};


#endif /*PRIMITVE_H_*/


