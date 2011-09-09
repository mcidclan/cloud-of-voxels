/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/Octant.h"
#include "./headers/Octree.h"

/*
 * Constructor
 */
Octant::Octant()
{
	this->pos.x =
	this->pos.y =
	this->pos.z = 0;

	this->depth = 1;

	this->voxel = NULL;
	this->parent = NULL;
	this->children = NULL;

	this->isparent = false;
}


/*
 * Destructor
 */
Octant::~Octant()
{
	Octree::delChildreen(this);
	this->isparent = false;
}


/*
 * Set the bit space corresponding to the current voxel
 */
void Octant::setBit(Voxel *voxel)
{
	if(this->depth == 1)
	{
		Octree::setBit(voxel, this);
	} else
	{
		if(this->isparent == false)
		{
			Octree::addChildren(this);
			printf("child added\n");
		}

		Vec3<SI> coordinates;
		math::vecadd(voxel->coordinates, Octree::center, &coordinates);

		Octree::updateLocalPosition(coordinates, this);

		this->children[Octree::locpos.x][Octree::locpos.y]
		[Octree::locpos.z].setBit(voxel);
	}
}


/*
 * get the bit space corresponding to the current coordinates
 */
void Octant::getBit(Vec3<float> *coordinates)
{
	if(this->children == NULL)
	{
		Octree::curbit = this;
		return;
	} else
	{
		Octree::updateLocalPosition(*coordinates, this);
		this->children[Octree::locpos.x][Octree::locpos.y]
		[Octree::locpos.z].getBit(coordinates);
	}
}


