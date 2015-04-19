//----------------------------------------------------------------------
/// \author Group: 20
/// \brief special matric class took from AG02
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------


/************************************************************************/
/* 711.013.EEGS.2007                                                    */
/*                                                                      */
/* Aufgabe 16: Raytracer mit stackbasierter Eingabesprache              */
/* Gruppe G02                                                           */
/*                                                                      */
/* file: PointLight.h                                                   */
/* author(s): karl gsoellpointner                                       */
/************************************************************************/

#ifndef __POINTLIGHT_H_
#define __POINTLIGHT_H_

#include "Light.h"

class PointLight : public Light {
private:
    Vec3 m_position;
public:
    inline PointLight(Vec3 &color, Vec3 &position) {
        m_color = color;
        m_position = position;
    }

    Vec3 getColor(Vec3 pos)
    {
        return m_color;
    };
    Vec3 getDirection(Vec3 pos)
    {
        Vec3 dir = m_position - pos;
        dir.normalize();
        return dir;
    };
    double getIntensity(Vec3 pos)
    {
        Vec3 dir = m_position - pos;
        double distance = dir.length();
        return 100.0 / (99.0 + distance*distance); 

    };

    bool hasPosition() { return true; }
    Vec3 getPosition() { return m_color; }
};

#endif
