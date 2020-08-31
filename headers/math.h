/*
 * Cloud of Voxels (CoV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Creation Date: 2011
 * Modification Date: 2020
 */

#ifndef ADDITIONAL_MATH_H
#define ADDITIONAL_MATH_H

	#include <math.h>
	#include "types.h"


	namespace math
	{
		/*
		 * getdecimal
		 */
		float getdecimal(const float s);

        float absf(const float v);

		/*
		 * vecadd
		 */
		template<typename Ta, typename Tb, typename Tc, typename T1, typename T2>
		void vecadd(const Ta x, const Tb y, const Tc z,
		const Vec3<T1> v2, Vec3<T2> *v3)
		{
			v3->x = x + v2.x;
			v3->y = y + v2.y;
			v3->z = z + v2.z;
		}


		/*
		 * vecadd
		 */
		template<typename T1, typename T2, typename T3>
		//void vecadd(const T1 v1, const T2 v2, T3 *v3)
		void vecadd(T1 *v1, T2 *v2, T3 *v3)
		{
			v3->x = v1->x + v2->x;
			v3->y = v1->y + v2->y;
			v3->z = v1->z + v2->z;	
		}


        /*
		 * vecadd
		 */
		template<typename T>
		const T vecadd(T v1, const T v2)
		{
            v1.x += v2.x;
            v1.y += v2.y;
            v1.z += v2.z;
			return v1;
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
		 * vecsub
		 */
		template<typename T1, typename T2, typename T3>
		//void vecsub(const T1 v1, const T2 v2, T3 *v3)
		void vecsub(T1 *v1, T2 *v2, T3 *v3)
		{
			v3->x = v1->x - v2->x;
			v3->y = v1->y - v2->y;
			v3->z = v1->z - v2->z;	
		}


		/*
		 * vecsub
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
		Vec3<T> vecxscl(Vec3<T> v, const float s)
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
		void vecxscl(Vec3<T1> *v, const T2 s)
		{
			v->x *= s;
			v->y *= s;
			v->z *= s;
		}


		/*
		 * vecxscl
		 */
		template <typename T1, typename T2, typename T3>
		void vecxscl(Vec3<T1> *v1, const T2 s, Vec3<T3> *v3)
		{
			v3->x = v1->x * s;
			v3->y = v1->y * s;
			v3->z = v1->z * s;
		}

		/*
		 * cpvec
		 */
		template <typename T1, typename T2>
		void cpvec(const T1 v1, T2 *v2)
		{
			v2->x = v1.x;
			v2->y = v1.y;
			v2->z = v1.z;
		}


		/*
		 * getMax
		 */
		/*template<typename T>
		T getwidest(Vec3<T> v)
		{
			if(fabs(v.x) < fabs(v.y)) v.x = v.y;
			if(fabs(v.x) < fabs(v.z)) v.x = v.z;
			return v.x;
		}*/


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


		/*
		 * dotproduct
		 */
		float dotproduct(Vec3<float> *v1, Vec3<float> *v2);


	}


#endif


