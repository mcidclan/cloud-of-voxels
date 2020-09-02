/*
 * Cloud of Voxels (CoV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Creation Date: 2020
 * Modification Date: 2020
 */

#ifndef OPTIONS_H
#define OPTIONS_H

    #include "types.h"
    #include <map>
    #include <string>
    
    #ifdef PSP
    #include <pspctrl.h>
    #include <pspkernel.h>
    #include <pspdisplay.h>
    #include <psppower.h>
    #define printf pspDebugScreenPrintf
    #endif
    
    using namespace std;
        
    class Options {
        public:
            static float CAM_Y_ROTATION;
        
            static bool nologs;
            static bool nomotion;
            static bool ACCELERATED;
            static bool HARD_SIBLINGS;            
            static bool SMOOTH_SIBLINGS;
            static bool AVOID_SCAN_GLITCHES;
            static bool TRANSPARENCY;
            static bool INTERNAL_BLENDING;

            static UC VOXEL_SHELL_TYPE;
            static UC PIXEL_STEP;
            
            static SUI WIN_WIDTH;
            static SUI WIN_HEIGHT;
            static SUI SCR_WIDTH;
            static SUI SCR_HEIGHT;
            static SUI OCTREE_SIZE;
            static SUI SCR_HALF_WIDTH;
            static SUI SCR_HALF_HEIGHT;
            static SUI MAX_RAY_LENGTH;
            static SUI MAX_VOXELS_BY_RAY;
            static SUI SHELL_LITE_THICKNESS;
            static LUI MAX_FRAME_TIME;            
            static SI CAM_Z_TRANSLATION;
            
            static UI SHELL_COLOR;
            
            static void process(int argc, char **argv);
    };
    
#endif
