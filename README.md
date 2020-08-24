cloud-of-voxels
===============
This is a basic Voxels to Pixels rendering (voxel rasterizer) project,

using Ray Tracing through an Octree. For each Pixel a Ray is generated,

and will go through the Octree searching for the first Voxel on its path.

When the Ray hits the Voxel, the corresponding Pixel is drawn to the screen.

<br/>

To export your model, use Blender 2.78c. Start Blender from command line

and open the file from which you want to export the model. Make sure than the

mesh is in "vertex paint" mode, then run the Python script. Once it's done,

replace the voxelmodels.cpp and voxelmodels.h by the generated files. Note that

the provided example contains gaps. From blender, before exporting, you need to

subdivide the mesh, until you don't see gaps anymore between the vertices.

<br/>

From Windows compile the code with: mingw32-make -f Makefile-Mingw clean;

mingw32-make -f Makefile-Mingw or from Linux: make clean; make;

By default the octree size is set to 256. That size is also the maximun size your

object could have with this configuration. Launch the program with:

./bin/cov.exe nomotion nologs or with ./bin/cov.exe nomotion nologs stepx2 

if it's too slow. The available options are: nomotion, nologs, noneighbour,

stepx2, stepx3, stepx4, w:, h:, o:, r:, z: and fps:.

<br/>

If you want to test different screen sizes use the w: and h: options. To change

the octree size use the o: option. The max ray length can be changed by using

the r: option and the camera z position with the use of the z: option. 

By default the maximun fps is at 25. You can ajust the value if you which, by

using the fps: option.

<br/>

With the given voxelmodels.cpp compiled, launch the program with the

following: ./bin/cov.exe nomotion nologs stepx2 w:1024 h:576 o:1024 z:-370 r:370
 
Enjoy!
