/*
 * Cloud of voxels (COV) project
 * Author: by mcidclan. m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef VIEWPLANE_H
#define VIEWPLANE_H

	#include "./math.h"

	class Viewplane
	{
		public:
			Mat3f basis;

			Vec3f ivector;
			Vec3f jvector;


		public:
			/*
			 * Constructor
			 */
			Viewplane();


			/*
			 * Destructor
			 */
			~Viewplane();


			/*
			 * create
			 */
			void create(const UI hsize, const UI vsize);


			/*
			 * resetScan
			 */
			void resetScan();


			/*
			 * verticalScan
			 */
			bool verticalScan();


			/*
			 * horizontalScan
			 */
			bool horizontalScan();


			/*
			 * scan
			 */
			bool scan();


			/*
			 * scan
			 */
			void getScanPosition(Vec3f *scanpos);


		private:
			bool firsthscan;
			bool lastscan;

			int vscan;
			int hscan;
			Vec2i hlimit;
			Vec2i vlimit;

			short UI hid;

			Vec3f *ivectors;
	};


#endif


