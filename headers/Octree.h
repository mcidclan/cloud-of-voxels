/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef OCTREE_H
#define OCTREE_H

	#include "./Octant.h"
    #define RAYSTEP_MIN_UNIT 1.0f;


	class Octree
	{
        public:
           static Octant* curbit;
           static Vec3<SI> center;
           
           Vec3<float> raypos;
           
		private:
			//UC lfid;
			//UC affectedfaces[3];
            Octant* root;
            Mat3f* basis;
			
            Vec3<SUI> locpos;
			Vec3<float>* kbase;
            Vec3<float> kbsample;
            
            SI raylength;
			
            float raystep;
			float depthray;
			float colordepthstep;
			
            
		public:
			/*
			 * initRoot
			 */
			void initRoot(SUI rootsize, SUI maxdepth, const SI raylength);


			/*
			 * initRayCast
			 */
			void initRayCast(Mat3f* const basis);


			/*
			 * resetRayCast
			 */
			void resetRayCast();


			/*
			 * rayCast
			 */
			void rayCast();


			/*
			 * getEntryDot
			 */
			void getNextEntryDot(Octant* octant);


			/*
			 * addVoxels
			 */
			void addVoxels(Voxel* voxels, const UI nvoxel);


            /*
             * addNeighborVoxels
             */
            void addNeighborVoxels(Vec3<SI>* const coordinates);


			/*
			 * setColorDepth
			 */
			unsigned char getColorDepth();


            /*
			 * rayToBorder
			 */
            void rayToBorder(const float a, const float b, const float c);
	};


#endif
