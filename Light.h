//----------------------------------------------------------------------
/// \author Markus Krallinger 0630748, Group: 20
/// \brief Cube Light, took from AG02
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef __LIGHT_H_
#define __LIGHT_H_


#include "Vec3.h"

class Light {
  protected:
    Vec3 m_color;

  public:
    Light() 
    {};
		
    virtual ~Light(){};

    //Abstract light evaluation functions
    virtual Vec3 getColor(Vec3 pos) = 0;
    virtual Vec3 getDirection(Vec3 pos) = 0;
    virtual double getIntensity(Vec3 pos) = 0;

    virtual bool hasPosition() = 0;
    virtual Vec3 getPosition() = 0;
};

#endif

