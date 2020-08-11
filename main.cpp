/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Project date: 2011
 * File creation date: 2020
 */
 
#include "./headers/Core.h"

/*
 * main
 */
int main(int argc, char **argv)
{
	Core *core = new Core();
	core->init();

	Render *render = new Render();
	render->setCore(core);
	render->init(argc, argv);
	return 1;
}