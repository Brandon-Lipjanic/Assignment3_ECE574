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
	double selfForce;
	double predForce;
	double succForce;
	double totalForce;
	int schedule;
	int operationType;   //1 for adder/sub, 2 for mult, 3 for logic/logical, 4 for divider/modulo
	string operation;
	vector <double> probability;
	vector <Node*> predNodes;
	vector <Node*> succNodes;

	std::string name;

	Node(double _path, std::string _name);
	

};

#endif