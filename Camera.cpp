/*
 * Cloud of voxels (COV) project
 * Author: by mcidclan. m.cid.clan@gmail.com
 * Date: 2011
 */

#include <string.h>
#include "./headers/Camera.h"

extern float midentity[16];

/*
 * projection matrix
 */
static float matprj[16] __attribute__ ((aligned (16)));


/*
 * rotation matrix
 */
static float matrot[16] __attribute__ ((aligned (16)));


/*
 * temporaries matrix
 */
static float mattmp_1[16] __attribute__ ((aligned (16)));
static float mattmp_2[16] __attribute__ ((aligned (16)));

/*
 * Constructor
 */
Camera::Camera()
{
	reset();

	this->nearcenter.x =
	this->nearcenter.y = 
	this->nearcenter.z = 0.0f;
}


/*
 * Destructor
 */
Camera::~Camera()
{
}


/*
 * setPerspective
 */
void Camera::setPerspective(const float fovy, const float aspect,
const float znear, const float zfar)
{
    const float vc = znear * tanf(fovy * M_PI / 360.0f);
    const float hc = fovy * aspect;
    this->setFrustum(-hc, hc, -vc, vc, znear, zfar);
}


/*
 * setFrustum (Opengl)
 */
void Camera::setFrustum(const float left, const float right, const float bottom,
const float top, const float znear, const float zfar)
{
	float	width = right - left,
			height = top - bottom,
			depth = zfar - znear;

	this->znear = znear;

	memset(matprj, 0x0, sizeof(matprj));

	matprj[0] = (2.0f * znear) / width;//E
	matprj[5] = (2.0f * znear) / height;//F
	matprj[8] = (right + left) / width;//A
	matprj[9] = (top + bottom) / height;//B
	matprj[10] = -(zfar + znear) / depth;//C
	matprj[11] = -1.0f;
	matprj[14] = -(2.0f * zfar * znear) / depth;//D
	matprj[15] = 1.0f;

	this->updateNearInfo(matprj);
}


/*
 * updateNearInfo
 */
void Camera::updateNearInfo(float *m)
{
	memcpy(&(this->basis.i), &m[0], sizeof(Vec3f));
	memcpy(&(this->basis.j), &m[4], sizeof(Vec3f));
	memcpy(&(this->basis.k), &m[8], sizeof(Vec3f));

	math::normalize(&(this->basis.i));
	math::normalize(&(this->basis.j));
	math::normalize(&(this->basis.k));
}


/*
 * orientation
 */
void Camera::setOrientation()
{
	
}


/*
 * position
 */
void Camera::setPosition(const float x, const float y , const float z)
{
	this->nearcenter.x = x;
	this->nearcenter.y = y;
	this->nearcenter.z = z;
}


/*
 * reset
 */
void Camera::reset()
{
	memset(matprj, 0x0, sizeof(matprj));
	matprj[0] =
	matprj[5] =
	matprj[10] =
	matprj[15] = 1.0f;

	resetTransformation();
}

/*
 * resetTransformation
 */
void Camera::resetTransformation()
{
	memset(matrot, 0x0, sizeof(matrot));
	matrot[0] =
	matrot[5] =
	matrot[10] =
	matrot[15] = 1.0f;
}


/*
 * rotate
 */
void Camera::rotate(const Vec3f axis, float angle)
{	
	math::eulerorientation(axis, angle, mattmp_1);
	math::mat4xmat4(matrot, mattmp_1, mattmp_2);

	memcpy(matrot, mattmp_2, sizeof(matrot));
	this->updateNearInfo(matrot);
}


/*
 * translate
 */
void Camera::translate(const Vec3f v)
{
	math::translate(v, matrot);
	this->nearcenter.x = matrot[12];
	this->nearcenter.y = matrot[13];
	this->nearcenter.z = matrot[14];
}


/*
 * getBasis
 */
void Camera::getBasis(Mat3f *basis)
{
	*basis = this->basis;
}


