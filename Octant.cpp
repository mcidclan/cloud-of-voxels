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
	this->voxel.color = 0x00;
	this->children = NULL;
	this->isparent = false;
}


/*
 * Destructor
 */
Octant::~Octant()
{
	this->removeChildren();
	delete [] this->facescenter;
}


/*
 * Add children to the current octant
 */
void Octant::addChildren()
{
	UC
	i = 0,
	j = 0;
	this->children = new Octant**[2];
	while(i < 2)
	{
		this->children[i] = new Octant*[2];
		j = 0;
		while(j < 2)
		{
			this->children[i][j] = new Octant[2];
			this->initChild(i, j, 0);
			this->initChild(i, j, 1);
			this->isparent = true;
			j++;
		}
		i++;
	}
}


/*
 * Remove children from the current octant
 */
void Octant::removeChildren() {
	UI
	i = 0,
	j = 0;
	while(i < 2)
	{
		j = 0;
		while(j < 2)
		{
			delete [] this->children[i][j];
			j++;
		}
		delete [] this->children[i];
		i++;
	}
	delete [] this->children;
}


/*
 * initChild
 */
void Octant::initChild(const SUI i, const SUI j, const SUI k)
{
	Octant* const child = &(this->children[i][j][k]);
    child->parent = this;
	child->depth = this->depth - 1;
	child->size = this->size / 2;
	
    math::cpvec(this->pos, &child->pos);
    child->pos.x += i * child->size;
	child->pos.y += j * child->size;
	child->pos.z += k * child->size;
	
    math::cpvec(child->pos, &child->center);
    child->half = ((float)child->size) / 2.0f;
	child->center.x += child->half;
	child->center.y += child->half;
	child->center.z += child->half;
    
	child->setFacesCenter();
}


/*
 * setFacesCenter
 */
void Octant::setFacesCenter()
{
	this->facescenter = new Vec3<SI>[6];
    math::vecadd(-this->half, 0, 0, this->center, &this->facescenter[0]);
	math::vecadd(this->half, 0, 0, this->center, &this->facescenter[1]);
	math::vecadd(0, -this->half, 0, this->center, &this->facescenter[2]);
	math::vecadd(0, this->half, 0, this->center, &this->facescenter[3]);
	math::vecadd(0, 0, -this->half, this->center, &this->facescenter[4]);
	math::vecadd(0, 0, this->half, this->center, &this->facescenter[5]);
}


/*
 * Set the bit space corresponding to the current voxel
 */
void Octant::setBit(const Voxel voxel)
{
    if(this->voxel.color == 0x00)
    {
        if(this->depth == 1)
        {
            this->voxel = voxel;
            if(!Options::nologs)
            {
                printf("Add voxel at: %i %i %i\n", this->pos.x,this->pos.y,this->pos.z);
            }
        } else
        {
            if(this->isparent == false)
            {
                this->addChildren();
                if(!Options::nologs)
                {
                    printf("children added in level %i\n", depth);
                }
            }
            Vec3<SI> coordinates = math::vecadd(voxel.coordinates, Octree::center);
            this->getChildAt(coordinates)->setBit(voxel);
        }
    }
}


/*
 * getBit
 */
void Octant::getBit(const Vec3<SI> coordinates)
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
Octant* Octant::getChildAt(const Vec3<SI> coordinates)
{
    const Vec3<UC> r = {
        (UC)(coordinates.x - this->center.x < 0.0f ? 0 : 1),
        (UC)(coordinates.y - this->center.y < 0.0f ? 0 : 1),
        (UC)(coordinates.z - this->center.z < 0.0f ? 0 : 1)
    };
	return &this->children[r.x][r.y][r.z];
}
