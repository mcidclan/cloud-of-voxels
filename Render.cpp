/*
 * Cloud of Voxels (CoV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Creation Date: 2011
 * Modification Date: 2020
 */
 
#include "./headers/Render.h"
#include "./headers/Core.h"

UC Render::PIXEL_STEP = 1;
float Render::CAM_Y_ROTATION = 0.0f;

static Render *render = NULL;

/*
 * 
 */
Render::Render()
{
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

static int key(unsigned int args, void *argp)
{
    const float step = 0.01745f;
    while(true)
    {
        SceCtrlData pad;
        sceCtrlReadBufferPositive(&pad, 1);
        Render::PIXEL_STEP = 1;
        Render::CAM_Y_ROTATION = 0.0f;
        
        if(pad.Buttons & PSP_CTRL_LEFT)
        {
            Render::PIXEL_STEP = 3;
            Render::CAM_Y_ROTATION = -step;
        }
        if(pad.Buttons & PSP_CTRL_RIGHT)
        {
            Render::PIXEL_STEP = 3;
            Render::CAM_Y_ROTATION = step;
        }
        
        sceKernelDelayThread(100000);
    }
}

void Render::timer(int value)
{
    SceUID id = sceKernelCreateThread("cov_loop", loop, 0x0A, 0x1000, 0, 0);
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
void Render::initBoard()
{
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    
    this->list = glGenLists(1);
    this->ready = false;
}


/*
 * 
 */
void Render::init(int argc, char **argv, Core* const core)
{
    this->core = core;
	
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
	glutInitWindowSize(Options::WIN_WIDTH, Options::WIN_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("CloudOfVoxels");
	
    glutDisplayFunc(Render::display);
    #ifndef PSP
    glutReshapeFunc(Render::reshape);
    #endif
	glutIdleFunc(Render::idle);
    
    this->initBoard();
    #ifdef PSP
    Render::reshape(Options::WIN_WIDTH, Options::WIN_HEIGHT);
    #endif
    
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
    if(!this->ready)
    {
        #ifdef PSP
        Options::PIXEL_STEP = Render::PIXEL_STEP;
        Options::CAM_Y_ROTATION = Render::CAM_Y_ROTATION;
        #endif
        this->core->transform();
        glNewList(this->list, GL_COMPILE);
        this->core->process();
        glEndList();
        this->ready = true;
    }
}

/*
 * 
 */
void Render::draw()
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
