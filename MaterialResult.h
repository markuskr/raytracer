//----------------------------------------------------------------------
/// \author Group:    20
/// \brief Material - class result
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef MATERIAL_RESULT_H_
#define MATERIAL_RESULT_H_

using namespace std;

#include "Vec3.h"

class MaterialResult
{
public:
  Vec3 color_;
  float ks_;
  float kd_;
  float n_;

  MaterialResult(Vec3& color, float ks, float kd, float n)
  {
    color_ = color;
    ks_ = ks;
    kd_ = kd;
    n_ = n;
  };

};

#endif

