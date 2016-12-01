#ifndef NODE_H
#define NODE_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <vector>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;


class Node{

public:

	int ALAP_Time;
	int ASAP_Time;
	int width;
	int latency; //Latency from the command line arg.

	//I've updated all of these to be vectors because force changes with time slot, so there will be a force assuming the node is schedule in each time slot.
	vector<double> selfForce;
	vector<double> predForce;
	vector<double> succForce;
	vector<double> totalForce;
	int schedule;
	int operationType;   //0 for adder/sub, 1 for mult, 2 for logic/logical, 3 for divider/modulo
	string operation;
	vector <double> probability;
	vector <Node*> predNodes;
	vector <Node*> succNodes;
	vector<string> inputVars;
	string outputVar;

	std::string name;

	Node();
	

};

#endif