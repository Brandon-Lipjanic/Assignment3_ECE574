#ifndef STATE_H
#define STATE_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <vector>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Node.h"
using namespace std;


class State {

public:

	vector<string> operationNames;
	std::string name;
	int number;
	
	State();


};

vector <State*> createStates(vector<Node*> nodes);

#endif