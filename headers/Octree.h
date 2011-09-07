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
			static SUI maxdepth;
			static SUI rootsize;

			static Vec3<SUI> locpos;


		public:
			/*
			 * Delete childreen
			 */
			static void delChildreen(Octant *octant);


			/*
			 * Init root information
			 */
			static void initRoot(SUI rootsize, SUI maxdepth, SUI curdepth,
			Octant *root);


			/*
			 * Init child
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
			 * Update locpos from the current octant's local position
			 */
			static void updateLocalPosition(Vec3<SI> v, Octant *octant);


	};

#endif


