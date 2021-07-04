/*
 * Cloud of Voxels (CoV) project
 * Author: mcidclan, m [.D'O'T.] cid [.D'O'T.] clan [.A'T.] gmail [.D'O'T.] com
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
