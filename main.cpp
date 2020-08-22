/*
 * Cloud of voxels (COV) project
 * Author: mcidclan, m.cid.clan@gmail.com
 * Project date: 2011
 * File creation date: 2020
 */

#include "./headers/Core.h"
#include <map>

using namespace std;

/*
 * main
 */
int main(int argc, char **argv)
{
    int i = 1;
    map<string, bool> options;
    while(i < argc) {
        options[argv[i]] = true;
        i++;
    }
    
    Options::nologs = options.find("nologs") != options.end();
    Options::nomotion = options.find("nomotion") != options.end();
    Options::noneighbour = options.find("noneighbour") != options.end();
    
	Core *core = new Core();
	core->init();

	Render *render = new Render();
	render->setCore(core);
	render->init(argc, argv);
    
    return 1;
}
