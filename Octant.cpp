/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/Octant.h"


/*
 * Constructor
 */
Octant::Octant()
{
	this->pos.x =
	this->pos.y =
	this->pos.z = 0;

	this->voxel = NULL;
	this->childreen = NULL;
}


/*
 * Destructor
 */
Octant::~Octant()
{
	unsigned char
	i = 0,
	j = 0;

	while(i < 2)
	{
		j = 0;
		while(j < 2)
		{
			delete [] this->children[i][j];
			j++;
		}
		delete [] this->children[i];
		i++;
	}

	delete [] this->children;
}


void Octant::setDimensions(short UI rootsize, short UI maxdepth)//static
{
	Octant::maxdepth = maxdepth;
	Octant::rootsize = rootsize;
}


/*
 *
 */
void Octant::initChild(Octant *parent, const UC i, const UC j, const UC k)//static
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
 * get the local position in the current octant
 */
void Octant::getLocalPosition(Vec3f dot)
{
	vecsub(this->parent->pos, &dot);
	vecxscl(&dot, this->cscoef);
	Octant::curpos = (Vec3sui)dot;
}


/*
 * Add children to the current octant
 */
void Octant::addChildren()
{
	UC
	i = 0,
	j = 0;

	this->children = new Octant**[2];

	while(i < 2)
	{
		this->children[i] = new Octant*[2];
		j = 0;
		while(j < 2)
		{
			this->children[i][j] = new Octant[2];
			Octant::initChild(this, i, j, 0);
			Octant::initChild(this, i, j, 1);
			j++;
		}
		i++;
	}
}


/*
 * Set bit space
 */
void Octant::setBit(Vec4 *voxel, Octant *octant)//static
{
	Vec3sui &curpos = Octant::curpos;
	octant->children[curpos.x][curpos.y][curpos.z] = voxel.w;
}


/*
 * Set bit space, corresponding to the current voxel
 */
void Octant::setBit(Vec4 *voxel)
{
	Vec3f dotlocpos = getLocalPosition(*dot);

	if(this->depth == 1)
	{
		setBit(this, voxel);
	} else
	{
		if(this->isparent == false)
		{
			this->addChildren();
		}

		...
	}
}


/*
 *
 */
Voxel* getBit(const vec3f raypos)//vec3f *raypos
{
	
	if(this->isparent == true)
	{
		vecsub(raypos, this->pos, &Octant::curpos);
		vecxscl(&Octant::curpos, posfac);

		this->children[Octant::curpos.x][Octant::curpos.y][Octant::curpos.z]
		->getBit(raypos);
	}

	return this->voxel;
}


