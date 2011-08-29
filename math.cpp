/*
 * Cloud of voxels (COV) project
 * Author: by mcidclan. m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/math.h"


//static 
float midentity[16] /*__aligned()*/ =
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
	 * vecxscl
	 */
	Vec3f vecxscl(Vec3f v, const float s)
	{
		v.x *= s;
		v.y *= s;
		v.z *= s;
		return v;
	}


	/*
	 * vecxscl
	 */
	void vecxscl(Vec3f *v, const float s)
	{
		v->x *= s;
		v->y *= s;
		v->z *= s;
	}


	/*
	 * mat4xmat4
	 */
	void mat4xmat4(float *m1, float *m2, float *m3)
	{
		unsigned char i = 0, j = 0, k = 0;
		float *row = NULL, *col = NULL;
 
		for(i = 0; i < 16; i += 4)
		{
			row = &(m1[i]);

			for(j = 0; j < 4; j++)
			{
				col = &(m2[j]);
				m3[k] = col[0]*row[0] + col[4]*row[1] + col[8]*row[2] + col[12]*row[3];
				k++;
			}
		}
	}


	/*
	 * getnorm
	 */
	float getnorm(Vec3f *v)
	{
		return sqrtf((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	}


	/*
	 * normalize
	 */
	void normalize(Vec3f *v)
	{
		const float norm = getnorm(v);

		if(norm != 0.0f)
		{
			v->x /= norm;
			v->y /= norm;
			v->z /= norm;
		}
	}


	/*
	 * eulerorientation
	 */
	void eulerorientation(Vec3f axis, const float angle, float *m)
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
	void translate(const Vec3f v, float *m)
	{
		m[12] = m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12];
		m[13] = m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13];
		m[14] = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14];
		m[15] = m[3] * v.x + m[7] * v.y + m[11] * v.z + m[15];
	}


}


