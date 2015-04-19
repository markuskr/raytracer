#ifndef TRANSLATEDOCORATOR_H_
#define TRANSLATEDOCORATOR_H_

#include "PrimitiveDecorator.h"
#include "ResultIntersect.h"
#include "Matrix4x4.h"
#include "Primitive.h"
#include "Vec3.h"

class TranslateDecorator : public PrimitiveDecorator
{
public:
  TranslateDecorator(Primitive *primitiv, Matrix4x4 matrix) : 
      PrimitiveDecorator(primitiv), m_matrix(matrix)
  {
  };

  ~TranslateDecorator()
  {
    delete m_primitive;
  }

  virtual ResultIntersect intersect (Ray &ray)
  {    
    Matrix4x4 inverse = m_matrix.inverse();

    Vec3 temp = inverse * ray.p;
    Ray temp_ray (temp, ray.d);
    ResultIntersect result = m_primitive->intersect(temp_ray);

    if (result.hit_)
    {
      result.hitpoint_ = m_matrix * result.hitpoint_ ;
    }     
    return result;
  };

private:
  Matrix4x4 m_matrix;
};

#endif
