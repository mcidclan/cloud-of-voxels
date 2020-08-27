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
    this->accelerated = false;
}


Octree::~Octree() {
    delete this->root;
    this->destroyAccelerator();
}


/*
 *
 */
 void Octree::destroyAccelerator()
{
    UI i = 0, j =0;
	while(i < Options::OCTREE_SIZE)
    {
		j = 0;
		while(j < Options::OCTREE_SIZE)
        {
			delete [] this->accelerator[i][j];
            j++;
		}
		delete [] this->accelerator[i];
        i++;
	}
	delete [] this->accelerator;
}

/*
 *
 */
void Octree::createAccelerator()
{
    double msize = (pow(Options::OCTREE_SIZE, 3.0)*4.0) / pow(1000.0, 3);
    printf("Trying to allocate %f GB for accelerator\n", msize);
    this->accelerator = new Octant***[Options::OCTREE_SIZE];
    UI i = 0, j = 0;
    while(i < Options::OCTREE_SIZE)
    {
        this->accelerator[i] = new Octant**[Options::OCTREE_SIZE];
        j = 0;
        while(j < Options::OCTREE_SIZE)
        {
            this->accelerator[i][j] = new Octant*[Options::OCTREE_SIZE];
            j++;
        }
        i++;
    }
    printf("Accelerator created\n");
}


/*
 * fillAccelerator
 */
void Octree::fillAccelerator()
{
    printf("Filling the accelerator, please wait...\n");
    int i = 0, j = 0, k = 0;
    const SI OCTREE_HALF_SIZE = Options::OCTREE_SIZE / 2;
    while(i < Options::OCTREE_SIZE)
    {
        j = 0;
        const SI x = i - OCTREE_HALF_SIZE;
        while(j < Options::OCTREE_SIZE)
        {
            k = 0;
            const SI y = j - OCTREE_HALF_SIZE;
            while(k < Options::OCTREE_SIZE)
            {
                const SI z = k - OCTREE_HALF_SIZE;
                this->accelerator[i][j][k] = this->root->getBit({x, y, z});
                k++;
            }
            j++;
        }
        i++;
    }
    printf("Accelerator filled\n");
}

void Octree::initAccelerator()
{
    this->createAccelerator();
    this->fillAccelerator();
    this->accelerated = true;
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
 * initBasis
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
 * getBit
 */
Octant* Octree::getBit()
{    
    if(this->accelerated)
    {
        const SI x = (this->ray->x + Octree::half);
        const SI y = (this->ray->y + Octree::half);
        const SI z = (this->ray->z + Octree::half);
        
        if(x >= 0 && x < Options::OCTREE_SIZE &&
            y >= 0 && y < Options::OCTREE_SIZE &&
            z >= 0 && z < Options::OCTREE_SIZE)
        {
            return this->accelerator[x][y][z];
        }
    }
    return this->root->getBit({
        (SI)this->ray->x,
        (SI)this->ray->y,
        (SI)this->ray->z
    });
}

/*
 * rayTrace
 */
bool Octree::rayTrace()
{
    if(this->ray != NULL)
    {
        this->resetRay();
        while(((SI)this->depthray) < this->raylength)
        {
            // Searches for the deepest available octant from the root,
            // corresponding to the current ray position
            Octree::curbit = this->getBit();
            
            if(Octree::curbit->voxel.active) return true;
            
            // Calculates the new ray position
            this->getNextEntryDot(Octree::curbit);
            this->depthray += this->raystep;
        }
    }
    return false;
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
        if(Options::nosiblings)
        {
            this->addSingleVoxel(voxels[i]);
        } else
        {
            if(Options::SMOOTH_SIBLINGS)
            {
                this->addSmooths(voxels[i]);
            } else this->addSiblings(voxels[i]);
		}
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

/*static const Vec3<SI> s0[8] = {
    {-1, -1, -1},
    {1, -1, -1},
    {-1, 1, -1},
    {1, 1, -1},
    {-1, -1, 1},
    {1, -1, 1},
    {-1, 1, 1},
    {1, 1, 1}
}*/

static const Vec3<SI> s1[12] = {
    {0, -1, -1},
    {0, 1, -1},
    {0, -1, 1},
    {0, 1, 1},
    
    {-1, -1, 0},
    {1, -1, 0},
    {-1, 1, 0},
    {1, 1, 0},
    
    {-1, 0, -1},
    {1, 0, -1},
    {-1, 0, 1},
    {1, 0, 1}
};

static const Vec3<SI> s2[6] = {
    {0, 0, -1},
    {0, 0, 1},
    {0, -1, 0},
    {0, 1, 0},
    {-1, 0, 0},
    {1, 0, 0}
};

/*
 * addSiblings
 */
void Octree::addSmooths(const Voxel voxel)
{
    UC i = 0;
    while(i < 12)
    {
        Voxel v = voxel;
        v.coordinates.x += s1[i].x;
        v.coordinates.y += s1[i].y;
        v.coordinates.z += s1[i].z;
        v.color.a = 63;
        this->root->setBit(v);
        i++;
    }
    i = 0;
    while(i < 6)
    {
        Voxel v = voxel;
        v.coordinates.x += s2[i].x;
        v.coordinates.y += s2[i].y;
        v.coordinates.z += s2[i].z;
        v.color.a = 127;
        this->root->setBit(v);
        i++;
    }
    this->root->setBit(voxel);
}

/*
 * addSiblings
 */
void Octree::addSiblings(const Voxel voxel)
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
        (UC)(color.b * darkness),
        color.a
    };
}
