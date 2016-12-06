#include "FileIO.h"
#include <stdio.h>
#include "Translator.h"
#include "vardef.h"
#include "ForceD.h"
#include "Node.h"
#include "Calc.h"
#include "ASAP_ALAP.h"
#include "State.h"
#include <stdio.h>
#include <string>
using namespace std;


int main(int argc, char* argv[]) {
	
//	if (argc != 4) {
//		return 0;
//	}
	int i, j;
	vector <Node*> Nodes;
	vector<vector<double>> typeDist;
	
//	int latency = stoi(argv[2]);
//	string outp = argv[3];
	vector<string> v, v1, modulesString, inputsString, out;
	vector<vector<string> > master, masterModules, masterInputs;
	vector<int> signs;
	vector<State*> states;
	double criticalPath = -1;
	int latency = 10;

	v = readFile("hls_test2.c");
	//v = readFile(argv[1]);

	v = separator(v, 0);
	modulesString = separator(v, 1);
	inputsString = separator(v, 2);

	master = masterTranslate(v);
	masterModules = masterTranslate(modulesString);
	masterInputs = masterTranslate(inputsString);

	vector<Node*> nodes;

	nodes = populateNodes(masterModules,latency);

	ASAP(nodes);
	ALAP(nodes);

	//populate available times
	for (int i = 0; i < nodes.size(); i++) {
		for (int j = nodes.at(i)->ASAP_Time; j <= nodes.at(i)->ALAP_Time; j++) {
			nodes.at(i)->availableTimes.push_back(j);
		}
	}

	for (int i = 0; i < nodes.size(); i++) {
		detWidth(nodes);
		detProb(nodes);
		typeDist = detTypeDist(nodes);
			selfForce(nodes, typeDist);
			PredForce(nodes);
			SucForce(nodes);
			TotForce(nodes);
			Schedule(nodes);

	}



	states = createStatesNew(nodes,latency);
	out = decipher(states, master);
	writeFile("output.txt", out);
	return 0;
	
}