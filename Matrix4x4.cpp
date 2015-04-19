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
/* file: Matrix4x4.h                                                    */
/* author(s): ulrich krispel, andreas dolinsek                          */
/************************************************************************/

#include "Matrix4x4.h"

#include <math.h>

const int Matrix4x4::_matrixSize = 4*4*sizeof(float);

const float Matrix4x4::_values_identity[] = { 
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
};

/** create Translation Matrix */
Matrix4x4 Matrix4x4::createTranslation(float tx, float ty, float tz){
	Matrix4x4 m;
	m.values[0][3] = tx;
	m.values[1][3] = ty;
	m.values[2][3] = tz;
	return m;
}

/** create Scale Matrix */
Matrix4x4 Matrix4x4::createScale(float sx, float sy, float sz) {								  
	Matrix4x4 m;
	m.values[0][0] = sx;
	m.values[1][1] = sy;
	m.values[2][2] = sz;
	return m;
}

/** create Uniform Scale Matrix */
Matrix4x4 Matrix4x4::createUniformScale(float s) {
	Matrix4x4 m;
	m.values[0][0] = s;
	m.values[1][1] = s;
	m.values[2][2] = s;
	return m;
}

/** create Rotation around X-Axis */
Matrix4x4 Matrix4x4::createRotX(float theta) {
	Matrix4x4 m;
	m.values[1][1] = cos(theta);
	m.values[1][2] = -sin(theta);
	m.values[2][1] = sin(theta);
	m.values[2][2] = cos(theta);
	return m;
}

/** create Rotation around Y-Axis */
Matrix4x4 Matrix4x4::createRotY(float theta) {
	Matrix4x4 m;
	m.values[0][0] = cos(theta);
	m.values[0][2] = sin(theta);
	m.values[2][0] = -sin(theta);
	m.values[2][2] = cos(theta);
	return m;
}

/** create Rotation around Z-Axis */
Matrix4x4 Matrix4x4::createRotZ(float theta) {

	Matrix4x4 m;
	m.values[0][0] = cos(theta) ;// * to_radian;
	m.values[0][1] = -sin(theta);// * to_radian;
	m.values[1][0] = sin(theta) ;// * to_radian;
	m.values[1][1] = cos(theta) ;// * to_radian;
	return m;
}

#define m00 values[0][0]
#define m01 values[0][1]
#define m02 values[0][2]
#define m03 values[0][3]
#define m10 values[1][0]
#define m11 values[1][1]
#define m12 values[1][2]
#define m13 values[1][3]
#define m20 values[2][0]
#define m21 values[2][1]
#define m22 values[2][2]
#define m23 values[2][3]
#define m30 values[3][0]
#define m31 values[3][1]
#define m32 values[3][2]
#define m33 values[3][3]

// inverting functions adopted from
// http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm

/** returns the inverse of the matrix */
Matrix4x4 Matrix4x4::inverse() {
	Matrix4x4 im;
	im.m00 = m12*m23*m31 - m13*m22*m31 + m13*m21*m32 - m11*m23*m32 - m12*m21*m33 + m11*m22*m33;
	im.m01 = m03*m22*m31 - m02*m23*m31 - m03*m21*m32 + m01*m23*m32 + m02*m21*m33 - m01*m22*m33;
	im.m02 = m02*m13*m31 - m03*m12*m31 + m03*m11*m32 - m01*m13*m32 - m02*m11*m33 + m01*m12*m33;
	im.m03 = m03*m12*m21 - m02*m13*m21 - m03*m11*m22 + m01*m13*m22 + m02*m11*m23 - m01*m12*m23;
	im.m10 = m13*m22*m30 - m12*m23*m30 - m13*m20*m32 + m10*m23*m32 + m12*m20*m33 - m10*m22*m33;
	im.m11 = m02*m23*m30 - m03*m22*m30 + m03*m20*m32 - m00*m23*m32 - m02*m20*m33 + m00*m22*m33;
	im.m12 = m03*m12*m30 - m02*m13*m30 - m03*m10*m32 + m00*m13*m32 + m02*m10*m33 - m00*m12*m33;
	im.m13 = m02*m13*m20 - m03*m12*m20 + m03*m10*m22 - m00*m13*m22 - m02*m10*m23 + m00*m12*m23;
	im.m20 = m11*m23*m30 - m13*m21*m30 + m13*m20*m31 - m10*m23*m31 - m11*m20*m33 + m10*m21*m33;
	im.m21 = m03*m21*m30 - m01*m23*m30 - m03*m20*m31 + m00*m23*m31 + m01*m20*m33 - m00*m21*m33;
	im.m22 = m01*m13*m30 - m03*m11*m30 + m03*m10*m31 - m00*m13*m31 - m01*m10*m33 + m00*m11*m33;
	im.m23 = m03*m11*m20 - m01*m13*m20 - m03*m10*m21 + m00*m13*m21 + m01*m10*m23 - m00*m11*m23;
	im.m30 = m12*m21*m30 - m11*m22*m30 - m12*m20*m31 + m10*m22*m31 + m11*m20*m32 - m10*m21*m32;
	im.m31 = m01*m22*m30 - m02*m21*m30 + m02*m20*m31 - m00*m22*m31 - m01*m20*m32 + m00*m21*m32;
	im.m32 = m02*m11*m30 - m01*m12*m30 - m02*m10*m31 + m00*m12*m31 + m01*m10*m32 - m00*m11*m32;
	im.m33 = m01*m12*m20 - m02*m11*m20 + m02*m10*m21 - m00*m12*m21 - m01*m10*m22 + m00*m11*m22;
	im.scale(1/determinant());
	return im;
}

/** calculates determinant */
float Matrix4x4::determinant() {
	float value;
	value =
		m03 * m12 * m21 * m30-m02 * m13 * m21 * m30-m03 * m11 * m22 * m30+m01 * m13 * m22 * m30+
		m02 * m11 * m23 * m30-m01 * m12 * m23 * m30-m03 * m12 * m20 * m31+m02 * m13 * m20 * m31+
		m03 * m10 * m22 * m31-m00 * m13 * m22 * m31-m02 * m10 * m23 * m31+m00 * m12 * m23 * m31+
		m03 * m11 * m20 * m32-m01 * m13 * m20 * m32-m03 * m10 * m21 * m32+m00 * m13 * m21 * m32+
		m01 * m10 * m23 * m32-m00 * m11 * m23 * m32-m02 * m11 * m20 * m33+m01 * m12 * m20 * m33+
		m02 * m10 * m21 * m33-m00 * m12 * m21 * m33-m01 * m10 * m22 * m33+m00 * m11 * m22 * m33;
	return value;
} 
