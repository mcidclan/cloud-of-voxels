cloud-of-voxels
===============
This is a basic Voxels to Pixels rendering (voxel rasterizer) project, using a<br/>
CPU Ray Tracing process over an Octree. For each Pixel a Ray is generated, and<br/>
goes through the Octree searching for the first Voxel on its path. When the Ray<br/>
hits the Voxel, the corresponding Pixel is drawn to the screen.<br/>

<br/>

By default the octree size is set to 256. That size is also the maximun size your<br/>
object could have with this configuration. You need Blender 2.78c to export your<br/>
model. Start Blender from command line and open the file from which you want to<br/>
export the model. If your mesh has been transformed, make sure to apply Location,<br/>
Rotation & Scale (CTRL+A). In the middle of the scene add a lattice, then on your<br/>
mesh add a "Remesh" modifier. Change the octree depth value, util the size of the<br/>
blocks fits with the lattice, modify the scale value in the modifier if needed.<br/>
Apply the modifier. Edit the mesh, select all the faces and choose "Shade Smooth"<br/>
from the Faces menu (CTRL+F). Then, add the modifiers "Triangulate" and "Smooth".<br/>
Increase the values in smooth if necessary. In bake, select "Bake to Vertex Color".<br/>
Put your mesh in "Vertex Paint" mode then run Bake in "Full Render" mode. Disable<br/>
the modifiers before running the Python script. Once it's done, replace the<br/>
voxelmodels.cpp and voxelmodels.h by the generated files.<br/>

<br/>

From Windows compile the code with: mingw32-make -f Makefile-Mingw clean;<br/>
mingw32-make -f Makefile-Mingw or from Linux: make clean; make;<br/>
Launch the program with: ./bin/cov no-motion no-logs or with<br/>
./bin/cov no-motion no-logs smooth-siblings stepx:2 if it's too slow.<br/>

<br/>

Available options:
<br/>
no-logs &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Disable useless log<br/>
no-motion &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Disable the default motion<br/>
accelerate &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Enable the pre-searching process<br/>
transparency &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Enable transparency<br/>
hard-siblings &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Force additionnal voxels arround each voxel.<br/>
mooth-siblings:_________Force smoother additionnal voxels arround each voxel.<br/>
avoid-scan-glitches:___Try to avoid glitches in real-time<br/>
w:_____________________Sets the view render width<br/>
h:_____________________Sets the view render height<br/>
z:_____________________Sets the camera z position<br/>
r:_____________________Changes the default value of the camera step angle<br/>
ray:___________________Set the max ray length<br/>
fps:___________________Changes the default max fps value<br/>
step:__________________Changes the default scan x and y step pixel<br/>
octree-size:___________Changes the default octree size<br/>
voxel-shell-type:______Activates transparent voxel shell (xl, normal, lite)<br/>
voxel-shell-rgba:______Affects a specific RGBA color to the voxel shell (0xFFFFFFFF).<br/>

<br/>

With the given voxelmodels.cpp, once compiled on linux test the program with: <br/>
./bin/cov no-motion step:1 w:128 h:128 octree-size:128 z:-64 ray:64 fps:60 \ <br/>
    no-logs accelerate voxel-shell-type:normal voxel-shell-rgba:0xFF808020 \ <br/>
    max-voxels-by-ray:2<br/>
<br/>
or width powershell:<br/>
./bin/cov no-motion step:1 w:128 h:128 octree-size:128 z:-64 ray:64 fps:60 &grave;<br/>
    no-logs accelerate voxel-shell-type:normal voxel-shell-rgba:0xFF808020 &grave;<br/>
    max-voxels-by-ray:2<br/>
<br/>
Enjoy!
