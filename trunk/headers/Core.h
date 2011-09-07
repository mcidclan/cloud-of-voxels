/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef CORE_H
#define CORE_H

	#include "./Camera.h"
	#include "./Viewplane.h"
	#include "./Space.h"
	#include "./Render.h"


	class Core
	{

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
			 * initSpace
			 */
			void init();


			/*
			 * initSpace
			 */
			void process(Render *render);


		private:
			Space *space;
			Camera *camera;
			Partition *partition;
			Viewplane *viewplane;


		private:
			/*
			 * transform
			 */
			void transform();


	};


#endif


