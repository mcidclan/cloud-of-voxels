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
	#include "options.h"
    #include <math.h>
    
    class Core;
	class Render
	{
        public:
            GLuint list;
            
            
        private:
            Core* core;
            UC* pixels;

            SI curpixi;
            SI curpixj;

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
             * setCore
             */
            void setCore(Core* const core);


            /*
             * display
             */
            static void display();


            /*
             * process
             */
            void process();
            
            
            /*
             * idle
             */
            static void idle();
            
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
            void setPixel(const Color color);


            /*
             * Jump to next pixel
             */
            bool nextPixel();


            /*
             * Get current pixel coordinates
             */
            Vec3<float> getPixelCoordinates(const Mat3f* const basis);


        private:
            /*
             * initBoard
             */
            void initBoard();
	};


#endif


