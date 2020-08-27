/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef OCTREE_H
#define OCTREE_H

	#include "Octant.h"
    #define RAYSTEP_MIN_UNIT 1.0f


	class Octree
	{
        public:
           static Octant* curbit;
           static float half;
           static UI frame;
           
		private:
            Vec3<float>* ray;
			Octant* root;
            Mat3f* basis;
			
            Vec3<SUI> locpos;
			Vec3<float>* kbase;
            Vec3<float> kbsample;
            
            SI raylength;
			
            float raystep;
			float depthray;
			float colordepthstep;
            
            bool accelerated;
            Octant**** accelerator;
            
		public:
            /*
			 * constructor
			 */
            Octree();
            
            
            /*
			 * destructor
			 */
            ~Octree();
             
             
			/*
			 * setRay
			 */
            void setRay(Vec3<float>* const ray);
            
            
			/*
			 * initRoot
			 */
			void initRoot(SUI rootsize, SUI maxdepth, const SI raylength);


			/*
			 * initBasis
			 */
			void initBasis(Mat3f* const basis);


			/*
			 * rayTrace
			 */
			bool rayTrace();


			/*
			 * getEntryDot
			 */
			void getNextEntryDot(Octant* octant);


			/*
			 * addVoxels
			 */
			void addVoxels(Voxel* voxels, const UI nvoxel);

			/*
			 * add a single voxel
			 */
			void addSingleVoxel(const Voxel voxel);
            
            
            /*
             * addSiblings
             */
            void addSiblings(const Voxel voxel);


            /*
             * addSiblings
             */
            void addSmooths(const Voxel voxel);


			/*
			 * getColorDepth
			 */
			Color getColorDepth(const Color color);


            /*
			 * rayToBorder
			 */
            void rayToBorder(const float a, const float b, const float c);
            
            
            /*
             * initAccelerator
             */
             void initAccelerator();
            

        private:
            /*
			 * resetRay
			 */
			void resetRay();
            
            
            /*
             * fillAccelerator
             */
            void fillAccelerator();
            
            
            /*
             * destroyAccelerator
             */
            void destroyAccelerator();


            /*
             * getAccelerator
             */
            void createAccelerator();
            
            
            /*
             * getBit
             */
            Octant* getBit();
	};


#endif
