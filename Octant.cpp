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

	this->depth = 0;

	this->voxel = NULL;
	this->parent = this;
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
		printf("Add voxel at: %i %i %i\n", this->pos.x,this->pos.y,this->pos.z);
	} else
	{
		if(this->isparent == false)
		{
			Octree::addChildren(this);
			printf("children added in %i\n", depth);
		}

		Vec3<float> coordinates;
		math::vecadd(voxel->coordinates, Octree::center, &coordinates);

		this->getChildAt(&coordinates)->setBit(voxel);
	}
}


/*
 * getBit
 */
void Octant::getBit(Vec3<float> *coordinates)
{
	if(this->children == NULL)
	{
		Octree::curbit = this;
		return;
	} else
	{
		this->getChildAt(coordinates)->getBit(coordinates);
	}
}


/*
 * getChildAt
 */
static Vec3<float> r;
Octant* Octant::getChildAt(Vec3<float> *coordinates)
{
	math::vecsub(*coordinates, this->center, &r);
	math::normalize(&r);
	math::vecxscl(&r, 0.5f);
		
	r.x = r.x+1.0f;
	r.y = r.y+1.0f;
	r.z = r.z+1.0f;

	return &this->children[(int)r.x][(int)r.y][(int)r.z];
}


