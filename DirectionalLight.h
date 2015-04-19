//----------------------------------------------------------------------
/// \author Markus Krallinger 0630748, Group: 20
/// \brief Cube DirectionalLight, took from AG02
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef __DIRECTIONALLIGHT_H_
#define __DIRECTIONALLIGHT_H_

#include "Light.h"
#include "Vec3.h"

class DirectionalLight : public Light
{
private:
  Vec3 m_direction;
public:

  //-------------------------------------------------------------------
  ///  \param color color of the light
  ///  \param direction direction of the light
    
  DirectionalLight(Vec3 &color, Vec3 &direction)
  {
    m_color = color;
    m_direction = direction;
    m_direction.normalize();	
    m_direction.negate(); 
  }

  //-------------------------------------------------------------------
  /// \brief returns the color of the light
  /// \param pos position of the light
  /// \return the color

  Vec3 getColor(Vec3 pos) 
  {
    return m_color;
  }

  //-------------------------------------------------------------------
  /// \brief returns the direction of the light
  /// \param pos position of the light
  /// \return the direction

  Vec3 getDirection(Vec3 pos) 
  {
    return m_direction;
  }

  //-------------------------------------------------------------------
  /// \brief returns the intensity of the light
  /// \param pos position of the light
  /// \return the intensity

  double getIntensity(Vec3 pos)
  {
    return 1.0f;
  }

  //-------------------------------------------------------------------
  /// \brief check if the light has position
  /// \return false

  bool hasPosition()
  {
    return false;
  }

  //-------------------------------------------------------------------
  /// \brief the position of the light
  /// \return the position of the light

  Vec3 getPosition()
  {  
    return Vec3(0,0,0); 
  }


};

#endif



