/*
 * Cloud of voxels (COV) project
 * Author: mcidclan. m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef ADDITIONAL_TYPE_H
#define ADDITIONAL_TYPE_H

	#include <stdio.h>
	#define UI unsigned int
	#define UC unsigned char

	typedef struct
	{
		short UI color;
		short int x, y, z;
	} Voxel;


	/*
	 * Vec2i
	 */
	typedef struct
	{
		int x, y;
	} Vec2i;


	/*
	 * Vec2ui
	 */
	typedef struct
	{
		UI x, y;
	} Vec2ui;


	/*
	 * Vec3f
	 */
	typedef struct
	{
		float x, y, z;
	} Vec3f;


	/*
	 * Mat3f
	 */
	typedef struct
	{
		Vec3f i, j, k;
	} Mat3f;


#endif


