/*
 * Cloud of Voxels (CoV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Creation Date: 2011
 * Modification Date: 2020
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
    this->yangle = 0.01745f * 180.0f;
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
    bool warning = false;
    this->octree = new Octree();
    
    SUI level = 0;
    unsigned int n = Options::OCTREE_SIZE;
    do
    {
        level += 1;
        if((n & 1) != 0) {
            warning = true;
        }
    } while((n >>= 1) != 1);
    printf("Number of level in the octree: %i\n", level);
    if(warning) {
        printf("!!!Warning octree size not a power of 2!!!\n");
    }
    
	this->camera = new Camera();
    printf("Adding voxels, please wait...\n");
    this->octree->initRoot(Options::OCTREE_SIZE, level, Options::MAX_RAY_LENGTH);
	this->octree->addVoxels(monkey, MESH_SIZE);
    
    if(Options::ACCELERATED)
    {
        this->octree->initAccelerator();
        printf("Core initialized with acceleration\n");
    } else printf("Core initialized\n");
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
    this->yangle += Options::CAM_Y_ROTATION * this->xsens;
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
    
    const UC step = Options::PIXEL_STEP;
    
	this->camera->getBasis(&basis);
	this->octree->initBasis(&basis);
	
    do
    {
        // Generates ray coordinates from current the pixel
        Vec3<float> ray = math::vecxscl(basis.i, curpix.x);
        math::vecadd(math::vecxscl(basis.j, curpix.y), &ray);
        // Reajusts the ray
        this->camera->reajust(&ray);
        this->octree->setRay(&ray);
        // Display a pixel if the ray hits a voxel.
        vector<DynamicVoxel> voxels;
        if(this->octree->rayTrace(&voxels))
        {
            UC i = voxels.size(), end = 0;
            if(i > Options::MAX_VOXELS_BY_RAY)
            {
                end = i - Options::MAX_VOXELS_BY_RAY;
            }
            
            if(Options::INTERNAL_BLENDING)
            {
                i--;
                Voxel voxel = *(voxels[i].voxel);
                const float depth = voxels[i].depth;
                
                UC ro = (voxels[i].voxel->color & 0xFF000000) >> 24;
                UC go = (voxels[i].voxel->color & 0x00FF0000) >> 16;
                UC bo = (voxels[i].voxel->color & 0x0000FF00) >> 8;
                    
                while(i-- > end)
                {
                    const UI r = (voxels[i].voxel->color & 0xFF000000) >> 24;
                    const UI g = (voxels[i].voxel->color & 0x00FF0000) >> 16;
                    const UI b = (voxels[i].voxel->color & 0x0000FF00) >> 8;
                    const float a = (voxels[i].voxel->color & 0x000000FF) / 255.0f;
                    
                    ro = (UC)(r * a + (1.0f - a) * ro);
                    go = (UC)(g * a + (1.0f - a) * go);
                    bo = (UC)(b * a + (1.0f - a) * bo);
                }
                
                voxel.color = (ro << 24) | (go << 16) | (bo << 8 ) | (voxel.color & 0x000000FF);
                DynamicVoxel dynamic = {depth, &voxel};
                
                const Color color = this->octree->getColorDepth(&dynamic);
                glColor4ub(color.r, color.g, color.b, color.a);
                    glBegin(GL_QUADS);
                    glVertex2i(curpix.x - step, curpix.y - step);
                    glVertex2i(curpix.x + step, curpix.y - step);
                    glVertex2i(curpix.x + step, curpix.y + step);
                    glVertex2i(curpix.x - step, curpix.y + step);
                glEnd();
            } else
            {
                while(i-- > end)
                {
                    const Color color = this->octree->getColorDepth(&voxels[i]);
                    glColor4ub(color.r, color.g, color.b, color.a);
                    glBegin(GL_QUADS);
                    glVertex2i(curpix.x - step, curpix.y - step);
                    glVertex2i(curpix.x + step, curpix.y - step);
                    glVertex2i(curpix.x + step, curpix.y + step);
                    glVertex2i(curpix.x - step, curpix.y + step);
                    glEnd();
                }
            }
        }
        if(!this->nextPixel(&curpix)) break;
    }
    while(true);
}
