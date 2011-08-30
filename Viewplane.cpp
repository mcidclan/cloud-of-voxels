/*
 * Cloud of voxels (COV) project
 * Author: by mcidclan. m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/Viewplane.h"


/*
 * Constructor
 */
Viewplane::Viewplane()
{
}


/*
 * Destructor
 */
Viewplane::~Viewplane()
{
	delete [] ivectors;
}


/*
 * create
 */
void Viewplane::create(const UI hsize, const UI vsize)
{
	Vec2ui localcenter =
	{
		hsize/2,
		vsize/2
	};

	this->hlimit.x = -localcenter.x;
	this->hlimit.y = localcenter.x;

	this->vlimit.x = -localcenter.y;
	this->vlimit.y = localcenter.y;

	this->ivectors = new Vec3f[hsize];
}


/*
 * reset
 */
void Viewplane::resetScan()
{
	this->firsthscan = true;
	this->lastscan = false;

	this->vscan = this->vlimit.x;
	this->verticalScan();
	this->horizontalScan();
}


/*
 * verticalScan
 */
bool Viewplane::verticalScan()
{
	this->hid = 0;
	this->hscan = this->hlimit.x;

	if(this->vscan < this->vlimit.y)
	{
		this->jvector = math::vecxscl(this->basis.j, (float)this->vscan);
		this->vscan++;

	} else return false;

	return true;
}


/*
 * horizontalScan
 */
bool Viewplane::horizontalScan()
{
	if(this->hscan < this->hlimit.y)
	{
		if(this->firsthscan == true)
		{
			this->ivectors[this->hid] =
			math::vecxscl(this->basis.i, (float)this->hscan);
		}

		this->ivector = this->ivectors[this->hid];
		this->hscan++;
		this->hid++;

	} else
	{
		this->firsthscan = false;
		return false;
	}
	return true;
}


/*
 * scan
 */
bool Viewplane::scan()
{
	if(this->horizontalScan() == false)
	{
		if(this->verticalScan() == false)
		{
			return false;
		} else
		{
			return this->horizontalScan();
		}
	}
	return true;
}


void Viewplane::getScanPosition(Vec3f *scanpos)
{
	math::vecadd(this->ivector, this->jvector, scanpos);
}


