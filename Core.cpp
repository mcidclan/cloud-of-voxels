/*
 * Cloud of voxels (COV) project
 * Author: by mcidclan. m.cid.clan@gmail.com
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
	delete this->space;
	delete this->camera;
	delete this->partition;
	delete this->viewplane;
}


/*
 * init
 */
Vec3f *scanpos = NULL;

void Core::init()
{
	this->camera = new Camera();

	this->partition = new Partition();
	this->partition->create(300, 300, 300);
	this->partition->setMaxDepth(68);

	this->space = new Space();
	this->space->setPartition(this->partition);
	this->space->addVoxels(monkey, MESH_SIZE);

	this->viewplane = new Viewplane();
	this->viewplane->create(SRC_WIDTH, SRC_HEIGHT);

	scanpos = &this->partition->scanpos;

	printf("Core initialized\n"); 
}


/*
 * transform
 */
float yangle = 0.0f;
void Core::transform()
{
	this->camera->resetTransformation();

	Vec3f yaxis = {0.0f, 1.0f, 0.0f};
	this->camera->rotate(yaxis, yangle);

	Vec3f translate =  {0.0f, 0.0f, -68.0f};
	this->camera->translate(translate);

	yangle+=0.03;
}


/*
 * process
 */
void Core::process(Render *render)
{
	this->transform();

	this->camera->getBasis(&(this->viewplane->basis));
	const Vec3f kbase = this->viewplane->basis.k;

	this->viewplane->resetScan();
	render->resetDraw();

	do
	{
		this->viewplane->getScanPosition(scanpos);
		math::vecadd(this->camera->nearcenter, scanpos);

		this->partition->resetDepthScan(&kbase);
		this->partition->depthScan();

		if(this->partition->curvoxel != NULL)
		{
			render->setPixel(this->partition->getColorDepth());
		}

		render->nextPixel();

	} while(this->viewplane->scan());
}


/*
 * main
 */
int main(int argc, char *argv[])
{
	Core *core = new Core();
	core->init();

	Render *render = new Render();
	render->setCore(core);
	render->init(argc, argv);

	return 1;
}


