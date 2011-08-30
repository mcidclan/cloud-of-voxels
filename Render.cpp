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

	glViewport(0, 0, SRC_WIDTH, SRC_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SRC_WIDTH, SRC_HEIGHT, 0, 0, 1);


	glGenTextures(2, tid);

	glBindTexture(GL_TEXTURE_2D, this->tid[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 1, SRC_WIDTH, SRC_HEIGHT, 0, GL_LUMINANCE,
	GL_UNSIGNED_BYTE, NULL);

	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, SRC_WIDTH, SRC_HEIGHT, 0);


	glBindTexture(GL_TEXTURE_2D, this->tid[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, 1, SRC_WIDTH, SRC_HEIGHT, 0, GL_LUMINANCE,
	GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	dwplane = glGenLists(1);

	glNewList(dwplane, GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2i(0,0);
			glVertex2i(0,SRC_HEIGHT);
			glTexCoord2i(0,1);
			glVertex2i(0,0);
			glTexCoord2i(1,1);
			glVertex2i(SRC_WIDTH,0);
			glTexCoord2i(1,0);
			glVertex2i(SRC_WIDTH,SRC_HEIGHT);
		glEnd();
	glEndList();

	glEnable(GL_TEXTURE_2D);
}


/*
 * 
 */
void Render::init(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE/*| GLUT_DOUBLE*/);
	glutInitWindowSize(SRC_WIDTH, SRC_HEIGHT);

	glutInitWindowPosition(10, 10);
	glutCreateWindow("cov");

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

	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, SRC_WIDTH,SRC_HEIGHT);


	if(core != NULL)
	{
		((Core*)core)->process(this);
	}

	glCallList(dwplane);

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
	glTexSubImage2D(GL_TEXTURE_2D, 0, this->curpixi, this->curpixj, 1, 1,
	GL_LUMINANCE, GL_UNSIGNED_BYTE, &color);
}


/*
 * Jump to next pixel
 */
void Render::nextPixel()
{
	this->curpixi++;
	if(this->curpixi >= SRC_WIDTH)
	{
		this->curpixi = 0;
		this->curpixj++;
	}
}


