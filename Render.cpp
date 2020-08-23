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
    glDeleteLists(this->list, 1);
}


/*
 * 
 */
void Render::timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(40, Render::timer, value); //25 frames per second
}


/*
 * 
 */
void Render::initBoard()
{
    glPointSize(Options::PIXEL_STEP);
    this->list = glGenLists(1);
}


/*
 * 
 */
void Render::init(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
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
 * setCore
 */
void Render::setCore(Core* const core)
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
    gluOrtho2D(0.0, width, height, 0.0);
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
    if(core != NULL)
	{
        this->core->process(this);
    }
}

/*
 * 
 */
void Render::draw()
{   
	glClear(GL_COLOR_BUFFER_BIT);
    glCallList(this->list);
	glFlush();
}


/*
 * Reset pixel position at the begining of the drawing board
 */
void Render::reset()
{
	this->curpixi =
	this->curpixj = 0;
}


/*
 * Set the current pixel on the drawing board.
 */
void Render::setPixel(const Color color)
{
    glColor3ub(color.r, color.g, color.b);
	glVertex2i(this->curpixi,this->curpixj);
}


/*
 * Jump to next pixel
 */
bool Render::nextPixel()
{
	if((this->curpixi += Options::PIXEL_STEP) >= Options::SCR_WIDTH)
	{
		this->curpixi = 0;
        if((this->curpixj += Options::PIXEL_STEP) >= Options::SCR_HEIGHT)
        {
            return false;
        }
	}
    return true;
}


/*
 * getPixelCoordinates
 */
Vec3<float> Render::getPixelCoordinates(const Mat3f* const basis)
{
    const float v = (float)(this->curpixi - Options::SCR_HALF_WIDTH);
    const float h = (float)(this->curpixj - Options::SCR_HALF_HEIGHT);

    Vec3<float> i = math::vecxscl(basis->i, v);
    const Vec3<float> j = math::vecxscl(basis->j, h);
    math::vecadd(j, &i);
    
    return i;
}
