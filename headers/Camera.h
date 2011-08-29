/*
 * Cloud of voxels (COV) project
 * Author: by mcidclan. m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef CAMERA_H
#define CAMERA_H

	 #include "./math.h"


	class Camera
	{
		public:
			Vec3f nearcenter;


		public:
			/*
			 * Constructor
			 */
			Camera();


			/*
			 * Destructor
			 */
			~Camera();


			/*
			 * setPerspective
			 */
			void setPerspective(const float fovy, const float aspect,
			const float znear, const float zfar);


			/*
			 * setFrustum
			 */
			void setFrustum(const float a, const float b, const float c,
			const float d, const float e, const float g);


			/*
			 * orientation
			 */
			void setOrientation();


			/*
			 * setPosition
			 */
			void setPosition(const float x, const float y , const float z);


			/*
			 * reset
			 */
			void reset();


			/*
			 * resetTransformation
			 */
			void resetTransformation();


			/*
			 * rotate
			 */
			void rotate(const Vec3f axis, float angle);


			/*
			 * translate
			 */
			void translate(const Vec3f v);


			/*
			 * getBasis
			 */
			void getBasis(Mat3f *basis);


		private:
			float znear;
			Mat3f basis;


		private:
			/*
			 * updateNearInfo
			 */
			void updateNearInfo(float *m);

	};


#endif


