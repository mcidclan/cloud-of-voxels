/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef OCTREE_H
#define OCTREE_H

	#include "octant.h"


	class Octree
	{
		public:
			/*
			 *
			 */
			static void del(Octant *octant);


			/*
			 *
			 */
			static void setDimensions(short UI rootsize, short UI maxdepth);


			/*
			 *
			 */
			static void initChild(Octant *parent, const UC i, const UC j,
			const UC k);


			/*
			 * Add children to the current octant
			 */
			static void addChildren(Octant *octant);


			/*
			 * Set bit space
			 */
			static void setBit(Vec4 *voxel, Octant *octant);
	};

#endif


