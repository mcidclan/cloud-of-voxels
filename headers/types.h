/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef ADDITIONAL_TYPE_H
#define ADDITIONAL_TYPE_H

	#include <stdio.h>

	#define UC unsigned char

	#define SI short int
	#define UI unsigned int
	#define SUI short unsigned int


	/*
	 * Vec2
	 */
	template <typename T>
	struct Vec2
	{
		T x, y;
	};


	/*
	 * Vec3
	 */
	template <typename T>
	struct Vec3
	{
		T x, y, z;
	};


	/*
	 * Mat3f
	 */
	typedef struct
	{
		Vec3<float> i, j, k;
	} Mat3f;


	/*
	 * Voxel
	 */
	typedef struct
	{
		SUI color;
		Vec3<SI> coordinates;
	} Voxel;


#endif


