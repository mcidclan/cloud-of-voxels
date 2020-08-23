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
bool Options::noneighbour = false;

SUI Options::SCR_WIDTH = 256;
SUI Options::SCR_HEIGHT = 256;
SUI Options::OCTREE_SIZE = 0;
SUI Options::SCR_HALF_WIDTH = 128;
SUI Options::SCR_HALF_HEIGHT = 128;
SUI Options::MAX_RAY_LENGTH = 0;

SI Options::CAM_Z_TRANSLATION = 0;

void Options::process(int argc, char **argv)
{
    int i = 1;
    bool ztrans = false;
    map<string, bool> options;
    while(i < argc)
    {    
        const string name = argv[i];
        const size_t wp = name.find("w:");
        const size_t hp = name.find("h:");
        const size_t op = name.find("o:");
        const size_t zp = name.find("z:");
        const size_t rp = name.find("r:");
        
        if(wp != string::npos)
        {
           Options::SCR_WIDTH = stoi(name.substr(2)); 
        } else if(hp != string::npos)
        {
            Options::SCR_HEIGHT = stoi(name.substr(2));
        } else if(op != string::npos)
        {
            Options::OCTREE_SIZE = stoi(name.substr(2));
        } else if(rp != string::npos)
        {
            Options::MAX_RAY_LENGTH = stoi(name.substr(2));
        } else if(zp != string::npos)
        {
            ztrans = true;
            Options::CAM_Z_TRANSLATION = stoi(name.substr(2));
        } else options[name] = true;
        i++;
    }
    
    Options::nologs = options.find("nologs") != options.end();
    Options::nomotion = options.find("nomotion") != options.end();
    Options::noneighbour = options.find("noneighbour") != options.end();
    
    Options::PIXEL_STEP = options.find("stepx2") != options.end() ? 2 :
    options.find("stepx3") != options.end() ? 3 :
    options.find("stepx4") != options.end() ? 4 : Options::PIXEL_STEP;
    
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
