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
    
    const SI raylength = (SCR_SIZE/2)*2;
    
	this->camera = new Camera();
    
    printf("Max ray length %i\n", raylength);
    printf("octree size %i\n", OCTREE_SIZE);
	printf("octree number of level %i\n", level);

	this->octree->initRoot(OCTREE_SIZE, level, raylength);
	this->octree->addVoxels(monkey, MESH_SIZE);

	printf("Core initialized\n");
}


/*
 * transform
 */
static const Vec3<float> yaxis = {0.0f, 1.0f, 0.0f};
static const float ztrans = -(float)(SCR_SIZE / 2);
static const float xlimit = (float)(SCR_SIZE / 4);

float ytrans = -xlimit;
float xsens = 2.0f;
float xtrans = -xlimit;
float yangle = 0.0f;

void Core::transform()
{
	this->camera->resetTransformation();
	this->camera->rotate(yaxis, yangle);
	Vec3<float> translate = {
        Options::nomotion ? 0.0f : xtrans,
        Options::nomotion ? 0.0f : ytrans,
        ztrans
    };
	this->camera->translate(translate);
	
    if(!Options::nomotion)
    {
        if(xtrans > xlimit) xsens = -2.0f;
        if(xtrans < -xlimit) xsens = 2.0f;
        xtrans += xsens;
        ytrans += xsens;
	}
    yangle += 0.0349f * xsens;
}

/*
 * process ray
 */
void Core::processRay(Render* const render, Vec3<float>* const ray)
{
    this->camera->reajust(ray);
    this->octree->setRay(ray);
    this->octree->rayTrace(); //
    if(Octree::curbit->voxel != NULL) //
    {
        render->setPixel(this->octree->getColorDepth());
    }
}

/*
 * process
 */
void Core::process(Render* const render)
{
    Mat3f basis = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };
    
	this->transform();
	this->camera->getBasis(&basis);
	this->octree->initBasis(&basis);
	render->reset();
    
	do
	{
        Vec3<float> ray = render->getPixelCoordinates(&basis);
        this->processRay(render, &ray);
        if(!render->nextPixel()) break;
	}
    while(true);
}
