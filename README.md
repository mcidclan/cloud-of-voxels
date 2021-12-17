cloud-of-voxels
===============
```
This is a basic CPU side Voxels to Pixels rendering (voxel raycaster) project,
using a process over an Octree to accelerate the ray. For each Pixel a Ray is
generated, and goes through the Octree searching for the first Voxel on its path.
When the Ray hits the Voxel, the corresponding Pixel is drawn to the screen.

By default the octree size is set to 256. That size is also the maximun size your
object could have with this configuration. You need Blender 2.78c to export your
model. Start Blender from command line and open the file from which you want to
export the model. If your mesh has been transformed, make sure to apply Location,
Rotation & Scale (CTRL+A). In the middle of the scene add a lattice, then on your
mesh add a "Remesh" modifier. Choose blocks, and change the octree depth value,
util the size of the blocks fits with the lattice, modify the scale value in the
modifier if needed. Apply the modifier. Edit the mesh, select all the faces and
choose "Shade Smooth" from the Faces menu (CTRL+F). Then, add the modifiers
"Triangulate" and "Smooth". Increase the values in smooth if necessary. In bake,
select "Bake to Vertex Color". Put your mesh in "Vertex Paint" mode then run Bake
in "Full Render" mode. Disable the modifiers before running the Python script
(given in the repo). Once it's done, replace the voxelmodels.cpp and voxelmodels.h
by the generated files.

From Windows compile the code with: mingw32-make -f Makefile-Mingw clean;
mingw32-make -f Makefile-Mingw or from Linux: make clean; make;
Launch the program with: ./bin/cov no-motion no-logs or with
./bin/cov no-motion no-logs stepx:2 if it's too slow.

Available options:
no-logs: ............... Disable useless log
no-motion: ............. Disable the default motion
accelerate: ............ Enable the pre-searching process
transparency: .......... Enable transparency
smooth-siblings: ....... Add additionnal voxels arround each voxel to reduce gaps
avoid-scan-glitches: ... Try to avoid glitches in real-time
w: ..................... Sets the view render width
h: ..................... Sets the view render height
z: ..................... Sets the camera z position
r: ..................... Changes the default value of the camera step angle
ray: ................... Set the max ray length
fps: ................... Changes the default max fps value
step: .................. Changes the default scan x and y step pixel
octree-size: ........... Changes the default octree size
voxel-shell-type: ...... Activates transparent voxel shell (xl, normal, lite)
voxel-shell-rgba: ...... Affects a specific RGBA color to the voxel shell (0xFFFFFFFF)
min-voxels-proximity: .. Minimum distance between the voxels for blending effect.
max-voxels-by-ray: ..... Maximum of voxels used for blending effect in one ray.
                         The default value is 1, and corresponds to max ray length.


With the given voxelmodels.cpp, once compiled on linux test the program with:
./bin/cov no-motion step:1 w:128 h:128 octree-size:256 z:-70 ray:80 no-logs \
    voxel-shell-type:xl voxel-shell-rgba:0xFF10F040 min-voxels-proximity:7 \
    accelerate fps:30
    
or with powershell:
./bin/cov no-motion step:1 w:128 h:128 octree-size:256 z:-70 ray:80 no-logs `
    voxel-shell-type:xl voxel-shell-rgba:0xFF10F040 min-voxels-proximity:7 `
    accelerate fps:30

Enjoy!
