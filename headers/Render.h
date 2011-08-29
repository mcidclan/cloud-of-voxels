/*
 * Cloud of voxels (COV) project
 * Author: by mcidclan. m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef RENDERER_H
#define RENDERER_H

	#include <GL/glut.h>
	#include <string.h>
	#include "./types.h"

	#define SRC_WIDTH 134
	#define SRC_HEIGHT 134


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
			//static void timer(int value);


			/*
			 * init
			 */
			void initGl();


			/*
			 * init
			 */
			void init(int argc, char *argv[]);


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
			 * resetDraw
			 */
			void resetDraw();


			/*
			 * setPixel
			 */
			void setPixel(unsigned char color);


			/*
			 * nextPixel
			 */
			void nextPixel();


			private:
				void *core;

//				UI curpix;
				UI curpixi;
				UI curpixj;
	};


#endif


