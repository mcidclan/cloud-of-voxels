/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef OCTANT_H
#define OCTANT_H

	#include "./math.h"


	class Octant
	{
		public:
			SUI size;
			SUI depth;
			Vec3<SI> pos;
			Vec3<float> center;

			float scoef;

			bool isparent;

			Voxel *voxel;
			Octant *parent;
			Octant ***children;


		public:
			/*
			 * Constructor
			 */
			Octant();


			/*
			 * Destructor
			 */
			~Octant();


			/*
			 * Set bit space, corresponding to the current voxel
			 */
			void setBit(Voxel *voxel);


			/*
			 * get the bit space corresponding to the current coordinates
			 */
			void getBit(Vec3<float> *coordinates);


			/*
			 * getChildAt
			 */
			Octant* getChildAt(Vec3<float> *coordinates);


		private:


	};

#endif


