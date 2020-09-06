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
    SUI level = 0;
    bool warning[2] = {
        !math::isPowerOfTwo(Options::OCTREE_SIZE, &level),
        (!math::isPowerOfTwo(Options::SCR_WIDTH, NULL) ||
        !math::isPowerOfTwo(Options::SCR_HEIGHT, NULL)) &&
        !Options::QUADS_AS_PIXELS
    };
    printf("Number of level in the octree: %i\n", level);
    
    if(warning[0]) {
        printf("!!!Warning!!! Octree size is not a power of 2\n");
    }
    if(warning[1]) {
        printf("!!!Warning!!! Texture rendering size is not a power of 2\n");
    }
    
    this->octree = new Octree();   
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


void Core::setPixel(Vec2<SI>* const curpix, DynamicVoxel* const voxel)
{
    const UC step = Options::PIXEL_STEP;
    const Color color = this->octree->getColorDepth(voxel);                
    glColor4ub(color.r, color.g, color.b, color.a);
    glBegin(GL_QUADS);
    glVertex2i(curpix->x - step, curpix->y - step);
    glVertex2i(curpix->x + step, curpix->y - step);
    glVertex2i(curpix->x + step, curpix->y + step);
    glVertex2i(curpix->x - step, curpix->y + step);
    glEnd();
}
 
 
/*
 * process
 */
void Core::process(UC* const pixels)
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
            
            if(Options::INTERNAL_BLENDING || !Options::QUADS_AS_PIXELS)
            {
                Voxel voxel = *(voxels[i-1].voxel);
                const float depth = voxels[0].depth;
                
                UC ro = 0, go = 0, bo = 0, alpha = 0;
                
                while(i-- > end)
                {
                    const UI r = (voxels[i].voxel->color & 0xFF000000) >> 24;
                    const UI g = (voxels[i].voxel->color & 0x00FF0000) >> 16;
                    const UI b = (voxels[i].voxel->color & 0x0000FF00) >> 8;
                    float a = (voxels[i].voxel->color & 0x000000FF);
                    if(a > alpha) {
                        alpha = a;
                    }
                    
                    const float d = this->octree->getDarkness(voxels[i].depth);
                    a = (a / 255.0f) * d;
                    
                    ro = (UC)(r * a + (1.0f - a) * ro);
                    go = (UC)(g * a + (1.0f - a) * go);
                    bo = (UC)(b * a + (1.0f - a) * bo);
                }
                
                if(pixels == NULL)
                {
                    voxel.color = (ro << 24) | (go << 16) | (bo << 8 ) | alpha;
                    DynamicVoxel dynamic = {depth, &voxel};
                    this->setPixel(&curpix, &dynamic);
                } else
                {   
                    const SUI x = (curpix.x / Options::PIXEL_STEP) + Options::SCR_HALF_WIDTH;
                    const SUI y = (curpix.y / Options::PIXEL_STEP) + Options::SCR_HALF_HEIGHT;
                    const UI offset = COLOR_BYTES_NUMBER * (x + y * Options::SCR_WIDTH);
                    
                    pixels[offset] = ro;
                    pixels[offset+1] = go;
                    pixels[offset+2] = bo;
                    pixels[offset+3] = alpha;
                }
            } else
            {
                while(i-- > end)
                {
                    this->setPixel(&curpix, &voxels[i]);
                }
            }
        }
        if(!this->nextPixel(&curpix)) break;
    }
    while(true);
}
