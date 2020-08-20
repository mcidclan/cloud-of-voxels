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
    delete this->octree;
	delete this->camera;
	delete this->viewplane;
}



/*
 * init
 */
void Core::init()
{
    this->octree = new Octree();
    
    SUI level = 0;
    unsigned int n = OCTREE_SIZE;
    do{
        level += 1;
    } while((n >>= 1) != 1);
    
    const SI raylength = (SCR_SIZE/2)*2);
    
	this->camera = new Camera();
    
    printf("Max ray length %i\n", raylength);
    printf("octree size %i\n", OCTREE_SIZE);
	printf("octree number of level %i\n", level);

	this->octree->initRoot(OCTREE_SIZE, level, raylength);
	this->octree->addVoxels(monkey, MESH_SIZE);

	this->viewplane = new Viewplane();
	this->viewplane->create(VIEW_WIDTH, VIEW_HEIGHT);

	printf("Core initialized\n");
}


/*
 * transform
 */
static const Vec3<float> yaxis = {0.0f, 1.0f, 0.0f};
static const float ztrans = -(float)(OCTREE_SIZE / 2);
static const float xlimit = (float)(OCTREE_SIZE / 4);

float ytrans = -xlimit;
float xsens = 2.0f;
float xtrans = -xlimit;
float yangle = 0.0f;

void Core::transform()
{
	this->camera->resetTransformation();
	this->camera->rotate(yaxis, yangle);
	Vec3<float> translate = {xtrans, ytrans, ztrans};
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
	this->octree->initRayCast(&this->viewplane->basis);
	this->viewplane->resetScan();
	render->resetDraw();
	do
	{
		this->viewplane->getScanPosition(&this->octree->raypos);
		math::vecadd(this->camera->nearcenter, &this->octree->raypos);
        
		this->octree->resetRayCast();
		this->octree->rayCast();
		
        if(this->octree->curbit->voxel != NULL)
		{
			render->setPixel(this->octree->getColorDepth());
		}
		render->nextPixel();
	} while(this->viewplane->scan());
}
