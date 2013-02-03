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
	this->camera = new Camera();

	SUI level = 9;//16max
	SUI osize = pow(2, (level-1));
	printf("octree size %i\n", osize);

	Octree::initRoot(osize, level, 128, new Octant());
	Octree::addVoxels(monkey, MESH_SIZE);

	this->viewplane = new Viewplane();
	this->viewplane->create(VIEW_WIDTH, VIEW_HEIGHT);

	scanpos = &Octree::raypos;

	printf("Core initialized\n");
}


/*
 * transform
 */
static float yangle = 0.0f;
static float xtrans = -32.0f;
static float ytrans = -32.0f;
static float xsens = 2.0f;

void Core::transform()
{
	this->camera->resetTransformation();

	static const Vec3<float> yaxis = {0.0f, 1.0f, 0.0f};
	this->camera->rotate(yaxis, yangle);

	Vec3<float> translate =  {xtrans, ytrans, -64.0f};
	this->camera->translate(translate);

	if(xtrans > 32.0f) xsens = -2.0f;
	if(xtrans < -32.0f) xsens = 2.0f;
	xtrans += xsens;
	ytrans += xsens;

	yangle += 0.0349f * xsens;//2°
}


/*
 * process
 */
void Core::process(Render *render)
{
	this->transform();

	this->camera->getBasis(&(this->viewplane->basis));

	Octree::initRayCast(&this->viewplane->basis.k);

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


/*
 * main
 */
int main(int argc, char **argv)
{
	Core *core = new Core();
	core->init();

	Render *render = new Render();
	render->setCore(core);
	render->init(argc, argv);
	return 1;
}


