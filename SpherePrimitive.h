//----------------------------------------------------------------------
/// Filename: SpherePrimitive.h
/// Group:    20
/// \brief : describes a sphere primitive
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef SPHEREPRIMITIVE_H_
#define SPHEREPRIMITIVE_H_
#include <cmath>

#include "Material.h"
#include "Primitive.h"
#include "ResultIntersect.h"

#include <iostream>

using namespace std;

class SpherePrimitive : public Primitive
{
public:
    SpherePrimitive (Material &material) 
        : Primitive(material)
    {};
    
    ~SpherePrimitive ()
    {
    	delete &m_material;
    }

//----------------------------------------------------------------------
  ResultIntersect intersect(Ray &ray) 
  {
    ResultIntersect result (m_material);
    result.hit_ = false;
    float a = (ray.d) * (ray.d);
    float b = 2 *(ray.d * ray.p);
    float c = (ray.p * ray.p) - 1;
    float checkCriterium = (b*b) - (4*a*c);
    if(checkCriterium >= 0) //no intersection
    {
      float t1 = (-b + sqrt(checkCriterium))/(2*a);
      float t2 = (-b - sqrt(checkCriterium))/(2*a);      
      if((t1 < 0) && (t2 < 0))
        return result;
      t1 = t1 > 0.0f ? t1 : 0.0f;
      t2 = t2 > 0.0f ? t2 : 0.0f;

      float s  = t1 <= t2 ? t1 : t2; 
      if ( s > 0.0) 
      {
        Vec3 firstHitPoint;
   // Check if one hitpoint is behind the ray, take only the other one if so
        if(t2 > t1) 
          firstHitPoint = t1 > 0.0 ? ray.p + ray.d*t1 : ray.p + ray.d*t2;			   
        else 
          firstHitPoint = t2 > 0.0 ? ray.p + ray.d*t2 : ray.p + ray.d*t1;
        float u,v;
        int face = 0;
        toTextureCoordinates(firstHitPoint, face, u, v); 		  
        result.hitpoint_ = firstHitPoint;
        result.face_ = face;
        result.u_ = u;
        result.v_ = v;
        result.normal_ = surfaceNormal(firstHitPoint, face);
        result.hit_ = true;
      }

    }
    return result;
  }

private: 

//----------------------------------------------------------------------
  void toTextureCoordinates(Vec3 &surfacePoint, int &face, float &u, float &v) 
  {
    float pi = 3.1415f;
    float d = sqrt(1.0f - (surfacePoint[1] * surfacePoint[1]));
    u=0.0f;
    if (fabs(d) < V_EPSILON) 
    {           
      u = 1.0f;
    } 
    else  
    {
      float ux = surfacePoint[0] / d;
      float uz = surfacePoint[2] / d;
      // safety checks
      ux = fabs(ux-1.0f)<V_EPSILON ? 1.0f : ux;
      ux = fabs(ux+1.0f)<V_EPSILON ? -1.0f : ux;
      uz = fabs(uz-1.0f)<V_EPSILON ? 1.0f : uz;
      uz = fabs(uz+1.0f)<V_EPSILON ? -1.0f : uz;
      ux = ux > 1.0f ? 1.0f : ux;
      ux = ux < -1.0f ? -1.0f : ux;
      float ux1 = asin(ux);
      float ux2 = ux1 < 0.0f ? - pi - ux1 : pi - ux1;
      ux1 = ux1 < 0.0f ? ux1 + 2*pi : ux1;
      ux2 = ux2 < 0.0f ? ux2 + 2*pi : ux2;     
      float uz1 = acos(uz);
      float uz2 = 2*pi - uz1;
      
			// select the u where ux and uz are the same
      if ( fabs(ux1-uz1) < V_EPSILON || fabs(ux1-uz2) < V_EPSILON ) 
         u = ux1;
      else 
			  u = ux2;
      u = u / ( 2* pi );
    }
    u = 1.0f - u;       
    v = (surfacePoint[1] + 1.0f) / 2.0f;
		u = u < 0.0f ? 0.0f : u;
    u = u > 1.0f ? 1.0f : u;
    v = v < 0.0f ? 0.0f : v;
    v = v > 1.0f ? 1.0f : v;
  };

//----------------------------------------------------------------------
  Vec3 surfaceNormal(Vec3 &surfacePoint, int face) 
  {	
  // calc the normal vector of the surface hit point 
    Vec3 len = (surfacePoint);	
  //len.normalize(); //<<<<<
    return  Vec3(len);
  };

};

#endif



