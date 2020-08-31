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
	this->voxel.active = 0;
    this->voxel.color.a = 0;
	this->children = NULL;
    this->optimized = NULL;
	this->isparent = false;
    this->frame = 0;
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
    if(Options::OPTIMIZE_MEMORY)
    {
        UC i = 0;
        this->optimized = new Octant*[8];
        while(i < 8) {
            this->optimized[i] = new Octant();
            this->initChild(i % 2, (i / 2) % 2, i / 4);
            i++;
        }
    } else
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
                j++;
            }
            i++;
        }
    }
    this->isparent = true;
}


/*
 * Remove children from the current octant
 */
void Octant::removeChildren() {
    if(Options::OPTIMIZE_MEMORY)
    {
        UC i = 0;
        while(i < 8)
        {
            delete this->optimized[i];
            i++;
        }
        delete [] this->optimized;
    } else 
    {
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
}


/*
 * initChild
 */
Octant* Octant::getChildren(const UC i, const UC j , const UC k)
{
    if(Options::OPTIMIZE_MEMORY)
    {
        return this->optimized[i + j * 2 + k * 4];
    }
    return &(this->children[i][j][k]);
}


/*
 * initChild
 */
void Octant::initChild(const SUI i, const SUI j, const SUI k)
{   
	Octant* const child = this->getChildren(i, j, k);
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
    if(math::absf(voxel.coordinates.x) >= (Octree::half - 2) ||
        math::absf(voxel.coordinates.y) >= (Octree::half - 2) ||
        math::absf(voxel.coordinates.z) >= (Octree::half - 2)) return;
            
    if(this->depth == 0)
    {
        if(!this->voxel.active || voxel.color.a == 255) {
            this->voxel = voxel;
            if(!Options::nologs)
            {
                printf("Add voxel at: %i %i %i\n", this->pos.x,this->pos.y,this->pos.z);
            }
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
        this->getChildAt(voxel.coordinates)->setBit(voxel);
    }
}


/*
 * getBit
 */
Octant* Octant::getBit(const Vec3<SI> coordinates)
{
	if(this->children != NULL || this->optimized != NULL)
	{
		return this->getChildAt(coordinates)->getBit(coordinates);
	}
    return this;
}


/*
 * getChildAt
 */
Octant* Octant::getChildAt(const Vec3<SI> coordinates)
{
    const Vec3<UC> r = {
        (UC)(coordinates.x < this->center.x ? 0 : 1),
        (UC)(coordinates.y < this->center.y ? 0 : 1),
        (UC)(coordinates.z < this->center.z ? 0 : 1)
    };
	return this->getChildren(r.x, r.y, r.z);
}
