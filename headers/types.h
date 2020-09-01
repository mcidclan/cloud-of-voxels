/*
 * Cloud of Voxels (CoV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Creation Date: 2011
 * Modification Date: 2020
 */

#ifndef ADDITIONAL_TYPE_H
#define ADDITIONAL_TYPE_H

	#include <stdio.h>
    #include <vector>
    using namespace std;
    
	#define UC unsigned char
	#define SI short int
	#define UI unsigned int
	#define SUI short unsigned int
	#define LUI long unsigned int

    #ifdef PSP
    #define M_PI 3.14159265358979323846
    #endif
    
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
	 * Color
	 */
    typedef struct
    {
        UC r, g, b, a;
    } Color;


	/*
	 * Voxel
	 */
	typedef struct
	{
        Vec3<SI> coordinates;
        UI color;        
	} Voxel;


	typedef struct
	{
        float depth;
        Voxel* voxel;
	} DynamicVoxel;

#endif


