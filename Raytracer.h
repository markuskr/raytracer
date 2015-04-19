//----------------------------------------------------------------------
/// Filename: Raytracer.h
/// Group:    20
/// \brief : implements a raytracer using two strategies
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef RAYTRACER_H_
#define RAYTRACER_H_


#include "RaytracerInterface.h"
#include "RayShootingStrategy.h"

#include "Image.h"
#include "Primitive.h"
#include "Ray.h"
#include "Vec3.h"

#include <cmath>

#include <iostream>
#include <fstream>

using namespace std;

class Raytracer 
{
private:
  RayShootingStrategy &m_ray_tracing_strategy;

public:
  Raytracer( RayShootingStrategy& ray_tracing_strategy)
    : m_ray_tracing_strategy (ray_tracing_strategy)  
  {};

//----------------------------------------------------------------------
  void createImage(int depth, int fov, Vec3 camera, Image &image, std::string filename)
  {
    Image &finished = m_ray_tracing_strategy.shootRay(image, depth, fov,  0, camera);
    
    int type = 6;  // 3 planes
    ofstream dst(filename.c_str(), ios::binary);
    if(!dst) 
    {
       cerr << "[ImageExportPNM] Couldn't open image file \"" << filename.c_str() << "\" for writing.\n";
    }
    else
    {
       dst << 'P' << type << endl << finished.getWidth() << ' ' << finished.getHeight() << " 255\n";
       dst.write((char *)finished.getValues(), finished.getWidth()*finished.getHeight()*3);
    }
  };
};

#endif

