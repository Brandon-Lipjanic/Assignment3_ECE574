#include "FileIO.h"
#include <stdio.h>
#include "Translator.h"
#include "vardef.h"
#include "Node.h"
#include "Calc.h"
#include "ASAP_ALAP.h"
#include <stdio.h>
#include <string>
using namespace std;


int main(int argc, char* argv[]) {
	
//	if (argc != 4) {
//		return 0;
//	}
	int i, j;
	vector <Node*> Nodes;
	vector<double> typeDist;
//	int latency = stoi(argv[2]);
//	string outp = argv[3];
	vector<string> v, v1, modulesString, inputsString, out;
	vector<vector<string> > master, masterModules, masterInputs;
	vector<int> signs;
	double criticalPath = -1;

	v = readFile("hls_lat_test2.c");
	//v = readFile(argv[1]);

	v = separator(v, 0);
	modulesString = separator(v, 1);
	inputsString = separator(v, 2);

	master = masterTranslate(v);
	masterModules = masterTranslate(modulesString);
	masterInputs = masterTranslate(inputsString);

	vector<Node*> nodes;

	nodes = populateNodes(masterModules,10);
	ASAP(nodes);
	ALAP(nodes);

//	signs = determineSign(master);
	
//	writeFile(outp, out);


	
}