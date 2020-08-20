/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/Octree.h"

Octant* Octree::curbit;
Vec3<SI> Octree::center;

/*
 * initRoot
 */
void Octree::initRoot(SUI size, SUI maxdepth, const SI raylength)
{
    this->root = new Octant();
    this->root->parent = NULL;
	this->root->depth = maxdepth;
	this->root->size = size;
	this->root->half = size/2;
	this->root->center.x =
	this->root->center.y =
	this->root->center.z = this->root->half;
    this->root->setFacesCenter();
    this->root->voxel = NULL;
	this->raylength = raylength;
	this->colordepthstep = (255.0f/(float)raylength);
    
    Octree::center = this->root->center;
}

/*
 * initRay
 */
void Octree::initRay(Mat3f* const basis)
{
    this->basis = basis;
	this->kbase = &(basis->k);
}


/*
 * resetRay
 */
void Octree::resetRay()
{
	//Moves the ray to its relative position in the octree
	this->depthray = 0.0f;
	math::vecadd(this->root->center, &this->raypos); //?
}


/*
 * rayTrace
 */
void Octree::rayTrace()
{
    while(true)
    {
        Octree::curbit = this->root;
        // Searches for the deepest available octant from the root,
        // corresponding to the current ray position
	    Octree::curbit->getBit({
            (SI)this->raypos.x,
            (SI)this->raypos.y,
            (SI)this->raypos.z
        });
	    if(Octree::curbit->voxel != NULL) break;
        
        // Calculates the new ray position
	    this->getNextEntryDot(Octree::curbit);
	    this->depthray += this->raystep;
	    if(((SI)this->depthray) > this->raylength) break;
    }
}


/*
 * rayToBorder
 */
void Octree::rayToBorder(const float a, const float b, const float c)
{
    if(c != 0.0f)
    {
        // Distance between the current ray position and the next potential
        // octant limit position
        const float borderdist = math::absf(b - a);
        if(borderdist != 0.0f)
        {
            // Number of step to be done to reach the next potential
            // octant limit position
            const float steps = (borderdist / math::absf(c));
            if(steps < this->raystep)
            {
                this->raystep = steps;
            }
        } else this->raystep = 0.0f;
    }
}


/*
 * getNextEntryDot
 */
void Octree::getNextEntryDot(Octant* octant)
{
    UC i = 0;
    this->raystep = ((float)this->root->size);

    i = (this->kbase->x > 0.0f) ? 1 : 0;
    rayToBorder(this->raypos.x, octant->facescenter[i].x, this->kbase->x);

    i = (this->kbase->y > 0.0f) ? 3 : 2;
    rayToBorder(this->raypos.y, octant->facescenter[i].y, this->kbase->y);
    
    i = (this->kbase->z > 0.0f) ? 5 : 4;
    rayToBorder(this->raypos.z, octant->facescenter[i].z, this->kbase->z);

    if(this->raystep == 0)
    {
        this->raystep = RAYSTEP_MIN_UNIT;
    }
	this->raypos.x += this->kbase->x * this->raystep;
	this->raypos.y += this->kbase->y * this->raystep;
	this->raypos.z += this->kbase->z * this->raystep;
}


/*
 * addVoxels
 */
void Octree::addVoxels(Voxel* voxels, const UI nvoxel)
{    
	UI i = 0;
	while(i < nvoxel)
	{
        this->addNeighborVoxels(&voxels[i].coordinates);
		i++;
	}
}


/*
 * addNeighborVoxels
 */
void Octree::addNeighborVoxels(Vec3<SI>* const coordinates)
{
    SI i = - 1;
    while(i < 2)
    {
        SI j = - 1;
        while(j < 2)
        {
            SI k = - 1;
            while(k < 2)
            {
                Voxel* voxel = new Voxel();
                voxel->coordinates.x = coordinates->x + i;
                voxel->coordinates.y = coordinates->y + j;
                voxel->coordinates.z = coordinates->z + k;
                this->root->setBit(voxel);
                k++;
            }
            j++;
        }
        i++;
    }
}


/*
 * setColorDepth
 */
unsigned char Octree::getColorDepth()
{
	const int c = 0xFF - (int)(this->depthray*this->colordepthstep);
	if(c <= 0)
	{
		return 0;
	}
	return c;
}
