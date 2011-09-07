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
			Vec3<SUI> pos;

			float cscoef;

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
			 *
			 */
			//Voxel* getBit(const vec3f raypos);


		private:


	};

#endif


