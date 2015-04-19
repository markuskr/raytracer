//----------------------------------------------------------------------
/// Filename: RaycastingStrategy.h
/// Group:    20
/// \brief : implements the rayshootingstrategy, used for shooting a ray into a scene
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef RAYCASTINGSTRATEGY_H_
#define RAYCASTINGSTRATEGY_H_


#include "Ray.h"
#include "Vec3.h"
#include "Primitive.h"
#include "ResultIntersect.h"
#include "MaterialResult.h"

#include <cmath>

#include "Light.h"

#include <vector>
#include <iostream>

using std::vector;

#define C_RAYDISPLACEMENT 0.0001f


class RaycastingStrategy : public CalculateColorStrategy
{
public:
//-----------------------------------------------------------------
  RaycastingStrategy ( 
    Vec3              ambient, 
    vector<Light *>   lighst ,
    Primitive        *object ) 
  : 
  CalculateColorStrategy(ambient, lighst, object)
  {};
//-----------------------------------------------------------------
  RaycastingStrategy ()     
  {};

//-----------------------------------------------------------------
  Vec3 calcultateColor(Ray &ray, int depth)
  {    
    ResultIntersect result = m_objects->intersect(ray);
    if (result.hit_)
    {
      MaterialResult material = result.material_
        .getMaterialParameters(result.u_, result.v_, result.face_);
      float n  = material.n_;
      float ks = material.ks_;
      float kd = material.kd_;
      Vec3 color;
      Vec3 ambient;
      ambient = Vec3::emul(m_ambient, material.color_);
      std::vector<Light*>::iterator it = m_lights.begin();
      Vec3 diffuse;
      Vec3 reflection;
      Vec3 specular;
      color = ambient * kd;
      Vec3 &hit_point = result.hitpoint_;
      Vec3 &normal_vector = result.normal_;
      for (; it < m_lights.end(); it++)
      {
        bool is_in_light = false;
        Vec3 light_direction = (*it)->getDirection(hit_point);                
        float si = normal_vector * light_direction;
        if (si > 0)
        {
					//shadow ray
          Vec3 vec_shadow = hit_point + light_direction * C_RAYDISPLACEMENT;
          Ray ray_shadow(vec_shadow, light_direction);
          ResultIntersect result_shadow = m_objects->intersect(ray_shadow);
          if ( (*it)->hasPosition())
          {
            if (result_shadow.hit_ )
            {
              Vec3 hitpoint_shadow = result_shadow.hitpoint_ - hit_point;
              Vec3 light_shadow    = (*it)->getPosition()    - result.hitpoint_;
              if (hitpoint_shadow.length() > light_shadow.length()) 
                is_in_light = true;
            }
            else
              is_in_light = true;
          }
          else
            if (!result_shadow.hit_ ) 
							 is_in_light = true;
          if (is_in_light)
          {
            float light_intensity = static_cast<float>((*it)->getIntensity(hit_point));            
            float temp =  si * light_intensity;
            diffuse += Vec3::emul(material.color_, (*it)->getColor(result.hitpoint_) * temp );
            Vec3 view_direction = ray.d;            
            view_direction.negate();            
            Vec3 h = light_direction  + view_direction;
            h.normalize();
            float bla = static_cast<float>(normal_vector * h);
            float si2 = pow((bla) , n);            
            Vec3 light_color =  (*it)->getColor(result.hitpoint_);
            specular += Vec3::emul(material.color_, light_color * light_intensity * si2);            
            color +=  specular * ks + diffuse *kd;          
         }
       }
     }     
     if (material.ks_ > 0.0)  
     {
       if (-- depth > 0)
       {  
         Vec3 reflection_dir = ray.d - normal_vector * 2.0f * (ray.d * normal_vector);    
         Vec3 reflStart = hit_point + reflection_dir * C_RAYDISPLACEMENT;
         Ray reflectionRay(reflStart, reflection_dir);          
         reflection += Vec3::emul(calcultateColor(reflectionRay, depth), material.color_ * ks); 
       }
     }
     color += reflection;
     color[0] = color[0] > 1.0f ? 1.0f : color[0];
     color[1] = color[1] > 1.0f ? 1.0f : color[1];
     color[2] = color[2] > 1.0f ? 1.0f : color[2];
     return color;
     }
     else      
     {
       return Vec3(0.0, 0.0, 0.0); //Background
     }
  }; 
};

#endif
