/*
 * Cloud of voxels (COV) project
 * Author: by mcidclan. m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef PARTITION_H
#define PARTITION_H

	#include "./math.h"

	class Partition
	{
		public:
			Voxel *curvoxel;
			Vec3f scanpos;
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
			void setTranslator(const Vec3f translator);

			/*
			 * setMaxDepth
			 */
			void setMaxDepth(const UI maxdepth);


			/*
			 * resetDepthScan
			 */
			void resetDepthScan(const Vec3f *kbase);


			/*
			 * depthScan
			 */
			void depthScan();

			
			/*
			 * setCenter
			 */
			Vec3f getCenter();


			/*
			 * getColorDepth
			 */
			unsigned char getColorDepth();


		private:
			Voxel ****bits;
			const Vec3f *kbase;

			Vec3f center;

			UI spacewidth;
			UI spaceheight;
			UI spacedepth;

			UI maxdepth;

			float colordepthstep;

		private:
			/*
			 * getCenter
			 */
			void setCenter();


	};


#endif


