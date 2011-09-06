/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef OCTANT_H
#define OCTANT_H

	#include ""


	class Octant
	{
		public:
			static Vec3sui curpos;

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
			 * get the local position in the current octant
			 */
			void getLocalPosition(Vec3f dot);


			/*
			 * Set bit space, corresponding to the current voxel
			 */
			void setBit(Vec4 *voxel);


			/*
			 *
			 */
			Voxel* getBit(const vec3f raypos);


		private:
			Octant ***children;


	};

#endif


