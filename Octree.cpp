/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/Octree.h"


UC Octree::lfid;
UC Octree::affectedfaces[3];

Vec3<SUI> Octree::locpos;

Vec3<float> *Octree::kbase;
Vec3<float> Octree::kbsample;
Vec3<float> Octree::raypos;

float const Octree::RAYSTEP_MIN_UNIT = 1.0f;//0.01f;

float Octree::raystep;
float Octree::lastraystep;
float Octree::depthray;
float Octree::raylength;
float Octree::colordepthstep;

Octant *Octree::root;
Octant *Octree::curbit;


/*
 * Delete childreen
 */
void Octree::delChildreen(Octant *octant)
{
	UI
	i = 0,
	j = 0;

	while(i < 2)
	{
		j = 0;
		while(j < 2)
		{
			delete [] octant->children[i][j];
			j++;
		}
		delete [] octant->children[i];
		i++;
	}
	delete [] octant->children;
}


/*
 * initRoot
 */
void Octree::initRoot(SUI rootsize, SUI maxdepth, const float raylength,
Octant *root)
{
	root->depth = maxdepth;
	root->size = rootsize;

	root->half = root->size/2;

	root->center.x =
	root->center.y =
	root->center.z = root->half;

	Octree::root = root;
	Octree::raylength = raylength;
	Octree::colordepthstep = (255.0f/(float)raylength);
	Octree::setFacesCenter(root, root->half);
}


/*
 * setFacesCenter
 */
void Octree::setFacesCenter(Octant *octant, const float half)
{
	octant->facescenter = new Vec3<float>[6];

    math::vecadd(-half, 0.0f, 0.0f, octant->center, &octant->facescenter[0]);
	math::vecadd(half, 0.0f, 0.0f, octant->center, &octant->facescenter[1]);

	math::vecadd(0.0f, -half, 0.0f, octant->center, &octant->facescenter[2]);
	math::vecadd(0.0f, half, 0.0f, octant->center, &octant->facescenter[3]);

	math::vecadd(0.0f, 0.0f, -half, octant->center, &octant->facescenter[4]);
	math::vecadd(0.0f, 0.0f, half, octant->center, &octant->facescenter[5]);
}


/*
 * initChild
 */
void Octree::initChild(const UC i, const UC j, const UC k, Octant *parent)
{
	Octant *child = &(parent->children[i][j][k]);

	child->depth = parent->depth - 1;
	child->size = parent->size / 2;

	math::cpvec(parent->pos, &child->pos);

	child->pos.x += i * child->size;
	child->pos.y += j * child->size;
	child->pos.z += k * child->size;

	math::cpvec(child->pos, &child->center);

	child->half = ((float)child->size) / 2.0f;
	child->center.x += child->half;
	child->center.y += child->half;
	child->center.z += child->half;

	Octree::setFacesCenter(child, child->half);
}


/*
 * Add children to the current octant
 */
void Octree::addChildren(Octant *octant)
{
	UC
	i = 0,
	j = 0;

	octant->children = new Octant**[2];

	while(i < 2)
	{
		octant->children[i] = new Octant*[2];

		j = 0;
		while(j < 2)
		{
			octant->children[i][j] = new Octant[2];
			Octree::initChild(i, j, 0, octant);
			Octree::initChild(i, j, 1, octant);
			octant->isparent = true;
			j++;
		}
		i++;
	}
}


/*
 * Set bit space
 */
void Octree::setBit(Voxel *voxel, Octant *octant)
{
	octant->voxel = voxel;
}


/*
 * initRayCast
 */
void Octree::initRayCast(Vec3<float> *kbase)
{
	Octree::kbase = kbase;
}


/*
 * resetRayCast
 */
void Octree::resetRayCast()
{
	//Move the ray to its relative position in the octree
	Octree::depthray = 0.0f;
	math::vecadd(Octree::root->center, &Octree::raypos);
}


/*
 * rayCast
 */
void Octree::rayCast()
{
    while(true)
    {
	    Octree::curbit = Octree::root;
	    Octree::curbit->getBit(&Octree::raypos);
	    Octree::getNextEntryDot(Octree::curbit, &Octree::raypos);

	    Octree::depthray += Octree::raystep;

	    if(Octree::curbit->voxel != NULL ||
	    (Octree::depthray > Octree::raylength)) return;
    }
	//Octree::rayCast();
}



/*
 * rayToBorder
 */
float borderdist;
void Octree::rayToBorder(const float a, const float b, const float c)
{
    if(c != 0.0f)
    {
        borderdist = fabs(b - a);
        
        if(borderdist != 0.0f)
        {
            Octree::lastraystep = (borderdist / fabs(c));

            if(Octree::lastraystep < Octree::raystep)
            {
                Octree::raystep = Octree::lastraystep;
            }
        } else Octree::raystep = 0.0f;
    }
}


/*
 * getNextEntryDot
 */
void Octree::getNextEntryDot(Octant* octant, Vec3<float> *coordinates)
{
    UC i = 0;
    Octree::raystep = ((float)Octree::root->size);

    i = (Octree::kbase->x > 0.0f) ? 1 : 0;
    rayToBorder(coordinates->x, octant->facescenter[i].x, Octree::kbase->x);

    i = (Octree::kbase->y > 0.0f) ? 3 : 2;
    rayToBorder(coordinates->y, octant->facescenter[i].y, Octree::kbase->y);

    i = (Octree::kbase->z > 0.0f) ? 5 : 4;
    rayToBorder(coordinates->z, octant->facescenter[i].z, Octree::kbase->z);


    if(Octree::raystep == 0)
    {
        Octree::raystep = Octree::RAYSTEP_MIN_UNIT;
    }

	coordinates->x += Octree::kbase->x * Octree::raystep;
	coordinates->y += Octree::kbase->y * Octree::raystep;
	coordinates->z += Octree::kbase->z * Octree::raystep;
}


/*
 * addVoxels
 */
void Octree::addVoxels(Voxel *voxels, const UI nvoxel)
{
	UI i = 0;
	while(i < nvoxel)
	{
        Octree::addNeighborVoxels(&voxels[i].coordinates);
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
                Octree::root->setBit(voxel);
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
	const int c = 0xFF - (int)(Octree::depthray*Octree::colordepthstep);

	if(c <= 0)
	{
		return 0;
	}
	return c;
}


