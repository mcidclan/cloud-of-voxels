#include "./headers/voxelmodels.h"

Voxel monkey[MESH_SIZE] __attribute__((aligned(8))) =

{
	{0xFF,{-18,-18,-18}},
	{0xFF,{-18,18,-18}},
	{0xFF,{18,18,-18}},
	{0xFF,{18,-18,-18}},
	{0xFF,{-18,-18,18}},
	{0xFF,{-18,18,18}},
	{0xFF,{18,18,18}},
	{0xFF,{18,-18,18}}
};
