/*
 * Cloud of voxels (CoV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Creation Date: 2011
 * Modification Date: 2020
 */

#ifndef CAMERA_H
#define CAMERA_H

    #include "math.h"

    class Camera
    {
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
        * setPosition
        */
        void setPosition(const float x, const float y , const float z);


        /*
        * resetTransformation
        */
        void resetTransformation();


        /*
        * rotate
        */
        void rotate(const Vec3<float> axis, float angle);


        /*
        * translate
        */
        void translate(const Vec3<float> v);


        /*
        * getBasis
        */
        void getBasis(Mat3f* const basis);


        /*
        * Apply translation to a given coordinates
        */
        void reajust(Vec3<float>* const coordinates);


        private:
        Mat3f basis;
        Vec3<float> nearcenter;


        private:
        /*
        * updateNearInfo
        */
        void updateNearInfo(float* const m);

    };

#endif

