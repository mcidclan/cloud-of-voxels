/*
 * Cloud of Voxels (CoV) project
 * Author: m-c/d, mcidclan
 * Creation Date: 2011
 * Modification Date: 2025
 */
 
#include "./headers/Render.h"
#include "./headers/Core.h"

UC Render::PIXEL_STEP = 1;
float Render::CAM_Y_ROTATION = 0.0f;
float Render::CAM_X_ROTATION = 0.0f;

static Render *render = NULL;

/*
 * 
 */
Render::Render()
{
    this->pixels = NULL;
	render = this;
}


/*
 * 
 */
Render::~Render()
{
    glDeleteLists(this->list, 1);
}

    
/*
 * 
 */
#ifndef PSP
void Render::timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(Options::MAX_FRAME_TIME/1000, Render::timer, value);
}
#else
static int loop(unsigned int args, void *argp)
{
    while(true)
    {
        glutPostRedisplay();
        sceKernelDelayThread(10);
    }
}

#define PIXEL_STEP_DURING_ROTATION 2

static int key(unsigned int args, void *argp)
{
    const float step = 0.01745f * 10.0f;
    while(true)
    {
        SceCtrlData pad;
        sceCtrlReadBufferPositive(&pad, 1);
        Render::PIXEL_STEP = 1;
        Render::CAM_Y_ROTATION = 0.0f;
        Render::CAM_X_ROTATION = 0.0f;
        
        if(pad.Buttons & PSP_CTRL_LEFT)
        {
            Render::PIXEL_STEP = PIXEL_STEP_DURING_ROTATION;
            Render::CAM_Y_ROTATION = -step;
        }
        if(pad.Buttons & PSP_CTRL_RIGHT)
        {
            Render::PIXEL_STEP = PIXEL_STEP_DURING_ROTATION;
            Render::CAM_Y_ROTATION = step;
        }
        if(pad.Buttons & PSP_CTRL_UP)
        {
            Render::PIXEL_STEP = PIXEL_STEP_DURING_ROTATION;
            Render::CAM_X_ROTATION = -step;
        }
        if(pad.Buttons & PSP_CTRL_DOWN)
        {
            Render::PIXEL_STEP = PIXEL_STEP_DURING_ROTATION;
            Render::CAM_X_ROTATION = step;
        }
        
        sceKernelDelayThread(10000);
    }
}

void Render::timer(int value)
{
    SceUID id = sceKernelCreateThread("cov_loop", loop, 0x0A, 0x10000, 0, 0);
    if (id >= 0)
    {
        sceKernelStartThread(id, 0, 0);
    }    
    id = sceKernelCreateThread("cov_key", key, 0x10, 0x1000, 0, 0);
    if (id >= 0){
        sceKernelStartThread(id, 0, 0);
    }
}
#endif


/*
 * 
 */
void Render::initRender()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    if(Options::QUADS_AS_PIXELS)
    {
        glFrontFace(GL_CW);
        this->list = glGenLists(1);
    } else initSurface();
    this->ready = false;
}


void Render::initSurface()
{
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    this->pixels = (UC*)malloc(SCR_WIDTH * SCR_HEIGHT * COLOR_BYTES_NUMBER);
    memset(this->pixels, 0, SCR_WIDTH * SCR_HEIGHT * COLOR_BYTES_NUMBER);
    
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    
    if(Options::SMOOTH_PIXELS)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT,
    0, GL_RGBA, GL_UNSIGNED_BYTE, this->pixels);
    
    this->surface = glGenLists(1);
    glNewList(this->surface, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex2i(-SCR_HALF_WIDTH, -SCR_HALF_HEIGHT);
    glTexCoord2d(0, 1); glVertex2i(-SCR_HALF_WIDTH, SCR_HALF_HEIGHT);
    glTexCoord2d(1, 1); glVertex2i(SCR_HALF_WIDTH, SCR_HALF_HEIGHT);
    glTexCoord2d(1, 0); glVertex2i(SCR_HALF_WIDTH, -SCR_HALF_HEIGHT);
    glEnd();
    glEndList();
}

    
/*
 * 
 */
void Render::init(int argc, char **argv, Core* const core)
{
    this->core = core;
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
    glutInitWindowSize(Options::WIN_WIDTH, Options::WIN_HEIGHT);
    glutCreateWindow("CloudOfVoxels");
    this->initRender();
    glutDisplayFunc(Render::display);
    glutReshapeFunc(Render::reshape);
    glutIdleFunc(Render::idle);
    Render::timer(0);
    glutMainLoop();
}


/*
 * 
 */
void Render::reshape(int width, int height)
{
    const double halfw = width/2.0;
    const double halfh = height/2.0;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-halfw, halfw, halfh, -halfh, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


/*
 * 
 */
void Render::display()
{
    render->draw();
}


/*
 * 
 */

void Render::idle()
{
    render->process();
}


/*
 * 
 */
void Render::process()
{
    #ifdef PSP
    Options::PIXEL_STEP = Render::PIXEL_STEP;
    Options::CAM_Y_ROTATION = Render::CAM_Y_ROTATION;
    Options::CAM_X_ROTATION = Render::CAM_X_ROTATION;
    #endif
    if(!this->ready)
    {
        this->core->transform();
        if(Options::QUADS_AS_PIXELS)
        {
            glNewList(this->list, GL_COMPILE);
            this->core->process();
            glEndList();
        } else
        {
            memset(this->pixels, 0, SCR_WIDTH * SCR_HEIGHT * COLOR_BYTES_NUMBER);
            this->core->process(this->pixels);
        }
        this->ready = true;
    }
}


/*
 * 
 */
void Render::draw()
{
    if(Options::QUADS_AS_PIXELS)
    {
        this->drawAsQuads();
    } else this->drawAsPixels();
}

void Render::drawAsQuads()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glCallList(this->list);
    glutSwapBuffers();
    // Make sure that the core process is sync
    if(this->ready)
    {
        #ifdef PSP
        glDeleteLists(this->list, 1);
        this->list = glGenLists(1);
        #endif
        this->ready = false;
    }
}


void Render::drawAsPixels()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glEnable(GL_TEXTURE_2D);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, SCR_WIDTH, SCR_HEIGHT,
    GL_RGBA, GL_UNSIGNED_BYTE, this->pixels);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    const float scale = Options::SCR_WIDTH / (float)((SI)(Options::
    SCR_WIDTH / Options::PIXEL_STEP));
    glTranslatef(-scale/2.0f, -scale/2.0f, 0.0f);
    glScalef(scale, scale, 1.0f);
    glCallList(this->surface);
    glutSwapBuffers();
    // Make sure that the core process is sync
    if(this->ready)
    {
        this->ready = false;
    }
}
