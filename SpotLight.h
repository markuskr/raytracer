//----------------------------------------------------------------------
/// Filename: SpotLight.h
/// Group:    20
/// \brief : describes a spotlight
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef SPOTLIGHT_H_
#define SPOTLIGHT_H_

#include "Light.h"

class SpotLight : Light {
private:
  Vec3 __position;
  Vec3 __at;
  double __cutoff;
  double __exp;

public:
//----------------------------------------------------------------------
  inline SpotLight(Vec3 &color, Vec3 &position, Vec3 &at, double cutoff, double exp) {
  __color = color;
  __position = position;
  __at = at;
  __cutoff = cutoff;
  __exp = exp;			
  }
//----------------------------------------------------------------------
///Light Interface
  Vec3 getColor(Vec3 pos)
  {
    return __color;
  };
  Vec3 getDirection(Vec3 pos)
  {
    Vec3 dir = __position - pos;
    dir.normalize();
    return dir;
   };

  double getIntensity(Vec3 pos) 
  {
    Vec3 dir = __position - pos;
    double direction = dir.length();
    Vec3 at_pos = __at - __position;
    Vec3 pos_position = pos - __position;
    at_pos.normalize(); // entspricht: (at - pos) / | at - pos |
    pos_position.normalize(); // entspricht: (Q - pos) / | Q - pos | )
   
		// angle berechnen und mit cutoff vergleichen
    double angle_dot_product = at_pos * pos_position;
    double angle = acos ( angle_dot_product ) * 180 / mPI;
    if (angle > __cutoff)
       return 0.0f;
    double i = pow(angle_dot_product, __exp);
    
		// isurface = 100 * i / (99 + d^2)
    double isurface = (100.0 * i) * (1 / (99.0 + direction * direction));
    return isurface;
};

bool hasPosition() { return true; }
Vec3 getPosition() { return __position; }
};

#endif
