//----------------------------------------------------------------------
/// Filename: PrimitiveDecorator.h
/// Group:    20
/// \brief : Decorator for primitves
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef PRIMITIVEDECORATOR_H_
#define PRIMITIVEDECORATOR_H_

#include "Primitive.h"
#include "ResultIntersect.h"
#include "Ray.h"

#include "Material.h"

class PrimitiveDecorator : public Primitive
{
public: 
  PrimitiveDecorator(Primitive *primitive) :
      Primitive(primitive->getMaterial()), m_primitive(primitive)
  {
  };

//----------------------------------------------------------------------
  virtual ResultIntersect intersect (Ray &ray)
  {
    return m_primitive->intersect(ray);
  };

protected:
  Primitive *m_primitive;
};


#endif


