//----------------------------------------------------------------------
/// Filename: RayShootingStrategy.h
/// Group:    20
/// \brief : interface for rayshooting strategy
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef RAYSHOOTINGSTRATEGY_H_
#define RAYSHOOTINGSTRATEGY_H_

#include "Image.h"
#include "Vec3.h"
#include "CalculateColorStrategy.h"

class RayShootingStrategy
{
public:

  RayShootingStrategy  ( CalculateColorStrategy &strategy )
    : m_color_strategy ( strategy )
  {
  };
  
  virtual ~RayShootingStrategy(){};

  virtual Image &shootRay ( 
    Image &image   ,
    int depth      , 
    int fov        ,   
    int antialising, 
    Vec3 &camera) = 0;
  
//-------------------------------------------------------------------
protected:
  CalculateColorStrategy &m_color_strategy ;
};

#endif


