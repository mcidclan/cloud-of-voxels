cloud-of-voxels
===============
This is a basic Voxels to Pixels rendering project, using Ray Tracing through

an Octree. For each Pixel, a Ray is generated and will go through the Octree,

searching for the first Voxel on its path. When the Ray hits the Voxel, the

corresponding Pixel is drawn to the screen.

<br/>

To export your model, use Blender 2.78c. Start Blender from command line

and open the file from which you want to export the model. Make sure than the

mesh is in "vertex paint" mode, then run the Python script. Once it's done,

replace the voxelmodels.cpp by the generated file and report the number of

voxels given by your prompt to voxelmodels.h. Note: To get a better display

quality, subdivide the mesh until it reduces the gaps between the vertices.

<br/>

From Windows compile the code with: mingw32-make -f Makefile-Mingw clean;

mingw32-make -f Makefile-Mingw or from Linux: make clean; make;

By default octree size is 256. That size is also the maximun size your

object could have with this configuration. Launch the program with:

./bin/cov.exe nomotion nologs or with ./bin/cov.exe nomotion nologs stepx2 

if it's too slow. The available options are: nomotion, nologs, noneighbour,

stepx2, stepx3, stepx4, w:, h:, o:, r: and z:. 

<br/>

If you want to test different screen sizes use the w: and h: options. To change

the octree size use the o: option. The max ray length can be changed by using

the r: option. And the camera z position with the use of the z: option. 

<br/>

With the given voxelmodels.cpp compiled, you launch the program with the

following: ./bin/cov.exe nomotion nologs stepx2 w:1024 h:576 o:1024 z:-370 r:370
 
Enjoy!
