/*
 * Cloud of Voxels (CoV) project
 * Author: mcidclan, m [.D'O'T.] cid [.D'O'T.] clan [.A'T.] gmail [.D'O'T.] com
 * Creation Date: 2011
 * Modification Date: 2020
 */

#ifndef OCTANT_H
#define OCTANT_H

    #include "math.h"
    #include "Options.h"

    typedef struct Octant
    {
        UC depth;
        Voxel* voxel;
        Octant* children;
        SI* facescenter;
        Vec3<SI> center;
        SI half;
    } Octant;


    class OctantManager
    {
        public:
        /*
        * Adds children to the current octant
        */
        static void init(Octant* const octant);


        /*
        * Adds children to the current octant
        */
        static void addChildren(Octant* const octant);


        /*
        * Removes children from the current octant
        */
        static void removeChildren(Octant* const octant);


        /*
        * initChild
        */
        static void initChild(Octant* const octant,
        const SUI i, const SUI j, const SUI k);


        /*
        * setFacesCenter
        */
        static void setFacesCenter(Octant* const octant);


        /*
        * initBit
        */
        static void initBit(Octant* const octant, const Voxel voxel);
        static void initBit(Octant* const octant, Voxel* const voxel);


        /*
        * Set bit space, corresponding to the current voxel
        */
        static void setBit(Octant* const octant,
        Voxel* const voxel, const bool dynamic = true);


        /*
        * get the bit space corresponding to the current coordinates
        */
        static Octant* getBit(Octant* const octant,
        const Vec3<SI> coordinates);


        /*
        * getChildAt
        */
        static Octant* getChildAt(Octant* const octant,
        const Vec3<SI> coordinates);


        /*
        * getChildren
        */
        static Octant* getChildren(Octant* const octant,
        const UC i, const UC j , const UC k);
    };

#endif
