/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/Octree.h"


SUI Octree::depth;

Vec3<SUI> Octree::center;
Vec3<SUI> Octree::locpos;
Vec3<float> Octree::raypos;
Vec3<float> Octree::raybit;
Vec3<float> *Octree::kbase;

float Octree::depthray;
float Octree::raylength;
float Octree::colordepthstep;

Octant *Octree::curbit;
Octant *Octree::root;



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
 *
 */
void Octree::initRoot(SUI rootsize, SUI maxdepth, const float raylength,
Octant *root)
{
	Octree::root = root;

	root->depth = maxdepth;
	root->size = rootsize;

	Octree::center.x =
	Octree::center.y =
	Octree::center.z = root->size/2;

	Octree::raylength = raylength;

	Octree::colordepthstep = (255.0f/(float)raylength);
}


/*
 *
 */
void Octree::initChild(const UC i, const UC j, const UC k, Octant *parent)
{
	Vec3<SI> pos = {i, j, k};

	Octant *child = &(parent->children[i][j][k]);
	child->parent = parent;
	child->depth = parent->depth - 1;

	child->size = parent->size / 2;

	child->pos = math::vecxscl(pos, child->size);
	math::vecadd(parent->pos, &child->pos);

	child->scoef = 1.0f/((float)child->size);
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
 * resetRayCast //kbase must be normalized
 */
void Octree::resetRayCast(Vec3<float> *kbase)
{
	Octree::depthray = 0.0f;//Reset the depth ray
	Octree::kbase = kbase;
	Octree::curbit = root;//Back to the root

	//Move the ray to its relative position in the octree
	math::vecadd(Octree::center, &Octree::raypos);
}


/*
 * rayCast
 */
void Octree::rayCast()
{
	//printf("depth ray %f\n", Octree::depthray);//debug

	//Octree::curbit = Octree::curbit->parent;
	Octree::curbit = root;///Back to the root, not good :/
	Octree::curbit->getBit(&Octree::raypos);

	if((Octree::curbit->depth == 1) || (Octree::depthray >= Octree::raylength))
	{
		//printf("\ndepth octant %i\n", curbit->depth);//debug
		//printf("Voxel found at: %f %f %f\n", Octree::raypos.x, Octree::raypos.y,
		//Octree::raypos.z);
		return;
	}

	Octree::raybit = math::vecxscl(*(Octree::kbase), Octree::curbit->size);
	math::vecadd(Octree::raybit, &Octree::raypos);

	Octree::depthray += Octree::curbit->size;
	Octree::rayCast();
}


/*
 * addVoxels
 */
void Octree::addVoxels(Voxel *voxels, const UI nvoxel)
{
	UI i = 0;
	while(i < nvoxel)
	{
		Octree::root->setBit(&voxels[i]);
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


