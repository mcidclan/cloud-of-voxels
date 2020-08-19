/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/Core.h"
#include "./headers/voxelmodels.h"

extern Voxel monkey[MESH_SIZE] __attribute__((aligned(8)));


/*
 * Constructor
 */
Core::Core()
{
}


/*
 * Destructor
 */
Core::~Core()
{
	delete this->camera;
	delete this->viewplane;
}



/*
 * init
 */
Vec3<float> *scanpos = NULL;

void Core::init()
{
    SUI level = 0;
    unsigned int n = OCTREE_SIZE;
    do{
        level += 1;
    } while((n >>= 1) != 1);
    
	this->camera = new Camera();
	printf("octree number of level %i\n", level);

	Octree::initRoot(OCTREE_SIZE, level, (SCR_SIZE/2)*2, new Octant());
	Octree::addVoxels(monkey, MESH_SIZE);

	this->viewplane = new Viewplane();
	this->viewplane->create(VIEW_WIDTH, VIEW_HEIGHT);

	scanpos = &Octree::raypos;

	printf("Core initialized\n");
}


/*
 * transform
 */
static const Vec3<float> yaxis = {0.0f, 1.0f, 0.0f};
static const float ztrans = -(float)(OCTREE_SIZE / 2);
static const float xlimit = (float)(OCTREE_SIZE / 4);
static float yangle = 0.0f;
static float xtrans = -xlimit;
static float ytrans = -xlimit;
static float xsens = 2.0f;

void Core::transform()
{
	this->camera->resetTransformation();
	this->camera->rotate(yaxis, yangle);
	Vec3<float> translate =  {xtrans, ytrans, ztrans};
	this->camera->translate(translate);
	if(xtrans > xlimit) xsens = -2.0f;
	if(xtrans < -xlimit) xsens = 2.0f;
	xtrans += xsens;
	ytrans += xsens;
	yangle += 0.0349f * xsens; //2°
}


/*
 * process
 */
void Core::process(Render *render)
{
	this->transform();
	this->camera->getBasis(&this->viewplane->basis);
	Octree::initRayCast(&this->viewplane->basis);
	this->viewplane->resetScan();
	render->resetDraw();
	do
	{
		this->viewplane->getScanPosition(scanpos);
		math::vecadd(this->camera->nearcenter, scanpos);
		Octree::resetRayCast();
		Octree::rayCast();
		if(Octree::curbit->voxel != NULL)
		{
			render->setPixel(Octree::getColorDepth());
		}
		render->nextPixel();
	} while(this->viewplane->scan());
}
