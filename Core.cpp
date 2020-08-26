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
    this->ztrans = (float)Options::CAM_Z_TRANSLATION;
    this->xlimit = (float)(Options::SCR_WIDTH / 4);
    this->ytrans = -xlimit;
    this->xsens = 2.0f;
    this->xtrans = -xlimit;
    this->yangle = 0.0f;
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
    unsigned int n = Options::Options::OCTREE_SIZE;
    do
    {
        level += 1;
    } while((n >>= 1) != 1);
    printf("octree number of level %i\n", level);
    
	this->camera = new Camera();
	this->octree->initRoot(Options::OCTREE_SIZE, level, Options::MAX_RAY_LENGTH);
	this->octree->addVoxels(monkey, MESH_SIZE);
	printf("Core initialized\n");
}

void Core::transform()
{
	this->camera->resetTransformation();
	this->camera->rotate({0.0f, 1.0f, 0.0f}, this->yangle);
	this->camera->translate({
        Options::nomotion ? 0.0f : this->xtrans,
        Options::nomotion ? 0.0f : this->ytrans,
        ztrans
    });
	
    if(!Options::nomotion)
    {
        if(this->xtrans > this->xlimit) this->xsens = -2.0f;
        if(this->xtrans < -this->xlimit) this->xsens = 2.0f;
        this->xtrans += this->xsens;
        this->ytrans += this->xsens;
	}
    this->yangle += 0.0349f * this->xsens;
}


/*
 * Jump to next pixel
 */
bool Core::nextPixel(Vec2<SI>* const curpix)
{
	if((curpix->x += Options::PIXEL_STEP) >= Options::SCR_HALF_WIDTH)
	{
		curpix->x = -Options::SCR_HALF_WIDTH;
        if((curpix->y += Options::PIXEL_STEP) >= Options::SCR_HALF_HEIGHT)
        {
            return false;
        }
	}
    return true;
}

/*
 * process
 */
void Core::process()
{
    Mat3f basis = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };
    Vec2<SI> curpix = {
        (SI)-Options::SCR_HALF_WIDTH,
        (SI)-Options::SCR_HALF_HEIGHT
    };
	this->camera->getBasis(&basis);
	this->octree->initBasis(&basis);
	
    glNewList(1, GL_COMPILE);
    glBegin(GL_POINTS);
        do
        {
            // Generates ray coordinates from current the pixel
            Vec3<float> ray = math::vecxscl(basis.i, curpix.x);
            math::vecadd(math::vecxscl(basis.j, curpix.y), &ray);
           
            // Reajusts the ray
            this->camera->reajust(&ray);
            this->octree->setRay(&ray);
            
            // Display a pixel if the ray hits a voxel.
            if(this->octree->rayTrace())
            {
                const Color color = this->octree->getColorDepth(
                Octree::curbit->voxel.color);
                
                glColor3ub(color.r, color.g, color.b);
                glVertex2i(curpix.x, curpix.y);
            }
            
            if(!this->nextPixel(&curpix)) break;
        }
        while(true);
    glEnd();
    glEndList();
}
