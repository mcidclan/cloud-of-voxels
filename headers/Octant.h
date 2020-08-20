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
			Vec3<SI> center;
			Vec3<SI>* facescenter;

			SI half;

			bool isparent;

			Voxel* voxel;
			Octant*** children;
            
            Octant* parent;
            
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
			 * Adds children to the current octant
			 */
			void addChildren();
            
            
            /*
			 * Removes children from the current octant
			 */
			void removeChildren();
            

			/*
			 * initChild
			 */
			void initChild(const SUI i, const SUI j, const SUI k);


            /*
			 * setFacesCenter
			 */
			void setFacesCenter();

            
			/*
			 * Set bit space, corresponding to the current voxel
			 */
			void setBit(Voxel* const voxel);


			/*
			 * get the bit space corresponding to the current coordinates
			 */
			void getBit(const Vec3<SI> coordinates);


			/*
			 * getChildAt
			 */
			Octant* getChildAt(const Vec3<SI> coordinates);
	};

#endif


