/*
 * Cloud of Voxels (CoV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Creation Date: 2011
 * Modification Date: 2020
 */

#include "./headers/Octant.h"
#include "./headers/Octree.h"

/*
 * Constructor
 */
void OctantManager::init(Octant* const octant)
{
	octant->pos.x =
	octant->pos.y =
	octant->pos.z = 0;
	octant->depth = 0;
	octant->voxel.active = 0;
    octant->voxel.color = 0;
    octant->children = NULL;
	octant->isparent = false;
}


/*
 * Add children to the current octant
 */
void OctantManager::addChildren(Octant* const octant)
{
    UC i = 0;
    octant->children = new Octant[8];
    while(i < 8) {
        OctantManager::init(&octant->children[i]);
        OctantManager::initChild(octant, i % 2, (i / 2) % 2, i / 4);
        i++;
    }
    octant->isparent = true;
}


/*
 * Remove children from the current octant
 */
void OctantManager::removeChildren(Octant* const octant) {
    if(octant->children != NULL)
    {
        delete [] octant->children;
        delete [] octant->facescenter;
    }    
}


/*
 * initChild
 */
Octant* OctantManager::getChildren(Octant* const octant,
const UC i, const UC j , const UC k)
{
    return &octant->children[i + j * 2 + k * 4];
}


/*
 * initChild
 */
void OctantManager::initChild(Octant* const octant,
const SUI i, const SUI j, const SUI k)
{   
	Octant* const child = OctantManager::getChildren(octant, i, j, k);
    child->parent = octant;
	child->depth = octant->depth - 1;
    
	//child->size = octant->size / 2;
	
    math::cpvec(octant->pos, &child->pos);
    child->pos.x += i * octant->half;
	child->pos.y += j * octant->half;
	child->pos.z += k * octant->half;
	
    math::cpvec(child->pos, &child->center);
    child->half = ((float)octant->half) / 2.0f;
	child->center.x += child->half;
	child->center.y += child->half;
	child->center.z += child->half;
    
	OctantManager::setFacesCenter(child);
}


/*
 * setFacesCenter
 */
void OctantManager::setFacesCenter(Octant* const octant)
{    
	octant->facescenter = new SI[6];
    octant->facescenter[0] = -octant->half + octant->center.x;
    octant->facescenter[1] = octant->half + octant->center.x;
    octant->facescenter[2] = -octant->half + octant->center.y;
    octant->facescenter[3] = octant->half + octant->center.y;
    octant->facescenter[4] = -octant->half + octant->center.z;
    octant->facescenter[5] = octant->half + octant->center.z;    
}


/*
 * Set the bit space corresponding to the current voxel
 */
void OctantManager::setBit(Octant* const octant, const Voxel voxel)
{
    if(math::absf(voxel.coordinates.x) >= (Octree::half - 2) ||
        math::absf(voxel.coordinates.y) >= (Octree::half - 2) ||
        math::absf(voxel.coordinates.z) >= (Octree::half - 2)) return;
            
    if(octant->depth == 0)
    {
        if(!octant->voxel.active || (voxel.color & 0x000000FF) == 255) { //
            octant->voxel = voxel;
            if(!Options::nologs)
            {
                printf("Add voxel at: %i %i %i\n",
                octant->pos.x, octant->pos.y, octant->pos.z);
            }
        }            
    } else
    {
        if(octant->isparent == false)
        {
            OctantManager::addChildren(octant);
            if(!Options::nologs)
            {
                printf("children added in level %i\n", octant->depth);
            }
        }
        OctantManager::setBit(OctantManager::getChildAt(
        octant, voxel.coordinates), voxel);
    }
}


/*
 * getBit
 */
Octant* OctantManager::getBit(Octant* const octant, const Vec3<SI> coordinates)
{
	if(octant->children != NULL)
	{
		return OctantManager::getBit(OctantManager::getChildAt(
        octant, coordinates), coordinates);
	}
    return octant;
}


/*
 * getChildAt
 */
Octant* OctantManager::getChildAt(Octant* const octant, const Vec3<SI> coordinates)
{
    const Vec3<UC> r = {
        (UC)(coordinates.x < octant->center.x ? 0 : 1),
        (UC)(coordinates.y < octant->center.y ? 0 : 1),
        (UC)(coordinates.z < octant->center.z ? 0 : 1)
    };
	return OctantManager::getChildren(octant, r.x, r.y, r.z);
}
