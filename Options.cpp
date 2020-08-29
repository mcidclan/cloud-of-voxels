/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Project date: 2011
 * File creation date: 2020
 */
 
#include "./headers/Options.h"

UC Options::PIXEL_STEP = 1;
UC Options::VOXEL_SHELL_TYPE = 0;

float Options::CAM_Y_ROTATION = 0.01745f;

bool Options::nologs = false;
bool Options::nomotion = false;
bool Options::ACCELERATED = false;
bool Options::HARD_SIBLINGS = false;
bool Options::SMOOTH_SIBLINGS = false;
bool Options::AVOID_SCAN_GLITCHES = false;
bool Options::TRANSPARENCY = false;

SUI Options::SCR_WIDTH = 256;
SUI Options::SCR_HEIGHT = 256;
SUI Options::OCTREE_SIZE = 0;
SUI Options::SCR_HALF_WIDTH = 128;
SUI Options::SCR_HALF_HEIGHT = 128;
SUI Options::MAX_RAY_LENGTH = 0;
LUI Options::MAX_FRAME_TIME = 25;
SI Options::CAM_Z_TRANSLATION = 0;

Color Options::SHELL_COLOR = {0, 0, 0, 0};

void Options::process(int argc, char **argv)
{
    int i = 1;
    bool ztrans = false;
    map<string, bool> options;
    while(i < argc)
    {    
        const string name = argv[i];
        if(name.find("w:") == 0)
        {
           Options::SCR_WIDTH = stoi(name.substr(2)); 
        } else if(name.find("h:") == 0)
        {
            Options::SCR_HEIGHT = stoi(name.substr(2));
        } else if(name.find("r:") == 0)
        {
            Options::CAM_Y_ROTATION *= (float)stoi(name.substr(2));
        } else if(name.find("z:") == 0)
        {
            Options::CAM_Z_TRANSLATION = stoi(name.substr(2));
            ztrans = true;
        } else if(name.find("ray:") == 0)
        {
            Options::MAX_RAY_LENGTH = stoi(name.substr(4));
        } else if(name.find("fps:") == 0)
        {
            Options::MAX_FRAME_TIME = stoi(name.substr(4));
        } else if(name.find("step:") == 0)
        {
            Options::PIXEL_STEP = stoi(name.substr(5));
        } else if(name.find("octree-size:") == 0)
        {
            Options::OCTREE_SIZE = stoi(name.substr(12));
        } else if(name.find("voxel-shell-type:") == 0)
        {
            const string type = name.substr(17);
            if(type == "xl")
            {
                Options::VOXEL_SHELL_TYPE = 2;
            } else Options::VOXEL_SHELL_TYPE = 1;
        } else if(name.find("voxel-shell-rgba:") == 0)
        {   
            UI color = stoll(name.substr(17), 0 , 16);
            Options::SHELL_COLOR.r = (color & 0xFF000000) >> 24;
            Options::SHELL_COLOR.g = (color & 0x00FF0000) >> 16;
            Options::SHELL_COLOR.b = (color & 0x0000FF00) >> 8;
            Options::SHELL_COLOR.a = (color & 0x000000FF);
        } else options[name] = true;
        i++;
    }
    
    Options::AVOID_SCAN_GLITCHES =
    options.find("avoid-scan-glitches") != options.end();
    Options::nologs = options.find("no-logs") != options.end();
    Options::nomotion = options.find("no-motion") != options.end();
    Options::ACCELERATED = options.find("accelerate") != options.end();
    Options::TRANSPARENCY = options.find("transparency") != options.end();
    Options::HARD_SIBLINGS = options.find("hard-siblings") != options.end();
    Options::SMOOTH_SIBLINGS = options.find("smooth-siblings") != options.end();
    
    if(Options::VOXEL_SHELL_TYPE)
    {
        Options::TRANSPARENCY = true;
    }
    
    printf("\n\nMax fps: %lu\n", MAX_FRAME_TIME);
    Options::MAX_FRAME_TIME = (LUI)(1000000.0f*(1.0f/Options::MAX_FRAME_TIME));
    
    if(Options::OCTREE_SIZE == 0)
    {
        (Options::OCTREE_SIZE = (Options::SCR_WIDTH/2)*2);
    }
    if(Options::MAX_RAY_LENGTH == 0)
    {
        Options::MAX_RAY_LENGTH = (Options::OCTREE_SIZE/2)*2;
    }
    
    if(!ztrans)
    {
        Options::CAM_Z_TRANSLATION = -(SI)(Options::OCTREE_SIZE/2);
    }
    
    Options::SCR_HALF_WIDTH = Options::SCR_WIDTH/2;
    Options::SCR_HALF_HEIGHT = Options::SCR_HEIGHT/2;  
    
    printf("Width: %d, Height: %d\n", Options::SCR_WIDTH, Options::SCR_HEIGHT);
    printf("Octree size: %d\n", Options::OCTREE_SIZE);
    printf("Max ray length: %d\n", Options::MAX_RAY_LENGTH);
    printf("Camera Z position: %d\n", Options::CAM_Z_TRANSLATION);
    printf("Pixel step: %d\n", Options::PIXEL_STEP);

    printf("Avoid glitches: %s\n", Options::AVOID_SCAN_GLITCHES ? "On" : "Off");
    printf("Smooth siblings: %s\n", Options::SMOOTH_SIBLINGS ? "On" : "Off");
    printf("Hard siblings: %s\n", Options::HARD_SIBLINGS ? "On" : "Off");
    printf("Transparency: %s\n", Options::TRANSPARENCY ? "On" : "Off");
    printf("Acceleration: %s\n", Options::ACCELERATED ? "On" : "Off");
    
    switch(Options::VOXEL_SHELL_TYPE)
    {
        case 1:
            printf("Voxel shell: normal\n");
            break;
        case 2:
            printf("Voxel shell: xl\n");
            break;
        default:
            printf("Voxel shell: Off\n");
    }
}
