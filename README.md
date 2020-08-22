cloud-of-voxels
===============
This is a basic Voxels to Pixels rendering project,

using Ray Tracing through an Octree.

For each Pixel, a Ray is generated and will go through the Octree,

searching for the first Voxel on its path. When the Ray hits the Voxel,

the corresponding Pixel is drawn to the screen.

<br/>

To export your model, use Blender 2.78c. Start Blender from command line

and open the file from which you want to export the model. Make sure than the

mesh is in "vertex paint" mode, then run the Python script. Once it's done,

replace the voxelmodels.cpp by the generated file and report the number of

voxels given by your prompt to voxelmodels.h. Note: To get a better display

quality, subdivide the mesh until it reduces the gaps between the vertices.

<br/>

From Windows compile by executing:

mingw32-make -f Makefile-Mingw clean; mingw32-make -f Makefile-Mingw

or from Linux: make clean; make;

Finally launch the program with: ./bin/cov.exe nomotion nologs or

./bin/cov.exe nomotion nologs stepx2 if it's to slow.

Available options are: nomotion, nologs, noneighbour, stepx2, stepx3 and stepx4.

<br/>

If you want to test different screen sizes, change the value of OCTREE_SIZE

in Render.h, this will automatically calculate the corresponding screen size.

Enjoy!
