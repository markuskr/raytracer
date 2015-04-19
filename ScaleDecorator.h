//----------------------------------------------------------------------
/// Filename: ScaleDecorater.h
/// Group:    20
/// \brief :  scales primitve
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef SCALEDECORATOR_H_
#define SCALEDECORATOR_H_

#include "PrimitiveDecorator.h"
#include "ResultIntersect.h"
#include "Matrix4x4.h"
#include "Primitive.h"

class ScaleDecorator : public PrimitiveDecorator
{
public:
  ScaleDecorator(Primitive *primitiv, Matrix4x4 matrix) : 
      PrimitiveDecorator(primitiv), m_matrix(matrix)
  {
  };

//----------------------------------------------------------------------  
  virtual ~ScaleDecorator()
  {
    delete m_primitive;
  }

//----------------------------------------------------------------------
  virtual ResultIntersect intersect (Ray &ray)
  {    
    
    Vec3 temp1 = m_matrix.inverse() * ray.p;
    //Vec3 temp2 = m_matrix.inverse() * ray.d;

    Ray temp_ray (temp1, ray.d);

    ResultIntersect result = m_primitive->intersect(temp_ray);
	  result.normal_   = (m_matrix * result.normal_);
    result.normal_.normalize();    
       
	  return result;
  };

private:
  Matrix4x4 m_matrix;
};

#endif
