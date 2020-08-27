cloud-of-voxels
===============
This is a basic Voxels to Pixels rendering (voxel rasterizer) project,

using a CPU Ray Tracing process over an Octree. For each Pixel a Ray is

generated, and goes through the Octree searching for the first Voxel on

its path. When the Ray hits the Voxel, the corresponding Pixel is drawn

to the screen.

<br/>

By default the octree size is set to 256. That size is also the maximun size your

object could have with this configuration. You need Blender 2.78c to export your

model. Start Blender from command line and open the file from which you want to

export the model. If your mesh has been transformed, make sure to apply Location,

Rotation & Scale (CTRL+A). Put your mesh in "vertex paint" mode, then run the

Python script. Once it's done, replace the voxelmodels.cpp and voxelmodels.h by

the generated files. Note that the provided example contains gaps. From blender,

before exporting, you could subdivide your mesh, until you don't see gaps anymore

between its vertices.

<br/>

From Windows compile the code with: mingw32-make -f Makefile-Mingw clean;

mingw32-make -f Makefile-Mingw or from Linux: make clean; make;

Launch the program with: ./bin/cov no-motion no-logs no-siblings or with
 
./bin/cov no-motion no-logs stepx:2 if it's too slow. The available options are:
 
no-motion, no-logs, no-siblings, w:, h:, z:, ray:, step:, fps: o-size: and

accelerate.

<br/>

If you want to test different screen sizes use the w: and h: options. To change

the octree size use the o-size: option. The max ray length can be changed by

using the ray: option and the camera z position with the use of the z: option. 

By default the maximun fps is set at 25. You can ajust the value if you which,

by using the fps: option. To accelerate the ray tracing, enable the pre-searching

process, by the use of the accelerate option.

<br/>

With the given voxelmodels.cpp, once compiled, you can test the program with:

./bin/cov no-motion no-logs step:3 w:768 h:576 o-size:768 z:-370 ray:370 accelerate

Enjoy!
