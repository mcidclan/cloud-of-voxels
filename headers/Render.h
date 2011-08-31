/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef RENDERER_H
#define RENDERER_H

	#include <GL/glut.h>
	#include <string.h>
	#include "./types.h"


	/*
	 * SCREEN RENDER SIZE
	 */
	const short UI SCR_WIDTH = 256;
	const short UI SCR_HEIGHT = 256;


	/*
	 * VIEWPLANE RENDER SIZE
	 */
	const short UI VIEW_WIDTH = 128;
	const short UI VIEW_HEIGHT = 128;


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
			void init(int argc, char *argv[]);


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


