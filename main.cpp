/*
 * Cloud of Voxels (CoV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Creation Date: 2020
 * Modification Date: 2020
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
