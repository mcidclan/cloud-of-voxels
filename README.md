cloud-of-voxels
===============
This is a basic Voxels to Pixels rendering (voxel rasterizer) project, using a

CPU Ray Tracing process over an Octree. For each Pixel a Ray is generated, and

goes through the Octree searching for the first Voxel on its path. When the Ray

hits the Voxel, the corresponding Pixel is drawn to the screen.

<br/>

By default the octree size is set to 256. That size is also the maximun size your

object could have with this configuration. You need Blender 2.78c to export your

model. Start Blender from command line and open the file from which you want to

export the model. If your mesh has been transformed, make sure to apply Location,

Rotation & Scale (CTRL+A). In the middle of the scene add a lattice, then on your

mesh add a "Remesh" modifier. Change the octree depth value, util the size of the

blocks fits with the lattice, modify the scale value in the modifier if needed.

Apply the modifier. Edit the mesh, select all the faces and choose "Shade Smooth"

from the Faces menu (CTRL+F). Then, add the modifiers "Triangulate" and "Smooth".

Increase the values in smooth if necessary. In bake, select "Bake to Vertex Color".

Put your mesh in "Vertex Paint" mode then run Bake in "Full Render" mode. Disable

the modifiers before running the Python script. Once it's done, replace the

voxelmodels.cpp and voxelmodels.h by the generated files.

<br/>

From Windows compile the code with: mingw32-make -f Makefile-Mingw clean;

mingw32-make -f Makefile-Mingw or from Linux: make clean; make;

Launch the program with: ./bin/cov no-motion no-logs or with
 
./bin/cov no-motion no-logs smooth-siblings stepx:2 if it's too slow.

<br/>

Available options:

no-logs .............. Disable useless log
no-motion ............ Disable the default motion
accelerate ........... Enable the pre-searching process
transparency ......... Enable transparency
hard-siblings ........ Force additionnal voxels arround each voxel.
mooth-siblings ....... Force smoother additionnal voxels arround each voxel.
avoid-scan-glitches .. Try to avoid glitches in real-time
w: ................... Sets the view render width
h: ................... Sets the view render height
z: ................... Sets the camera z position
r: ................... Changes the default value of the camera step angle
ray: ................. Set the max ray length
fps:  ................ Changes the default max fps value
step: ................ Changes the default scan x and y step pixel 
octree-size: ......... Changes the default octree size
voxel-shell-type: .... Activates transparent voxel shell (xl, normal, lite)
voxel-shell-rgba: .... Affects a specific RGBA color to the voxel shell (0xFFFFFFFF). 

<br/>

With the given voxelmodels.cpp, once compiled, you can test the program with:

./bin/cov no-motion no-logs step:2 w:512 h:512 octree-size:512 z:-256 ray:256 accelerate

Enjoy!
