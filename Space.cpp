/*
 * Cloud of voxels (COV) project
 * Author: by mcidclan. m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/Space.h"


/*
 * Contructor
 */
Space::Space()
{
	this->partition = NULL;
}


/*
 * Destructor
 */
Space::~Space()
{
}


/*
 * setPartition
 */
void Space::setPartition(Partition *partition)
{
	this->partition = partition;
}


/*
 * addVoxels
 */
bool Space::addVoxels(Voxel *voxels, const UI nvoxel)
{
	UI i = 0;

	if(partition != NULL)
	{
		while(i < nvoxel)
		{
			this->partition->setBit(&voxels[i]);
			i++;
		}
	} else return false;

	return true;
}


