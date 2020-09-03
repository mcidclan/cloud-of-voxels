/*
 * Cloud of Voxels (CoV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Creation Date: 2011
 * Modification Date: 2020
 */

#ifndef OCTREE_H
#define OCTREE_H

	#include "Octant.h"
    #define RAYSTEP_MIN_UNIT 1.0f


	class Octree
	{
        public:
           static float size;
           static float half;
           
		private:
            Vec3<float>* ray;
			Octant* root;
            Mat3f* basis;
			
            Vec3<SUI> locpos;
			Vec3<float>* kbase;
            Vec3<float> kbsample;
            
            SI raylength;
			
            float raystep;
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
			bool rayTrace(vector<DynamicVoxel>* const voxels);


			/*
			 * addVoxels
			 */
			void addVoxels(Voxel* voxels, const UI nvoxel);
            

			/*
			 * getColorDepth
			 */
			Color getColorDepth(const DynamicVoxel* const dynamic);
            Color getColorDepth(const UC r, const UC g, const UC b, const float depth);

            
            /*
             * initAccelerator
             */
             void initAccelerator();
            

        private:
            /*
			 * getEntryDot
			 */
			void getNextEntryDot(Octant* octant);
            
            /*
			 * add a single voxel
			 */
			void addSingleVoxel(Voxel* const voxel);


            /*
             * addSiblings
             */
            void addSmooths(Voxel* const voxel);


            /*
             * addShellXL
             */
             void addShellXL(const Voxel voxel);


            /*
             * addShellLite
             */
             void addShellLite(const Voxel voxel);
            
            /*
             * addShell
             */
            void addShell(const Voxel voxel);
            
            /*
			 * rayToBorder
			 */
            void rayToBorder(const float a, const float b, const float c);
            
            
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
            
            
            /*
             * getNextBit
             */
            Octant* getNextBit(float* axis, const float side);


            /*
             * avoidScanGlitches
             */
            void avoidScanGlitches(Octant** const curbit);
	};


#endif
