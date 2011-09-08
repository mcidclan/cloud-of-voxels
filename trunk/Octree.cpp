/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/Octree.h"


SUI Octree::depth;
SUI Octree::maxdepth;
SUI Octree::rootsize;

Vec3<SUI> Octree::center;
Vec3<SUI> Octree::locpos;

float Octree::depthray;
float Octree::raylength;


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
	root->depth = maxdepth;
	//Octree::root = root;
	Octree::maxdepth = maxdepth;
	Octree::rootsize = rootsize;

	Octree::center.x =
	Octree::center.y =
	Octree::center.z = rootsize/2;

	Octree::raylength = raylength;
}


/*
 *
 */
void Octree::initChild(const UC i, const UC j, const UC k, Octant *parent)
{
	SUI level;
	const Vec3<SUI> locpos = {i, j, k};

	Octant *child = &(parent->children[i][j][k]);

	child->parent = parent;
	child->depth = parent->depth - 1;

	level = Octree::maxdepth - child->depth;
	child->size = Octree::rootsize / (2 * level);

	child->pos = math::vecxscl(locpos, child->size);
	child->cscoef = 1.0f/((float)child->size);
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
	octant->children[Octree::locpos.x][Octree::locpos.y][Octree::locpos.z]
	.voxel = voxel;
}


/*
 * Update locpos from the current octant's local position
 */
void Octree::updateLocalPosition(Vec3<SI> v, Octant *octant)//???//functional?
{
	//const Vec3<SUI> locpos = {0, 0, 0};
	math::vecsub(octant->parent->pos, &v);
	math::vecxscl(&v, octant->cscoef);
	math::cpvec(v, &Octree::locpos);//
	math::vecadd(Octree::center, &Octree::locpos);//
}


/*
 * resetRayCast //resetDepthScan
 */
void Partition::resetRayCast(const Vec3<float> *kbase)//kbase must be normalized
{
	Octree::depthray = 0;
	Octree::kbase = kbase;
	math::vecadd(Octree::center, &Octree::raypos);
}


/*
 * rayCast //depthScan
 */
void Octree::rayCast()//not yet implemented
{
	float raybit;

	getBit(&Octree::raypos);

	if((Octree::curoctant->depth == 1) || (Octree::depthray >= Octree::raylength))
	{
		return;
	}

	raybit = math::vecxscl(*(Octree::kbase), Octree::curoctant->size);
	math::vecadd(raybit, &Octree::raypos);

	Octree::depthray += Octree::curoctant->size;


	Octree::rayCast();
}


