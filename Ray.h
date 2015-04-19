//----------------------------------------------------------------------
/// Filename: Ray.h
/// Group:    20
/// \brief : describes a ray
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef RAY_H_
#define RAY_H_

#include "Vec3.h"

class Ray {
public:
	Ray(Vec3 &sp, Vec3 &dir) {
		p = sp;
		d = dir;
		d.normalize();
	}
	Vec3 p;		/** Ray starting point */
	Vec3 d;		/** direction vector */
};

#endif
