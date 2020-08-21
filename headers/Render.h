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
    const short UI OCTREE_SIZE = 512;
    // Calculate the screen size, makes sure that the size used for the scan,
    // never goes outsite of the octree limits.
    const short UI SCR_SIZE = (((short UI)sqrt((double)(OCTREE_SIZE*OCTREE_SIZE)/2))/2)*2;
    const short UI SCR_WIDTH = SCR_SIZE;
	const short UI SCR_HEIGHT = SCR_SIZE;
    
    const short UI SCR_HALF_WIDTH = SCR_WIDTH / 2;
    const short UI SCR_HALF_HEIGHT = SCR_HEIGHT / 2;
    const UC PIXEL_STEP = 1;
    
    class Core;
    
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
			void setCore(Core* const core);


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
			void reset();


			/*
			 * Set the current pixel on the drawing board.
			 */
			void setPixel(unsigned char color);


			/*
			 * Jump to next pixel
			 */
			bool nextPixel();


			/*
			 * Get current pixel coordinates
			 */
            Vec3<float> getPixelCoordinates(const Mat3f* const basis);


			private:
				Core* core;
                UC* pixels;
    
				SI curpixi;
				SI curpixj;
                
				GLuint dwplane;
	};


#endif


