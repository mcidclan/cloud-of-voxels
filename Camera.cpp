/*
 * Cloud of voxels (CoV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Creation Date: 2011
 * Modification Date: 2020
 */

#include "./headers/Camera.h"


/*
 * extern midentity
 */
extern const float midentity[16];


/*
 * rotation matrix
 */
static float matrot[16] __attribute__ ((aligned (__BIGGEST_ALIGNMENT__)));


/*
 * temporaries matrix
 */
static float mattmp_1[16] __attribute__ ((aligned (__BIGGEST_ALIGNMENT__)));
static float mattmp_2[16] __attribute__ ((aligned (__BIGGEST_ALIGNMENT__)));


/*
 * Constructor
 */
Camera::Camera()
{
	this->resetTransformation();
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
 * updateNearInfo
 */
void Camera::updateNearInfo(float* const m)
{
	memcpy(&(this->basis.i), &m[0], sizeof(Vec3<float>));
	memcpy(&(this->basis.j), &m[4], sizeof(Vec3<float>));
	memcpy(&(this->basis.k), &m[8], sizeof(Vec3<float>));

	math::normalize(&(this->basis.i));
	math::normalize(&(this->basis.j));
	math::normalize(&(this->basis.k));
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
void Camera::rotate(const Vec3<float> axis, float angle)
{	
	math::eulerorientation(axis, angle, mattmp_1);
	math::mat4xmat4(matrot, mattmp_1, mattmp_2);

	memcpy(matrot, mattmp_2, sizeof(matrot));
	this->updateNearInfo(matrot);
}


/*
 * translate
 */
void Camera::translate(const Vec3<float> v)
{
	math::translate(v, matrot);
	this->nearcenter.x = matrot[12];
	this->nearcenter.y = matrot[13];
	this->nearcenter.z = matrot[14];
}


/*
 * getBasis
 */
void Camera::getBasis(Mat3f* const basis)
{
	*basis = this->basis;
}


/*
 * Reajust the given coordinates to the camera center
 */
void Camera::reajust(Vec3<float>* const coordinates)
{
    math::vecadd(this->nearcenter, coordinates);
}
