/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef OCTREE_H
#define OCTREE_H

	#include "./Octant.h"


	class Octree
	{

		public:
			static UC lfid;
			static UC affectedfaces[3];

			static Vec3<SUI> locpos;

			static Vec3<float> *kbase;
            static Vec3<float> kbsample;
			static Vec3<float> raypos;


			static float raystep;
			static float depthray;
            static float lastraystep;
			static float raylength;
			static float colordepthstep;

			static Octant *curbit;
			static Octant *root;

            static float const RAYSTEP_MIN_UNIT;

		public:
			/*
			 * Delete childreen
			 */
			static void delChildreen(Octant *octant);


			/*
			 * initRoot
			 */
			static void initRoot(SUI rootsize, SUI maxdepth,
			const float raylength, Octant *root);


			/*
			 * setFacesCenter
			 */
			static void setFacesCenter(Octant *octant, const float half);


			/*
			 * initChild
			 */
			static void initChild(const UC i, const UC j, const UC k,
			Octant *parent);


			/*
			 * Add children to the current octant
			 */
			static void addChildren(Octant *octant);


			/*
			 * Set bit space
			 */
			static void setBit(Voxel *voxel, Octant *octant);


			/*
			 * initRayCast
			 */
			static void initRayCast(Vec3<float> *kbase);


			/*
			 * resetRayCast
			 */
			static void resetRayCast();


			/*
			 * rayCast
			 */
			static void rayCast();


			/*
			 * getEntryDot
			 */
			static void getNextEntryDot(Octant* octant,
			Vec3<float> *coordinates);


			/*
			 * addVoxels
			 */
			static void addVoxels(Voxel *voxels, const UI nvoxel);


            /*
             * addNeighborVoxels
             */
            static void addNeighborVoxels(Vec3<SI>* const coordinates);


			/*
			 * setColorDepth
			 */
			static unsigned char getColorDepth();


            /*
			 * rayToBorder
			 */
            static void rayToBorder(const float a, const float b, const float c);
	};


#endif


