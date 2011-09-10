/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Date: 2011
 */

#ifndef OCTREE_H
#define OCTREE_H

	#include "./Octant.h"


	class Octree
	{

		public:
			static SUI depth;
			static SUI maxdepth;
			static SUI rootsize;

			static Vec3<SUI> center;
			static Vec3<SUI> locpos;
			static Vec3<float> raypos;
			static Vec3<float> raybit;
			static Vec3<float> *kbase;

			static float depthray;
			static float raylength;

			static Octant *curbit;
			static Octant *root;


		public:
			/*
			 * Delete childreen
			 */
			static void delChildreen(Octant *octant);


			/*
			 *
			 */
			static void initRoot(SUI rootsize, SUI maxdepth,
			const float raylength, Octant *root);


			/*
			 *
			 */
			static void initChild(const UC i, const UC j, const UC k,
			Octant *parent);


			/*
			 * Add children to the current octant
			 */
			static void addChildren(Octant *octant);


			/*
			 * Set bit space
			 */
			static void setBit(Voxel *voxel, Octant *octant);


			/*
			 * Update locpos after findind the corresponding relative
			 * position of v in the current octant.
			 */
			template <typename T>
			static void updateLocalPosition(Vec3<T> v, Octant *parent)
			{
				/*if(octant->parent != NULL)
				{
					printf("-- %i %i %i\n", octant->parent->pos.x, octant->parent->pos.y, octant->parent->pos.z);
					math::vecsub(octant->parent->pos, &v);
				}*/

				math::vecsub(parent->pos, &v);
				math::vecxscl(&v, parent->children[0][0][0].scoef);
				math::cpvec(v, &Octree::locpos);
			}


			/*
			 * resetRayCast //kbase must be normalized
			 */
			static void resetRayCast(Vec3<float> *kbase);


			/*
			 * rayCast
			 */
			static void rayCast();


	};

#endif


