/*
 * Cloud of Voxels (CoV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Creation Date: 2011
 * Modification Date: 2020
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
            static UC PIXEL_STEP;
            static float CAM_Y_ROTATION;
            
        private:
            bool ready;
            Core* core;
            GLuint list;
            
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
            void init(int argc, char **argv, Core* const core);


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


        private:
            /*
             * initBoard
             */
            void initBoard();
	};


#endif


