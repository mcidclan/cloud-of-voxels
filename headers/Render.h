/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef RENDERER_H
#define RENDERER_H

    #ifndef MINGW
        #include <GL/glut.h>
    #else
        #include <GL/freeglut.h>
	#endif
    #include <string.h>
	#include "./types.h"
    #include <math.h>

	/*
	 * SCREEN RENDER SIZE
	 */
    const short UI OCTREE_SIZE = 512;//1024;
    // Calculate the screen size, makes sure that the size used for the scan,
    // never goes outsite of the octree limits.
    const short UI SCR_SIZE = (((short UI)sqrt((double)(OCTREE_SIZE*OCTREE_SIZE)/2))/2)*2;
    const short UI SCR_WIDTH = SCR_SIZE;
	const short UI SCR_HEIGHT = SCR_SIZE;
    
	/*
	 * VIEWPLANE RENDER SIZE
	 */
	const short UI VIEW_WIDTH = SCR_WIDTH;
	const short UI VIEW_HEIGHT = SCR_HEIGHT;


	class Render
	{
		public:
			/*
			 * Constructor
			 */
			Render();


			/*
			 * Destructor
			 */
			~Render();


			/*
			 * timer
			 */
			static void timer(int value);


			/*
			 * init
			 */
			void init(int argc, char **argv);


			/*
			 * initBoard
			 */
			void initBoard();


			/*
			 * setCore
			 */
			void setCore(void *core);


			/*
			 * display
			 */
			static void display();


			/*
			 * reshape
			 */
			static void reshape(int width, int height);


            /*
			 * draw
			 */
			void draw();


			/*
			 * Reset pixel position at the begining of the drawing board
			 */
			void resetDraw();


			/*
			 * Set the current pixel on the drawing board.
			 */
			void setPixel(unsigned char color);


			/*
			 * Jump to next pixel
			 */
			void nextPixel();


			private:
				void *core;

				UI curpixi;
				UI curpixj;

				GLuint tid[2];
				GLuint dwplane;
	};


#endif


