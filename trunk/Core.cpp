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
	delete this->space;
	delete this->camera;
	delete this->partition;
	delete this->viewplane;
}


/*
 * init
 */
Vec3<float> *scanpos = NULL;

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
	this->viewplane->create(VIEW_WIDTH, VIEW_HEIGHT);

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

	Vec3<float> yaxis = {0.0f, 1.0f, 0.0f};
	this->camera->rotate(yaxis, yangle);

	Vec3<float> translate =  {0.0f, 0.0f, -68.0f};
	this->camera->translate(translate);

	yangle+=0.02;
}


/*
 * process
 */
void Core::process(Render *render)
{
	this->transform();

	this->camera->getBasis(&(this->viewplane->basis));
	const Vec3<float> kbase = this->viewplane->basis.k;

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
{/*
	Core *core = new Core();
	core->init();

	Render *render = new Render();
	render->setCore(core);
	render->init(argc, argv);*/

	//

	Voxel voxel =
	{
		0xFF,
		{0, 0, 16383}
	};

	Vec3<float> kbase =
	{
		0.0f, 0.0f, 1.0f
	};

	SUI level = 16;//max
	SUI osize = pow(2, (level-1) );
	printf("octant size %i\n\n", osize);

	Octant *root = new Octant();
	Octree::initRoot(osize, level, osize/2, root);

	root->setBit(&voxel);

	printf("\nRayCasting started\n");
	Octree::resetRayCast(&kbase);
	Octree::rayCast();

	return 1;
}

