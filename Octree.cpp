/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/Octree.h"

Octant* Octree::curbit;
Vec3<SI> Octree::center;

Octree::Octree() {
}


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
    
	this->ray = NULL;
    this->raylength = raylength;
	this->colordepthstep = (255.0f/(float)raylength);
    
    Octree::center = this->root->center;
}

/*
 * init
 */
void Octree::initBasis(Mat3f* const basis)
{
    this->basis = basis;
	this->kbase = &(basis->k);
}


/*
 * setRay
 */
void Octree::setRay(Vec3<float>* const ray) {
    this->ray = ray;
}


/*
 * resetRay
 */
void Octree::resetRay()
{
	// Moves the ray to its relative position in the octree
	this->depthray = 0.0f;
	math::vecadd(this->root->center, this->ray);
}


/*
 * rayTrace
 */
void Octree::rayTrace()
{
    if(this->ray != NULL)
    {
        this->resetRay();
        while(true)
        {
            Octree::curbit = this->root;
            // Searches for the deepest available octant from the root,
            // corresponding to the current ray position
            Octree::curbit->getBit({
                (SI)this->ray->x,
                (SI)this->ray->y,
                (SI)this->ray->z
            });
            if(Octree::curbit->voxel != NULL) break;
            
            // Calculates the new ray position
            this->getNextEntryDot(Octree::curbit);
            this->depthray += this->raystep;
            if(((SI)this->depthray) > this->raylength) break;
        }
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
    if(this->ray != NULL)
    {
        UC i = 0;
        this->raystep = ((float)this->root->size);

        i = (this->kbase->x > 0.0f) ? 1 : 0;
        rayToBorder(this->ray->x, octant->facescenter[i].x, this->kbase->x);

        i = (this->kbase->y > 0.0f) ? 3 : 2;
        rayToBorder(this->ray->y, octant->facescenter[i].y, this->kbase->y);
        
        i = (this->kbase->z > 0.0f) ? 5 : 4;
        rayToBorder(this->ray->z, octant->facescenter[i].z, this->kbase->z);

        if(this->raystep == 0)
        {
            this->raystep = RAYSTEP_MIN_UNIT;
        }
        this->ray->x += this->kbase->x * this->raystep;
        this->ray->y += this->kbase->y * this->raystep;
        this->ray->z += this->kbase->z * this->raystep;
    }
}


/*
 * addVoxels
 */
void Octree::addVoxels(Voxel* voxels, const UI nvoxel)
{    
	UI i = 0;
	while(i < nvoxel)
	{
        if(Options::noneighbour)
        {
            this->addSingleVoxel(&voxels[i].coordinates);
        } else this->addNeighborVoxels(&voxels[i].coordinates);
		i++;
	}
}


/*
 * add single voxel
 */
void Octree::addSingleVoxel(Vec3<SI>* const coordinates)
{
    Voxel* voxel = new Voxel();
    voxel->coordinates.x = coordinates->x;
    voxel->coordinates.y = coordinates->y;
    voxel->coordinates.z = coordinates->z;
    this->root->setBit(voxel);
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
