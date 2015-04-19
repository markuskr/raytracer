//----------------------------------------------------------------------
/// Filename: Vec3.h
/// Group:    20
/// \brief :describes a 3 dimensional vector
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <iostream>
using namespace std;

#define V_EPSILON 0.0000001

class Vec3 {
public:
  float val[3];	/** x,y,z */

  Vec3() {
    val[0] = 0.0f;
    val[1] = 0.0f;
    val[2] = 0.0f;
  }

  Vec3(float x, float y, float z) {
    val[0] = x;
    val[1] = y;
    val[2] = z;
  }
///-------------------------------------------------------------------
	/// \normailze vector
  void normalize() {
    float l = length();
    val[0] /= l;
    val[1] /= l;
    val[2] /= l;
  }


  inline Vec3 & operator=(const Vec3 &from) {
    val[0] = from.val[0];
    val[1] = from.val[1];
    val[2] = from.val[2];
    return *this;
  }

///-------------------------------------------------------------------
	/// \operator+
  friend const Vec3 operator+(const Vec3& a, const Vec3& b) {
    return Vec3(a.val[0]+b.val[0], a.val[1]+b.val[1], a.val[2]+b.val[2]);
  }

///-------------------------------------------------------------------
	/// \operator -
  friend const Vec3 operator-(const Vec3& a, const Vec3& b) {
    return Vec3(a.val[0]-b.val[0], a.val[1]-b.val[1], a.val[2]-b.val[2]);
  }

///-------------------------------------------------------------------
	/// \operator *
  friend const Vec3 operator*(const Vec3& v,const float s) {
    return Vec3(v.val[0]*s, v.val[1]*s, v.val[2]*s);
  }

///-------------------------------------------------------------------
	/// \scalar product
  static Vec3 emul (const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.val[0]*v2.val[0], v1.val[1]*v2.val[1], v1.val[2]*v2.val[2]);
  }

///-------------------------------------------------------------------
  ///  \dot product
  float operator*(Vec3& a) const {
    return val[0]*a[0] + val[1]*a[1]+val[2]*a[2];
  }


///-------------------------------------------------------------------
	/// \access operator
  float& operator[](int x) {
    return val[x];
  }


///-------------------------------------------------------------------
	/// \operator += 
  Vec3& operator+=(const Vec3& v) { 
    val[0] += v.val[0];
    val[1] += v.val[1];
    val[2] += v.val[2];
    return *this;
  }

  void negate() {
    val[0]=-val[0];
    val[1]=-val[1];
    val[2]=-val[2];
  }

  float length() {
    return sqrt(val[0]*val[0]+val[1]*val[1]+val[2]*val[2]);
  }
///-------------------------------------------------------------------
	/// \ support for cout
  friend ostream& operator<<(ostream& Stream, const Vec3& v) {
    return Stream << "(" << v.val[0] << "|" << v.val[1] << "|" << v.val[2] << ")";
  }

///-------------------------------------------------------------------
	/// \ ==operator
  friend bool operator==(const Vec3& V1, const Vec3& V2){
    if (V1.val[0] == V2.val[0] && V1.val[1] == V2.val[1] && V1.val[2] == V2.val[2] )
      return true;
    else
      return false;
  }

};

#endif
