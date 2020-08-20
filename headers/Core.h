/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef CORE_H
#define CORE_H

	#include "./Camera.h"
	#include "./Octree.h"
	#include "./Render.h"

	class Core
	{
        private:
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
			void process(Render *render);
        
        private:
			/*
			 * transform
			 */
			void transform();
	};


#endif


