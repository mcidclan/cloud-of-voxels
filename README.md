cloud-of-voxels
===============
This is a basic Voxels to Pixels rendering project,

using Ray Tracing through an Octree.

For each Pixel, a Ray is generated and will go through the Octree,

searching for the first Voxel on its path. When the Ray hits the Voxel,

the corresponding Pixel is drawn to the screen.

<br/>

To export your model, use Blender >= 2.58 <= 2.78c

open the Blender file and run the Python script.

Once it's done, replace the voxelmodels.cpp by the generated file.

<br/>

If you want to test different screen sizes, change the value of OCTREE_SIZE

in Render.h, this will automatically calculate the corresponding screen size.

Enjoy!
