/*
 * Cloud of Voxels (CoV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Creation Date: 2011
 * Modification Date: 2020
 */

#include "./headers/math.h"


/*
 * midentity
 */
const float midentity[16] __attribute__ ((aligned (__BIGGEST_ALIGNMENT__))) =
{
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
};

namespace math
{
	/*
	 * getdecimal
	 */
	float getdecimal(const float s)
	{
		const int integer = ((int)s);
		return s - ((float)integer);
	}


	/*
	 * mat4xmat4
	 */
	void mat4xmat4(float* const m1, float* const m2, float* const m3)
	{
		unsigned char
		i = 0,
		j = 0,
		k = 0;

		float
		*rw = NULL,
		*cl = NULL;
 

		for(i = 0; i < 16; i += 4)
		{
			rw = &(m1[i]);

			for(j = 0; j < 4; j++)
			{
				cl = &(m2[j]);
				m3[k] = cl[0]*rw[0] + cl[4]*rw[1] + cl[8]*rw[2] + cl[12]*rw[3];
				k++;
			}
		}
	}


	/*
	 * getnorm
	 */
	float getnorm(Vec3<float>* const v)
	{
		return sqrtf((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	}


	/*
	 * normalize
	 */
	void normalize(Vec3<float>* const v)
	{
		const float norm = getnorm(v);

		if(norm > 0.0f)
		{
			v->x /= norm;
			v->y /= norm;
			v->z /= norm;
		}
	}


	/*
	 * eulerorientation
	 */
	void eulerorientation(Vec3<float> axis, const float angle, float* const m)
	{
		float
		h = sinf(angle),
		i = cosf(angle),
		j = 1.0f - i;

		m[0] = axis.x * axis.x * j + i;
		m[1] = axis.y * axis.x * j + axis.z * h;
		m[2] = axis.z * axis.x * j - axis.y * h;
		m[3] = 0.0f;
		m[4] = axis.x * axis.y * j - axis.z * h;
		m[5] = axis.y * axis.y * j + i;
		m[6] = axis.z * axis.y * j + axis.x * h;
		m[7] = 0.0f;

		m[8] = axis.x * axis.z * j + axis.y * h;
		m[9] = axis.y * axis.z * j - axis.x * h;
		m[10] = axis.z * axis.z * j + i;
		m[11] = 0.0f;

		m[12] = 0.0f;
		m[13] = 0.0f;
		m[14] = 0.0f;
		m[15] = 1.0f;
	}


	/*
	 * translate
	 */
	void translate(const Vec3<float> v, float* const m)
	{
		m[12] = m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12];
		m[13] = m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13];
		m[14] = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14];
		m[15] = m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15];
	}


	float dotproduct(Vec3<float>* const v1, Vec3<float>* const v2)
	{
		return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
	}

    float absf(const float v)
    {
        if(v < 0.0f) return -v;
        return v;
    }
}


