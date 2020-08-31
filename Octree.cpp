/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/Octree.h"

extern Vec3<SI> atom[18];
extern Vec3<SI> shell[54];
extern Vec3<SI> shellxl[150];

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
 * getNextBit
 */
Octant* Octree::getNextBit(float* axis, const float side)
{
    const float d = *axis;
    *axis = ((SI)d) + side;
    Octant* const curbit = this->getBit();
    *axis = d;
    return curbit;
}


/*
 * avoidScanGlitches
 */
void Octree::avoidScanGlitches(Octant** const curbit)
{
    if(Options::AVOID_SCAN_GLITCHES)
    {
        if(!(*curbit)->voxel.active) {
            *curbit = getNextBit(&this->ray->x, 1.0f);
        }
        if(!(*curbit)->voxel.active) {
            *curbit = getNextBit(&this->ray->y, 1.0f);
        }
        if(!(*curbit)->voxel.active) {
            *curbit = getNextBit(&this->ray->z, 1.0f);
        }
        if(!(*curbit)->voxel.active) {
            *curbit = getNextBit(&this->ray->x, -1.0f);
        }
        if(!(*curbit)->voxel.active) {
            *curbit = getNextBit(&this->ray->y, -1.0f);
        }
        if(!(*curbit)->voxel.active) {
            *curbit = getNextBit(&this->ray->z, -1.0f);
        }
    }
}

/*
 * rayTrace
 */
bool Octree::rayTrace(vector<DynamicVoxel>* const voxels)
{
    if(this->ray != NULL)
    {
        float depthray = 0.0f;
        while(depthray < (float)this->raylength)
        {
            // Searches for the deepest available octant from the root,
            // corresponding to the current ray position
            Octant* curbit = this->getBit();
            this->avoidScanGlitches(&curbit);
            if(curbit->voxel.active)
            {
                voxels->push_back({curbit->voxel, depthray});
                if(!Options::TRANSPARENCY ||
                    curbit->voxel.color.a == 0xFF) return true;
            }
            // Calculates the new ray position
            this->getNextEntryDot(curbit);
            depthray += this->raystep;
        }
    }
    return voxels->size() > 0;
}


/*
 * rayToBorder
 */
 
void Octree::rayToBorder(const float a, const float b, const float c)
{
    if(c != 0.0f)
    {
        // Distance between the current ray position and
        // the next potential octant limit position
        const float d = math::absf(b - a) / math::absf(c);
        if(d < this->raystep) {
            this->raystep = d;
        }
    }
}


/*
 * getNextEntryDot
 */
void Octree::getNextEntryDot(Octant* octant)
{
    if(this->ray != NULL)
    {
        this->raystep = ((float)this->root->size);
        rayToBorder(this->ray->x, octant->facescenter[
        (this->kbase->x > 0.0f) ? 1 : 0].x, this->kbase->x);
        rayToBorder(this->ray->y, octant->facescenter[
        (this->kbase->y > 0.0f) ? 3 : 2].y, this->kbase->y);
        rayToBorder(this->ray->z, octant->facescenter[
        (this->kbase->z > 0.0f) ? 5 : 4].z, this->kbase->z);
         
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
    UC percent = 0;
    const UI step = nvoxel / 100;
	while(i < nvoxel)
	{
        if(i % (step * 10) == 0) {
            printf(">%d ", percent);
            percent+=10;
        }
        if(Options::SMOOTH_SIBLINGS)
        {
            this->addSmooths(voxels[i]);
        } else if(Options::HARD_SIBLINGS)
        {
            this->addSiblings(voxels[i]);
        } else this->addSingleVoxel(voxels[i]);
            
        switch(Options::VOXEL_SHELL_TYPE)
        {
            case 1:
                this->addShell(voxels[i]);
                break;
            case 2:
                this->addShellXL(voxels[i]);
                break;
            case 3:
                this->addShellLite(voxels[i]);
                break;
        }
        i++;
	}
    printf("\n");
}


/*
 * add single voxel
 */
void Octree::addSingleVoxel(const Voxel voxel)
{
    this->root->setBit(voxel);
}

/*
 * addSmooths
 */
void Octree::addSmooths(const Voxel voxel)
{
    UC i = 0;
    while(i < 18)
    {
        Voxel v = voxel;
        v.coordinates.x += atom[i].x;
        v.coordinates.y += atom[i].y;
        v.coordinates.z += atom[i].z;
        v.color.a = 255;
        this->root->setBit(v);
        i++;
    }
    this->root->setBit(voxel);
}

/*
 * addSmooths
 */
void Octree::addShellLite(const Voxel voxel)
{   
    UC i = 1;
    while(i < 6)
    {
        Voxel v = voxel;
        math::vecxscl(&v.coordinates, 1.0f + i / 120.0f);
        if(Options::SHELL_COLOR.a > 0)
        {
            v.color = Options::SHELL_COLOR;
        }
        else v.color.a = 16;
        this->root->setBit(v);
        i++;
    }
}


/*
 * addShellXL
 */
void Octree::addShellXL(const Voxel voxel)
{
    UC i = 0;
    while(i < 150)
    {
        Voxel v = voxel;
        v.coordinates.x += shellxl[i].x;
        v.coordinates.y += shellxl[i].y;
        v.coordinates.z += shellxl[i].z;
        if(Options::SHELL_COLOR.a > 0)
        {
            v.color = Options::SHELL_COLOR;
        }
        else v.color.a = 16;
        this->root->setBit(v);
        i++;
    }
}


/*
 * addShell
 */
void Octree::addShell(const Voxel voxel)
{
    UC i = 0;
    while(i < 54)
    {
        Voxel v = voxel;
        v.coordinates.x += shell[i].x;
        v.coordinates.y += shell[i].y;
        v.coordinates.z += shell[i].z;
        if(Options::SHELL_COLOR.a > 0)
        {
            v.color = Options::SHELL_COLOR;
        }
        else v.color.a = 16;
        this->root->setBit(v);
        i++;
    }
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
Color Octree::getColorDepth(const DynamicVoxel* const dynamic)
{
    const float darkness = 1.0f - dynamic->depth*this->colordepthstep;
	return {
        (UC)(dynamic->voxel.color.r * darkness),
        (UC)(dynamic->voxel.color.g * darkness),
        (UC)(dynamic->voxel.color.b * darkness),
        dynamic->voxel.color.a
    };
}
