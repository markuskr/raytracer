//----------------------------------------------------------------------
/// Filename: PlanePrimitive.h
/// Group:    20
/// \brief : describes a plane primitive
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef PLANEPRIMITIVE_H_
#define PLANEPRIMITIVE_H_

#include <cmath>

#include "Material.h"
#include "Primitive.h"
#include "ResultIntersect.h"

#include <iostream>

using namespace std;

class PlanePrimitive : public Primitive
{
public:
  PlanePrimitive(Material &material) :
    Primitive(material)
  {
    distance = 0;
  };

  ~PlanePrimitive()
  {
    delete &m_material;
  };

//----------------------------------------------------------------------
  ResultIntersect intersect(Ray &ray)
  {

    distance= ray.p.length();
    nVec = surfaceNormal(ray.d, 0);

    ResultIntersect result(m_material);
    result.hit_ = false;

    float Vd = (nVec * ray.d);

    if (fabs(Vd) < 0.0001f)
    {
      // ray is parallel
      return result;
    }

    float t = -(nVec * ray.p + distance) / Vd;

    // ignore intersection behind viewpoint
    if (t > 0)
    {
      // create Interval Data
      Vec3 hp(ray.p+ray.d*t);
      float u;
      float v;
      int face = 0;
      toTextureCoordinates(hp, face, u, v);
      result.hitpoint_ = hp;
      result.face_ = face;
      result.u_ = u;
      result.v_ = v;

      result.normal_ = surfaceNormal(hp, face);
      result.hit_ = true;
    }
    return result;

  };


private:
  Vec3 nVec;
  float distance;

//----------------------------------------------------------------------
  void toTextureCoordinates(Vec3 &surfacePoint, int &face, float &u,
      float &v)
  {
    u = surfacePoint[0];
    v = surfacePoint[2];
  };

//----------------------------------------------------------------------
  Vec3 surfaceNormal(Vec3 &surfacePoint, int face)
  {
    return Vec3(0.0, 1.0, 0.0);
  };
};

#endif /*PLANEPRIMITIVE_H_*/
