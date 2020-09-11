/*
 * Cloud of Voxels (CoV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Creation Date: 2011
 * Modification Date: 2020
 */

#ifndef RENDERER_H
#define RENDERER_H

    #include <GL/freeglut.h>
    #include <math.h>
    #include "Options.h"

    #define SCR_WIDTH Options::SCR_WIDTH
    #define SCR_HEIGHT Options::SCR_HEIGHT
    #define SCR_HALF_WIDTH Options::SCR_HALF_WIDTH
    #define SCR_HALF_HEIGHT Options::SCR_HALF_HEIGHT
    #define COLOR_BYTES_NUMBER 4

    class Core;
    class Render
    {
        public:
        static UC PIXEL_STEP;
        static float CAM_Y_ROTATION;

        private:
        bool ready;
        UC* pixels;
        Core* core;
        GLuint list;
        GLuint surface;
        GLuint texture;

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
        void initRender();


        /*
        * initBoard
        */
        void initSurface();


        /*
        * drawAsQuads
        */            
        void drawAsQuads();


        /*
        * drawAsQuads
        */
        void drawAsPixels();

    };

#endif

