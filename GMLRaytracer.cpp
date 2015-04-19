//----------------------------------------------------------------------
/// Filename: GMLRaytracer.cpp
/// Author:   Markus Krallinger 0630748
/// Group:    20
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------


#include "GMLRaytraceFacade.h"

int main(int argc, char* argv[])
{	
  GMLRaytraceFacade raytracer(argv[1]);
  raytracer.run();
  return 0;  
}
