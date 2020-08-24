/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/Octree.h"

Octant* Octree::curbit;
float Octree::half;
UI Octree::frame;

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

    this->root->pos.x =
	this->root->pos.y =
	this->root->pos.z = -this->root->half;
	
    this->root->center.x =
	this->root->center.y =
	this->root->center.z = 0.0f;
    this->root->setFacesCenter();
    
	this->ray = NULL;
    this->raylength = raylength;
	this->colordepthstep = (1.0f/(float)raylength);
    
    Octree::frame = 0;
    Octree::half = this->root->half;
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
    Octree::curbit = this->root;
}


/*
 * rayTrace
 */
void Octree::rayTrace()
{
    if(this->ray != NULL)
    {
        this->resetRay();
        while(((SI)this->depthray) < this->raylength)
        {
            Octree::curbit = this->root;
            // Searches for the deepest available octant from the root,
            // corresponding to the current ray position
            Octree::curbit->getBit({
                (SI)this->ray->x,
                (SI)this->ray->y,
                (SI)this->ray->z
            });
            if(Octree::curbit->voxel.active) break;
            
            // Calculates the new ray position
            this->getNextEntryDot(Octree::curbit);
            this->depthray += this->raystep;
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
        if(borderdist > 0.0f)
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

        if(this->raystep < RAYSTEP_MIN_UNIT)
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
            this->addSingleVoxel(voxels[i]);
        } else this->addNeighborVoxels(voxels[i]);
		i++;
	}
}


/*
 * add single voxel
 */
void Octree::addSingleVoxel(const Voxel voxel)
{
    this->root->setBit(voxel);
}

/*
 * addNeighborVoxels
 */
void Octree::addNeighborVoxels(const Voxel voxel)
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
                Voxel v = voxel;
                v.coordinates.x += i;
                v.coordinates.y += j;
                v.coordinates.z += k;
                this->root->setBit(v);
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
Color Octree::getColorDepth(const Color color)
{
    const float darkness = 1.0f - this->depthray*this->colordepthstep;
	return {
        (UC)(color.r * darkness),
        (UC)(color.g * darkness),
        (UC)(color.b * darkness)
    };
}
