/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Project date: 2011
 * File creation date: 2020
 */

#ifndef OPTIONS_H
#define OPTIONS_H

    #include "types.h"
    #include <map>
    #include <string>
    
    using namespace std;
    
    class Options {
        public:
            static bool nologs;
            static bool nomotion;
            static bool noneighbour;
            
            static UC PIXEL_STEP;
            static SUI SCR_WIDTH;
            static SUI SCR_HEIGHT;
            static SUI OCTREE_SIZE;
            static SUI SCR_HALF_WIDTH;
            static SUI SCR_HALF_HEIGHT;
            static SUI MAX_RAY_LENGTH;
            static LUI MAX_FRAME_TIME;            
            static SI CAM_Z_TRANSLATION;
            
            static void process(int argc, char **argv);
    };
    
#endif
