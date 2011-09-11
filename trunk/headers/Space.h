/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef SPACE_H
#define SPACE_H

	#include "./Partition.h"

	class Space
	{
		public:
			/*
			 * Contructor
			 */
			Space();


			/*
			 * Destructor
			 */
			~Space();


			/*
			 * setPartition
			 */
			void setPartition(Partition *partition);


			/*
			 * addVoxels
			 */
			bool addVoxels(Voxel *voxels, const UI nvoxel);


		private:
			Partition *partition;


	};


#endif


