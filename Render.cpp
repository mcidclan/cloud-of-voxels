/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */
 
#include "./headers/Render.h"
#include "./headers/Core.h"


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
void Render::timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(Options::MAX_FRAME_TIME/1000, Render::timer, value);
}


/*
 * 
 */
void Render::initBoard()
{
    glDepthFunc(GL_LESS); 
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(Options::PIXEL_STEP);
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
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH | GLUT_SINGLE);
	glutInitWindowSize(Options::SCR_WIDTH, Options::SCR_HEIGHT);

	glutInitWindowPosition(10, 10);
	glutCreateWindow("Cloud of Voxels");

	glutReshapeFunc(Render::reshape);
    glutDisplayFunc(Render::display);
    glutIdleFunc(Render::idle);
    
	this->initBoard();

    Render::timer(0);
	glutMainLoop();
    
	printf("Renderer initialized\n");
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
    gluOrtho2D(-halfw, halfw, halfh, -halfh);
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
        this->core->transform();
        this->core->process();
        this->ready = true;
    }
}


/*
 * 
 */
void Render::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCallList(1);
    glFlush();

    // Make sure that the core process is sync
    if(this->ready)
    {
        this->ready = false;
    }
}
