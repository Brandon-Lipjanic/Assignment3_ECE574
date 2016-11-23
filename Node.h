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


class Node{

public:

	int ALAP_Time;
	int ASAP_Time;
	int width;
	double selfForce;
	double predForce;
	double succForce;
	double totalForce;
	int schedule;
	string operation;
	vector <double> probability;
	vector <Node*> predNodes;
	vector <Node*> succNodes;

	std::string name;

	Node(double _path, std::string _name);
	

};

#endif