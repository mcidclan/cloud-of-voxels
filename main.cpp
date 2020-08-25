/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Project date: 2011
 * File creation date: 2020
 */

#include "./headers/Core.h"

using namespace std;

/*
 * main
 */
int main(int argc, char **argv)
{
    Options::process(argc, argv);

	Core *core = new Core();
	core->init();

	Render *render = new Render();
	render->init(argc, argv, core);
    
    return 1;
}
