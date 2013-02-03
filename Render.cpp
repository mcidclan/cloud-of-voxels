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
	this->core = NULL;
	render = this;
}


/*
 * 
 */
Render::~Render()
{
	glDeleteLists(dwplane, 1);
	glDeleteTextures(2, tid);
}


/*
 * 
 */
void Render::timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(16, Render::timer, value);
}


/*
 * 
 */
void Render::initBoard()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
    glPointSize(1);
}


/*
 * 
 */
void Render::init(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_LUMINANCE | GLUT_SINGLE/* | GLUT_DOUBLE*/);
	glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);

	glutInitWindowPosition(10, 10);
	glutCreateWindow("Cloud of Voxels");

	glutReshapeFunc(Render::reshape);
    glutDisplayFunc(Render::display);

	this->initBoard();

	printf("Renderer initialized\n");

	Render::timer(0);
	glutMainLoop();
}


/*
 * setCore
 */
void Render::setCore(void *core)
{
	this->core = core;
}


/*
 * 
 */
void Render::reshape(int width, int height)
{
    glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(SCR_WIDTH, 0, 0, SCR_HEIGHT, -1, 1);
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
void Render::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINT);

	if(core != NULL)
	{
		((Core*)core)->process(this);
	}

    glEnd();

	glutSwapBuffers();
}


/*
 * Reset pixel position at the begining of the drawing board
 */
void Render::resetDraw()
{
	this->curpixi =
	this->curpixj = 0;
}


/*
 * Set the current pixel on the drawing board.
 */
void Render::setPixel(const unsigned char color)
{
    glColor3ub(color, color, color);
	glVertex2i(this->curpixi,this->curpixj);
}


/*
 * Jump to next pixel
 */
void Render::nextPixel()
{
	this->curpixi++;
	if(this->curpixi >= VIEW_WIDTH)
	{
		this->curpixi = 0;
		this->curpixj++;
	}
}


