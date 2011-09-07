/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef VIEWPLANE_H
#define VIEWPLANE_H

	#include "./math.h"

	class Viewplane
	{
		public:
			Mat3f basis;

			Vec3<float> ivector;
			Vec3<float> jvector;


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
			void getScanPosition(Vec3<float> *scanpos);


		private:
			bool firsthscan;
			bool lastscan;

			int vscan;
			int hscan;
			Vec2<int> hlimit;
			Vec2<int> vlimit;

			short UI hid;

			Vec3<float> *ivectors;
	};


#endif


