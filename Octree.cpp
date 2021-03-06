/*
 * Cloud of Voxels (CoV) project
 * Author: mcidclan, m [.D'O'T.] cid [.D'O'T.] clan [.A'T.] gmail [.D'O'T.] com
 * Creation Date: 2011
 * Modification Date: 2020
 */

#include "./headers/Octree.h"

extern Vec3<SI> atom[18];
extern Vec3<SI> shell[54];
extern Vec3<SI> shellxl[150];

float Octree::size;
float Octree::half;

Octree::Octree()
{
    this->accelerated = false;
}


Octree::~Octree()
{
    delete [] this->root->facescenter;
    delete this->root;
    if(Options::ACCELERATED)
    {
        this->destroyAccelerator();
    }
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
                this->accelerator[i][j][k] =
                OctantManager::getBit(this->root, {x, y, z});
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
    OctantManager::init(this->root);
	this->root->depth = maxdepth;
	this->root->half = size/2;
	
    this->root->center.x =
	this->root->center.y =
	this->root->center.z = 0.0f;
    OctantManager::setFacesCenter(this->root);
    
	this->ray = NULL;
    this->raylength = raylength;
	this->colordepthstep = (1.0f/(float)raylength);
    
    Octree::half = this->root->half;
    Octree::size = Octree::half*2.0f;
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
    return OctantManager::getBit(this->root, {
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
        if((*curbit)->voxel == NULL) {
            *curbit = getNextBit(&this->ray->x, 1.0f);
        }
        if((*curbit)->voxel == NULL) {
            *curbit = getNextBit(&this->ray->y, 1.0f);
        }
        if((*curbit)->voxel == NULL) {
            *curbit = getNextBit(&this->ray->z, 1.0f);
        }
        if((*curbit)->voxel == NULL) {
            *curbit = getNextBit(&this->ray->x, -1.0f);
        }
        if((*curbit)->voxel == NULL) {
            *curbit = getNextBit(&this->ray->y, -1.0f);
        }
        if((*curbit)->voxel == NULL) {
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
            if(curbit->voxel != NULL)
            {
                if(!Options::TRANSPARENCY || (curbit->voxel->color & 0x000000FF) == 0xFF)
                {
                    voxels->push_back({depthray, curbit->voxel});
                    return true;
                }
                if(Options::TRANSPARENCY)
                {
                    if(voxels->size() == 0 || (voxels->size() > 0 && (depthray -
                    (*voxels)[voxels->size()-1].depth) >= Options::MIN_VOXELS_PROXIMITY))
                    {
                        voxels->push_back({depthray, curbit->voxel});
                    }
                }
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
        this->raystep = Octree::size;
        rayToBorder(this->ray->x, octant->facescenter[
        (this->kbase->x > 0.0f) ? 1 : 0], this->kbase->x);
        rayToBorder(this->ray->y, octant->facescenter[
        (this->kbase->y > 0.0f) ? 3 : 2], this->kbase->y);
        rayToBorder(this->ray->z, octant->facescenter[
        (this->kbase->z > 0.0f) ? 5 : 4], this->kbase->z);
         
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
        if((step > 0) && (i % (step * 10) == 0))
        {
            printf(">%d ", percent);
            percent+=10;
        }
        
        if(Options::SMOOTH_SIBLINGS)
        {
            this->addSmooths(&voxels[i]);
        } else this->addSingleVoxel(&voxels[i]);
            
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

template<typename T>
void Octree::initBit(T voxel)
{
    OctantManager::initBit(this->root, voxel);
}


/*
 * add single voxel
 */
void Octree::addSingleVoxel(Voxel* const voxel)
{
    this->initBit(voxel);
}

/*
 * addSmooths
 */
void Octree::addSmooths(Voxel* const voxel)
{
    UC i = 0;
    while(i < 18)
    {
        Voxel v = *voxel;
        v.coordinates.x += atom[i].x;
        v.coordinates.y += atom[i].y;
        v.coordinates.z += atom[i].z;
        this->initBit(v);
        i++;
    }
    this->initBit(voxel);
}

/*
 * addSmooths
 */
void Octree::addShellLite(const Voxel voxel)
{
    UC i = 0;
    while(i < Options::SHELL_LITE_THICKNESS)
    {
        Voxel v = voxel;
        math::vecxscl(&v.coordinates, 1.05f + i * 0.02f);
        if(Options::SHELL_COLOR > 0)
        {
            v.color = Options::SHELL_COLOR;
        }
        else v.color = (v.color & 0xFFFFFF00) | 0x0F;
        this->initBit(v);
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
        if(Options::SHELL_COLOR > 0)
        {
            v.color = Options::SHELL_COLOR;
        }
        else v.color = (v.color & 0xFFFFFF00) | 0x0F;
        this->initBit(v);
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
        if(Options::SHELL_COLOR > 0)
        {
            v.color = Options::SHELL_COLOR;
        }
        else v.color = (v.color & 0xFFFFFF00) | 0x0F;
        this->initBit(v);
        i++;
    }
}


/*
 * setColorDepth
 */
Color Octree::getColorDepth(const DynamicVoxel* const dynamic)
{
    const float darkness = getDarkness(dynamic->depth);
	return {
        (UC)(((dynamic->voxel->color & 0xFF000000) >> 24) * darkness),
        (UC)(((dynamic->voxel->color & 0x00FF0000) >> 16) * darkness),
        (UC)(((dynamic->voxel->color & 0x0000FF00) >> 8) * darkness),
        (UC)(dynamic->voxel->color & 0x000000FF)
    };
}


Color Octree::getColorDepth(const UC r, const UC g, const UC b, const float depth)
{
    const float darkness = getDarkness(depth);
    return {(UC)(r * darkness), (UC)(g * darkness), (UC)(b * darkness), 0};
}

float Octree::getDarkness(const float depth)
{
   return 1.0f - depth * this->colordepthstep;
}