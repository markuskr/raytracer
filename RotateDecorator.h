//----------------------------------------------------------------------
/// Filename: RotateDecorater.h
/// Group:    20
/// \brief :  rotates primitve
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef ROTATEDECORATOR_H_
#define ROTATEDECORATOR_H_

#include "PrimitiveDecorator.h"
#include "ResultIntersect.h"
#include "Matrix4x4.h"
#include "Primitive.h"
#include "Vec3.h"

class RotateDecorator : public PrimitiveDecorator
{
public:
  RotateDecorator(Primitive *primitiv, Matrix4x4 matrix) : 
      PrimitiveDecorator(primitiv), m_matrix(matrix)
  {
  };

  virtual ~RotateDecorator()
  {  
    delete m_primitive;
  }

//----------------------------------------------------------------------
  virtual ResultIntersect intersect (Ray &ray)
  {    
    
    Vec3 temp  = m_matrix.inverse() * ray.p;
    Vec3 temp2 = m_matrix.inverse() * ray.d;

    Ray temp_ray(temp,temp2);
    ResultIntersect result = m_primitive->intersect(temp_ray);
    
    if (result.hit_)
    {
      result.hitpoint_ = m_matrix * result.hitpoint_ ;
      result.normal_   = m_matrix * result.normal_   ;    
      result.normal_.normalize();     
    }      
    return result;
  };

private:
  Matrix4x4 m_matrix;
};

#endif
