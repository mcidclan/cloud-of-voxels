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
		}

		Octree::updateLocalPosition(voxel->coordinates, this);
		this->children[Octree::locpos.x][Octree::locpos.y][Octree::locpos.z]
		.setBit(voxel);
	}
}


/*
 *
 */
/*Voxel* Octant::getBit(const vec3f raypos)
{
	
	if(this->isparent == true)
	{
		vecsub(raypos, this->pos, &Octant::curpos);
		vecxscl(&Octant::curpos, posfac);

		this->children[Octant::curpos.x][Octant::curpos.y][Octant::curpos.z]
		->getBit(raypos);
	}

	return this->voxel;
}*/


