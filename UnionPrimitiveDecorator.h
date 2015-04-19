//----------------------------------------------------------------------
/// Filename: UnionPrimitiveDecorator.h
/// Group:    20
/// \brief : describes an union decorator
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef UNIONPRIMITIVEDECORATOR_H_
#define UNIONPRIMITIVEDECORATOR_H_

#include "PrimitiveDecorator.h"
#include "ResultIntersect.h"
#include "Matrix4x4.h"
#include "Primitive.h"

class UnionPrimitiveDecorator : public PrimitiveDecorator
{
public:
  UnionPrimitiveDecorator(Primitive *primitiv,Primitive *p1) : 
      PrimitiveDecorator(primitiv)
  {
    m_primitive1 = p1;
  };

  ~UnionPrimitiveDecorator()
  {
    delete m_primitive;
    delete m_primitive1; 
  }

  virtual ResultIntersect intersect (Ray &ray)
  {    
    ResultIntersect res1  = m_primitive1->intersect(ray);
    ResultIntersect res2  = m_primitive ->intersect(ray);

    if (res2.hit_ && res1.hit_)
    {
      if (res2.hitpoint_.length() < res1.hitpoint_.length())
        return res2;
      else
        return res1;
    }
    else if (res1.hit_)
    {
      return res1;
    }
    else if (res2.hit_)
    {
      return res2;
    }
    else
      return res1;
  };

private:
  Primitive *m_primitive1;
};

#endif

