/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */
//Must be re-implemented
#include "./headers/Octree.h"


SUI Octree::depth;

Vec3<SUI> Octree::center;
Vec3<SUI> Octree::locpos;

Vec3<float> Octree::raypos;
Vec3<float> Octree::raysrc;
Vec3<float> *Octree::kbase;

Vec3<float> Octree::kbase2;
static UC affectedfaces[3];


float Octree::depthray;
float Octree::raylength;
float Octree::colordepthstep;

Octant *Octree::curbit;
Octant *Octree::root;


//Variables working with temporaries values
static float fvalue;
static Vec3<float> vvalue;


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

	root->half = root->size/2;

	Octree::center.x =
	Octree::center.y =
	Octree::center.z = root->half;

	math::cpvec(Octree::center, &root->center);

	Octree::raylength = raylength;
	Octree::colordepthstep = (255.0f/(float)raylength);

	Octree::setFacesCenter(root, root->half);
}


/*
 *
 */
void Octree::setFacesCenter(Octant *octant, const float half)
{//Must be re-implemented
	//printf("setFacecenter\n");
	octant->facescenter = new Vec3<float>[6];
	math::vecadd(-half, 0.0f, 0.0f, octant->center, &octant->facescenter[0]);
	math::vecadd(half, 0.0f, 0.0f, octant->center, &octant->facescenter[1]);

	math::vecadd(0.0f, -half, 0.0f, octant->center, &octant->facescenter[2]);
	math::vecadd(0.0f, half, 0.0f, octant->center, &octant->facescenter[3]);

	math::vecadd(0.0f, 0.0f, -half, octant->center, &octant->facescenter[4]);
	math::vecadd(0.0f, 0.0f, half, octant->center, &octant->facescenter[5]);
}


/*
 * keepAffectedFaces()
 */
void Octree::keepAffectedFaces()
{//Must be re-implemented
	/*if(Octree::kbase->x < 0.0f) affectedfaces[0] = 0;
	else if(Octree::kbase->x > 0.0f) affectedfaces[0] = 1;
	else affectedfaces[0] = 6;

	if(Octree::kbase->y < 0.0f) affectedfaces[1] = 2;
	else if(Octree::kbase->y > 0.0f) affectedfaces[1] = 3;
	else affectedfaces[1] = 6;
	
	if(Octree::kbase->z < 0.0f) affectedfaces[2] = 4;
	else if(Octree::kbase->z > 0.0f) affectedfaces[2] = 5;
	else affectedfaces[2] = 6;*/

	affectedfaces[0] = Octree::kbase->x < 0.0f ? 0 : 1;
	affectedfaces[1] = Octree::kbase->y < 0.0f ? 2 : 3;
	affectedfaces[2] = Octree::kbase->z < 0.0f ? 4 : 5;
}


/*
 *
 */
void Octree::initChild(const UC i, const UC j, const UC k, Octant *parent)
{//Must be re-implemented
	Vec3<SI> pos = {i, j, k};

	Octant *child = &(parent->children[i][j][k]);

	child->parent = parent;
	child->depth = parent->depth - 1;
	child->size = parent->size / 2;

	child->pos = math::vecxscl(pos, child->size);
	math::vecadd(parent->pos, &child->pos);

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
{//Must be re-implemented
	Octree::kbase = kbase;
	Octree::kbase2 = math::vecxscl(*Octree::kbase, 0.9f);
	Octree::keepAffectedFaces();
}


/*
 * resetRayCast
 */
void Octree::resetRayCast()
{//Must be re-implemented
	//Move the ray to its relative position in the octree
	math::vecadd(Octree::center, &Octree::raypos);
	math::cpvec(Octree::raypos, &Octree::raysrc);
}


/*
 * rayCast
 */
#include <stdlib.h>
void Octree::rayCast()//Must be reimplemented
{//Must be re-implemented
	Octree::curbit = root;//not a good thing
	Octree::curbit->getBit(&Octree::raypos);
	Octree::getNextEntryDot(Octree::curbit, &Octree::raypos);//

	math::vecsub(Octree::raysrc, Octree::raypos, &vvalue);
	Octree::depthray = math::getnorm(&vvalue);

	math::vecadd(Octree::kbase2, &Octree::raypos);

	if(Octree::curbit->voxel != NULL || (Octree::depthray > Octree::raylength))
	{
		return;
	}

	Octree::rayCast();
}


/*
 * getNearestFace
 */
void Octree::getNearestFace(Octant* octant, Vec3<float> *coordinates, UC *lid)
{//Must be re-implemented
	float
	dp = 0.0f,
	maxdp = 0.0f;

	UC i = 0;
	*lid = affectedfaces[0];

	while(i < 3)
	{
		UC &fid = affectedfaces[i];

		//if(fid == 6) goto next;

		math::vecsub(octant->facescenter[fid], *coordinates, &vvalue);
		dp = math::dotproduct(&vvalue, Octree::kbase);

		if(dp > maxdp)
		{
			maxdp = dp;
			*lid = fid;
		}

		//next:
		i++;
	}
}


/*
 * getNextEntryDot
 */
void Octree::getNextEntryDot(Octant* octant, Vec3<float> *coordinates)
{//Must be re-implemented
	UC fid = 0;
	getNearestFace(octant, coordinates, &fid);

	if(fid == 0 || fid == 1)
	{
		fvalue = fabs(octant->facescenter[fid].x - coordinates->x);
	}

	if(fid == 2 || fid == 3)
	{
		fvalue = fabs(octant->facescenter[fid].y - coordinates->y);
	}

	if(fid == 4 || fid == 5)
	{
		fvalue = fabs(octant->facescenter[fid].z - coordinates->z);
	}

	vvalue = math::vecxscl(*Octree::kbase, fvalue);
	math::vecadd(vvalue, coordinates);
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


