/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef ADDITIONAL_MATH_H
#define ADDITIONAL_MATH_H

	#include <math.h>
	#include "./types.h"


	namespace math
	{


		/*
		 * getdecimal
		 */
		float getdecimal(const float s);


		/*
		 * vecadd
		 */
		template<typename T1, typename T2, typename T3>
		void vecadd(const T1 v1, const T2 v2, T3 *v3)
		{
			v3->x = v1.x + v2.x;
			v3->y = v1.y + v2.y;
			v3->z = v1.z + v2.z;	
		}


		/*
		 * vecadd
		 */
		template<typename T1, typename T2>
		void vecadd(const T1 v1, T2 *v2)
		{
			v2->x += v1.x;
			v2->y += v1.y;
			v2->z += v1.z;	
		}


		/*
		 * vecadd
		 */
		template<typename T1, typename T2>
		void vecsub(const T1 v1, T2 *v2)
		{
			v2->x -= v1.x;
			v2->y -= v1.y;
			v2->z -= v1.z;	
		}


		/*
		 * vecxscl
		 */
		template <typename T>
		T vecxscl(T v, const float s)
		{
			v.x *= s;
			v.y *= s;
			v.z *= s;
			return v;
		}


		/*
		 * vecxscl
		 */
		template <typename T1, typename T2>
		void cpvec(const T1 v1, T2 *v2)
		{
			v2->x = v1.x;
			v2->y = v1.y;
			v2->z = v1.z;
		}

		/*
		 * vecxscl
		 */
		template <typename T>
		void vecxscl(T *v, const float s)
		{
			v->x *= s;
			v->y *= s;
			v->z *= s;
		}


		/*
		 * mat4xmat4
		 */
		void mat4xmat4(float *m1, float *m2, float *m3);


		/*
		 * getnorm
		 */
		float getnorm(Vec3<float> *v);


		/*
		 * normalize
		 */
		void normalize(Vec3<float> *v);


		/*
		 * eulerorientation
		 */
		void eulerorientation(Vec3<float> axis, const float angle, float *m);


		/*
		 * translate
		 */
		void translate(const Vec3<float> v, float *m);


	}


#endif


