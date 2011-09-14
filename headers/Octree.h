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
			static SUI depth;

			static Vec3<SUI> center;
			static Vec3<SUI> locpos;
			static Vec3<float> raypos;
			static Vec3<float> raysrc;

			static Vec3<float> *kbase;

			static Vec3<float> kbase2;//

			static float depthray;
			static float raylength;
			static float colordepthstep;

			static Octant *curbit;
			static Octant *root;


		public:
			/*
			 * Delete childreen
			 */
			static void delChildreen(Octant *octant);


			/*
			 *
			 */
			static void initRoot(SUI rootsize, SUI maxdepth,
			const float raylength, Octant *root);


			/*
			 *
			 */
			static void setFacesCenter(Octant *octant, const float half);


			/*
			 * keepAffectedFaces()
			 */
			static void keepAffectedFaces();


			/*
			 *
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
			 * getNearestFace
			 */
			static void getNearestFace(Octant* octant, Vec3<float> *coordinates,
			UC *lid);


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
			 * setColorDepth
			 */
			static unsigned char getColorDepth();


	};


#endif


