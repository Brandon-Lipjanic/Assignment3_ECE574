#include "FileIO.h"
#include <stdio.h>
#include "Translator.h"
#include "vardef.h"
#include "Node.h"
#include <stdio.h>
#include <string>
using namespace std;


int main(int argc, char* argv[]) {
	//ALAP
	//ASAP
	/*receive latency, vector(Node*)*/
	//determine_width
	//determine_probability
	//determine_type distribution
	//self_force
	//predecessor_force
	//successor_force
	//total_force
	//schedule 

//	if (argc != 4) {
//		return 0;
//	}
	int i, j;
//	int latency = stoi(argv[2]);
//	string outp = argv[3];
	vector<string> v, v1, v2, modulesString, inputsString, out;
	vector<vector<string> > master, masterModules, masterInputs;
	vector<int> signs;
	double criticalPath = -1;

	v = readFile("hls_test8.c");
	//v = readFile(argv[1]);


	for (i = 0; i < v.size(); i++) {
		if (v.at(i).find('=') != string::npos) {
			modulesString.push_back(v.at(i));
		}
		else if (v[i] != ""){
			inputsString.push_back(v.at(i));
		}
	}
	for (i = 0; i < v.size(); ++i) {
		v1 = getInputs(v[i]);
		if (v1.size() != 0)
			master.push_back(v1);
	}

	for (j = 0; j < v.size(); ++j) {
		if (v[j] != "")
			v2.push_back(v[j]);
	}

	signs = determineSign(master);
	
//	writeFile(outp, out);
}