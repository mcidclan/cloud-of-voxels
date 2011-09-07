/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/Partition.h"


/*
 * Constructor
 */
Partition::Partition()
{
	this->curvoxel = NULL;

	this->curdepth = 0;
	this->maxdepth = 1;
	this->colordepthstep = 300.0f/1.0f;
}


/*
 * Destructor
 */
Partition::~Partition()// à verifier
{
	unsigned
	i = 0,
	j = 0,
	k = 0;

	while(i < this->spacewidth)
	{
		j = 0;
		while(j < this->spaceheight)
		{
			k = 0;
			while(k < this->spacedepth)
			{
				delete [] this->bits[i][j][k];
				k++;
			}

			delete [] this->bits[i][j];
			j++;
		}
		delete [] this->bits[i];
		i++;
	}

	delete [] this->bits;
}


/*
 * create
 */
void Partition::create(const UI spacewidth, const UI spaceheight,
const UI spacedepth)
{
	unsigned
	i = 0,
	j = 0,
	k = 0;

	this->spacewidth = spacewidth;
	this->spaceheight = spaceheight;
	this->spacedepth = spacedepth;

	this->bits = new Voxel***[this->spacewidth];

	while(i < this->spacewidth)
	{
		this->bits[i] = new Voxel**[this->spaceheight];

		j = 0;
		while(j < this->spaceheight)
		{
			this->bits[i][j] = new Voxel*[this->spacedepth];

			k = 0;
			while(k < this->spacedepth)
			{
				this->bits[i][j][k] = NULL;
				k++;
			}

			j++;
		}
		i++;
	}

	setCenter();

	printf("partition created\n");
}


/*
 * getBit
 */
void Partition::setBit(Voxel *voxel)
{
	const short UI x = voxel->coordinates.x+this->center.x;
	const short UI y = voxel->coordinates.y+this->center.y;
	const short UI z = voxel->coordinates.z+this->center.z;

	if(x > this->spacewidth || y > this->spaceheight || z > this->spacedepth)
	{
		return;
	}

	this->bits[x][y][z] = voxel;
}


void Partition::setCurrentVoxel()
{
	curvoxel = this->bits[(UI)scanpos.x][(UI)scanpos.y][(UI)scanpos.z];
}


/*
 * setCenter
 */
void Partition::setCenter()
{
	this->center.x = spacewidth/2;
	this->center.y = spaceheight/2;
	this->center.z = spacedepth/2;
}


/*
 * setMaxDepth
 */
void Partition::setMaxDepth(const UI maxdepth)
{
	this->maxdepth = maxdepth;
	this->colordepthstep = (300.0f/(float)maxdepth);
}


/*
 * resetDepthScan
 */
void Partition::resetDepthScan(const Vec3<float> *kbase)
{
	this->curdepth = 0;
	this->kbase = kbase;
	math::vecadd(this->center, &this->scanpos);
}


/*
 * depthScan
 */
void Partition::depthScan()
{
	this->setCurrentVoxel();

	if((this->curvoxel != NULL) || (this->curdepth == this->maxdepth))
	{
		return;
	}

	math::vecadd(*(this->kbase), &this->scanpos);
	this->curdepth++;
	depthScan();
}


/*
 * setColorDepth
 */
unsigned char Partition::getColorDepth()
{
	const int c = this->curvoxel->color -
	(int)(((float)this->curdepth)*this->colordepthstep);

	if(c <= 0)
	{
		return 0;
	}

	return c;
}


