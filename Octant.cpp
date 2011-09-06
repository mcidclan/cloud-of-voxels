/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/Octant.h"


/*
 * Constructor
 */
Octant::Octant()
{
	this->pos.x =
	this->pos.y =
	this->pos.z = 0;

	this->voxel = NULL;
	this->childreen = NULL;
}


/*
 * Destructor
 */
Octant::~Octant()
{

	Octree::del(this);
}


/*
 * get the local position in the current octant
 */
void Octant::updateLocalPosition(Vec3f dot)
{
	vecsub(this->parent->pos, &dot);
	vecxscl(&dot, this->cscoef);
	Octree::locpos = (Vec3sui)dot;
}


/*
 * Set bit space, corresponding to the current voxel
 */
void Octant::setBit(Vec4 *voxel)
{
	updateLocalPosition(*dot);

	if(this->depth == 1)
	{
		setBit(this, voxel);
	} else
	{
		if(this->isparent == false)
		{
			this->addChildren();
		}

		Vec3sui &olpos = Octree::locpos;
		this->childreen[olpos.x][olpos.y][olpos.z]->setBit(voxel);
	}
}


/*
 *
 */
Voxel* Octant::getBit(const vec3f raypos)
{
	
	if(this->isparent == true)
	{
		vecsub(raypos, this->pos, &Octant::curpos);
		vecxscl(&Octant::curpos, posfac);

		this->children[Octant::curpos.x][Octant::curpos.y][Octant::curpos.z]
		->getBit(raypos);
	}

	return this->voxel;
}


