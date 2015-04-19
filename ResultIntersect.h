//----------------------------------------------------------------------
/// Filename: ResultIntersect.h
/// Group:    20
/// \brief :  saves result of an intersection
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef RESULTINTERSECT_H_
#define RESULTINTERSECT_H_

#include "Vec3.h"
#include "Material.h"

class ResultIntersect 
{
public:
//-------------------------------------------------------------------
  ResultIntersect(Vec3 distance, int face, float u, float v, Vec3 normal, Material &material) 
  : 
  hitpoint_(distance), 
  face_(face)        , 
  u_(u)              , 
  v_(v)              , 
  normal_(normal)    , 
  material_(material)
  {};

  ResultIntersect & operator=(const ResultIntersect &from) 
  {
    hitpoint_ = from.hitpoint_;
    face_    = from.face_; 
    u_       = from.u_; 
    v_       = from.v_; 
    normal_ = from.normal_;
    material_ = from.material_;
    return *this;
  };

//-------------------------------------------------------------------
  ResultIntersect(Material &material) 
  :  material_(material)
  {
    hitpoint_= Vec3(0,0,0); 
    face_    = 0; 
    u_       = 0; 
    v_       = 0; 
    normal_  = Vec3(0,0,0);
  };

//-------------------------------------------------------------------
  Vec3 hitpoint_;
  int   face_ ;
  float u_    ;
  float v_    ;
  Vec3 normal_;
  Material &material_;
  bool hit_;
};

#endif
