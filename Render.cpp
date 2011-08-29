/*
 * Cloud of voxels (COV) project
 * Author: by mcidclan. m.cid.clan@gmail.com
 * Date: 2011
 */

#include "./headers/Render.h"
#include "./headers/Core.h"


static Render *render = NULL;


Render::Render()
{
	this->core = NULL;
	render = this;
}


Render::~Render()
{
	
}


/*void Render::timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(16, Render::timer, value);
}*/


void Render::initGl()
{
	glViewport(0, 0, SRC_WIDTH, SRC_HEIGHT);

	glShadeModel(GL_FLAT);
	//glEnable(GL_POINT_SMOOTH);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SRC_WIDTH, SRC_HEIGHT, 0, 0, 1);
}


void Render::init(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(SRC_WIDTH, SRC_HEIGHT);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("2DPix<-DVVC Project");

	glutDisplayFunc(Render::display);
	glutIdleFunc(Render::display);

	this->initGl();

	printf("Render initialized\n");
	//Render::timer(0);
	glutMainLoop();
}


/*
 * setCore
 */
void Render::setCore(void *core)
{
	this->core = core;
}


void Render::display()
{
	render->draw();
}


void Render::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
		if(core != NULL)
		{
			((Core*)core)->process(this);
		}
	glEnd();

	glutSwapBuffers();
}


/*
 * resetDraw
 */
void Render::resetDraw()
{
	//this->curpix = 0;
	this->curpixi =
	this->curpixj = 0;
}


/*
 * setPixel
 */
void Render::setPixel(unsigned char color)
{
	glColor3ub(color, color, color);
	glVertex2f(this->curpixi, this->curpixj);
}


/*
 * nextPixel
 */
void Render::nextPixel()
{
	//this->curpix++;

	this->curpixi++;
	if(this->curpixi >= SRC_WIDTH)
	{
		this->curpixi = 0;
		this->curpixj++;
	}
}



