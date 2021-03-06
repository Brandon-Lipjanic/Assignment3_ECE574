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
	
	if (argc != 4) {
		return 0;
	}
	int i, j;
	vector <Node*> Nodes;
	vector<vector<double>> typeDist;

	int latency = stoi(argv[2]);

	vector<string> v, v1, modulesString, inputsString, out;
	vector<vector<string> > master, masterModules, masterInputs;
	vector<int> signs;
	vector<State*> states;
	double criticalPath = -1;




	v = readFile(argv[1]);

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



	for (int i = 0; i < nodes.size(); i++) {
		//populate available times
		for (int k = 0; k < nodes.size(); k++) {
			nodes.at(k)->availableTimes.clear();
			for (int j = nodes.at(k)->ASAP_Time; j <= nodes.at(k)->ALAP_Time; j++) {
				nodes.at(k)->availableTimes.push_back(j);
			}
		}
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
	writeFile(argv[3], out);
	return 0;
	
}