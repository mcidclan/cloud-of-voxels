/*
 * Cloud of voxels (COV) project
 * Author: by mcidclan. m.cid.clan@gmail.com
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
	unsigned i = 0,
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
	unsigned i = 0,
				j = 0,
				k = 0;

	this->spacewidth	= spacewidth;
	this->spaceheight = spaceheight;
	this->spacedepth	= spacedepth;

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
	const UI x = /*ceilf(*/voxel->x+this->center.x/*)*/;
	const UI y = /*ceilf(*/voxel->y+this->center.y/*)*/;
	const UI z = /*ceilf(*/voxel->z+this->center.z/*)*/;

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
	this->center.x = ((float)spacewidth)/2.0f;
	this->center.y = ((float)spaceheight)/2.0f;
	this->center.z = ((float)spacedepth)/2.0f;
}


/*
 * setCenter
 */
Vec3f Partition::getCenter()
{
	return this->center;
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
void Partition::resetDepthScan(const Vec3f *kbase)
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


