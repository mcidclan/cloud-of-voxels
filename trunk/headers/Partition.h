/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef PARTITION_H
#define PARTITION_H

	#include "./math.h"

	class Partition
	{
		public:
			Voxel *curvoxel;
			Vec3<float> scanpos;
			UI curdepth;

		public:
			/*
			 * Constructor
			 */
			Partition();


			/*
			 * Destructor
			 */
			~Partition();

			
			/*
			 * create
			 */
			void create(const UI spacewidth,
			const UI spaceheight, const UI spacedepth);


			/*
			 * getBit
			 */
			void setBit(Voxel *voxel);


			/*
			 * setCurrentVoxel
			 */
			void setCurrentVoxel();


			/*
			 * setTranslator
			 */
			void setTranslator(const Vec3<float> translator);

			/*
			 * setMaxDepth
			 */
			void setMaxDepth(const UI maxdepth);


			/*
			 * resetDepthScan
			 */
			void resetDepthScan(const Vec3<float> *kbase);


			/*
			 * depthScan
			 */
			void depthScan();


			/*
			 * getColorDepth
			 */
			unsigned char getColorDepth();


		private:
			Voxel ****bits;
			const Vec3<float> *kbase;

			Vec3<float> center;

			UI spacewidth;
			UI spaceheight;
			UI spacedepth;

			UI maxdepth;

			float colordepthstep;

		private:
			/*
			 * setCenter
			 */
			void setCenter();


	};


#endif


