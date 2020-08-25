/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef CORE_H
#define CORE_H

	#include "Camera.h"
	#include "Octree.h"
	#include "Render.h"
    
	class Core
	{
        private:
            float ztrans;
            float xlimit;
            float ytrans;
            float xsens;
            float xtrans;
            float yangle;

            Octree *octree;
            Camera *camera;

		public:
			/*
			 * Constructor
			 */
			Core();


			/*
			 * Destructor
			 */
			~Core();


			/*
			 * init core
			 */
			void init();


			/*
			 * process
			 */
			void process();
            
            
            /*
			 * transform
			 */
			void transform();
        

        private:
            /*
             * Jump to next pixel
             */
            bool nextPixel(Vec2<SI>* const curpix);

	};


#endif


