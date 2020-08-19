cloud-of-voxels
===============
This is a basic Voxel to Pixel renderer project,

using Ray Casting through an Octree.

For each Pixel, a Ray is generated and will go through the Octree,

searching for the first Voxel on its path. When the Ray hits the Voxel,

the corresponding Pixel is drawn to the screen.

<br/>

To export your model via Blender,

open the Blender file and run the Python script.

One time is done, replace the voxelmodels.cpp by the generated file.

<br/>

If you want to test different screen size, change the value

of OCTREE_SIZE in Render.h

Enjoy!
