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
        bool isPowerOfTwo(UI value, SUI* const level);


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
        const Vec3<T1> v2, Vec3<T2>* const v3)
        {
        v3->x = x + v2.x;
        v3->y = y + v2.y;
        v3->z = z + v2.z;
        }


        /*
        * vecadd
        */
        template<typename T1, typename T2, typename T3>
        void vecadd(T1* const v1, T2* const v2, T3* const v3)
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
        void vecadd(const T1 v1, T2* const v2)
        {
        v2->x += v1.x;
        v2->y += v1.y;
        v2->z += v1.z;	
        }


        /*
        * vecsub
        */
        template<typename T1, typename T2, typename T3>
        void vecsub(T1* const v1, T2* const v2, T3* const v3)
        {
        v3->x = v1->x - v2->x;
        v3->y = v1->y - v2->y;
        v3->z = v1->z - v2->z;	
        }


        /*
        * vecsub
        */
        template<typename T1, typename T2>
        void vecsub(const T1 v1, T2* const v2)
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
        void vecxscl(Vec3<T1>* const v, const T2 s)
        {
        v->x *= s;
        v->y *= s;
        v->z *= s;
        }


        /*
        * vecxscl
        */
        template <typename T1, typename T2, typename T3>
        void vecxscl(Vec3<T1>* const v1, const T2 s, Vec3<T3>* const v3)
        {
        v3->x = v1->x * s;
        v3->y = v1->y * s;
        v3->z = v1->z * s;
        }

        /*
        * cpvec
        */
        template <typename T1, typename T2>
        void cpvec(const T1 v1, T2* const v2)
        {
        v2->x = v1.x;
        v2->y = v1.y;
        v2->z = v1.z;
        }


        /*
        * mat4xmat4
        */
        void mat4xmat4(float* const m1, float* const m2, float* const m3);


        /*
        * getnorm
        */
        float getnorm(Vec3<float>* const v);


        /*
        * normalize
        */
        void normalize(Vec3<float>* const v);


        /*
        * eulerorientation
        */
        void eulerorientation(Vec3<float> axis, const float angle, float* const m);


        /*
        * translate
        */
        void translate(const Vec3<float> v, float* const m);


        /*
        * dotproduct
        */
        float dotproduct(Vec3<float>* const v1, Vec3<float>* const v2);


    }

#endif

