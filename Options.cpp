/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Project date: 2011
 * File creation date: 2020
 */
 
#include "./headers/Options.h"

UC Options::PIXEL_STEP = 1;

bool Options::nologs = false;
bool Options::nomotion = false;
bool Options::nosiblings = false;
bool Options::ACCELERATED = false;

SUI Options::SCR_WIDTH = 256;
SUI Options::SCR_HEIGHT = 256;
SUI Options::OCTREE_SIZE = 0;
SUI Options::SCR_HALF_WIDTH = 128;
SUI Options::SCR_HALF_HEIGHT = 128;
SUI Options::MAX_RAY_LENGTH = 0;
LUI Options::MAX_FRAME_TIME = 25;
SI Options::CAM_Z_TRANSLATION = 0;

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
        } else if(name.find("o-size:") == 0)
        {
            Options::OCTREE_SIZE = stoi(name.substr(7));
        } else options[name] = true;
        i++;
    }
    
    printf("Max fps: %lu\n", MAX_FRAME_TIME);
    Options::MAX_FRAME_TIME = (LUI)(1000000.0f*(1.0f/Options::MAX_FRAME_TIME));
    printf("Max frame time: %lu microseconds\n", MAX_FRAME_TIME);
    
    Options::nologs = options.find("no-logs") != options.end();
    Options::nomotion = options.find("no-motion") != options.end();
    Options::nosiblings = options.find("no-siblings") != options.end();
    Options::ACCELERATED = options.find("accelerate") != options.end();
        
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
    
    printf("Width:%d, Height:%d\nOctree Size:%d\nMax Ray Length: %d\nZcam: %d\n",
    Options::SCR_WIDTH, Options::SCR_HEIGHT, Options::OCTREE_SIZE,
    Options::MAX_RAY_LENGTH, Options::CAM_Z_TRANSLATION);
    printf("Pixel Step:%d\n", Options::PIXEL_STEP);
}
