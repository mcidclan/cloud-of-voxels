/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/Octree.h"


/*
 *
 */
void Octree::del(Octant *octant)
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
void Octree::setDimensions(short UI rootsize, short UI maxdepth)
{
	Octree::maxdepth = maxdepth;
	Octree::rootsize = rootsize;
}


/*
 *
 */
void Octree::initChild(Octant *parent, const UC i, const UC j, const UC k)
{
	short UI level;
	const Vec3uc locpos = {i, j, k};

	Octant *child = &parent[i][j][k];

	child->depth = parent->depth - 1;
	level = child->maxdepth - child->depth;
	child->size = Octant::rootsize / (2 * level);
	child->pos = vecxscl(locpos, child->size);
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
			Octant::initChild(octant, i, j, 0);
			Octant::initChild(octant, i, j, 1);
			j++;
		}
		i++;
	}
}


/*
 * Set bit space
 */
void Octree::setBit(Vec4 *voxel, Octant *octant)
{
	Vec3sui &curpos = Octant::curpos;
	octant->children[curpos.x][curpos.y][curpos.z] = voxel.w;
}


