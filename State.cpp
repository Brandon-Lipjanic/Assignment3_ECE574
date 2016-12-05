#include <string>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <vector>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "State.h"
using namespace std;






State::State() {
	name = "";
	number = -1;
}


vector <State*> createStates(vector<Node*> nodes) {

	vector<State*> states;
	bool flag = false;


	for (int i = 0; i < nodes.size(); i++) {

		for (int j = 0; j < states.size(); j++) {
			
			if (nodes.at(i)->schedule == states.at(j)->number) {
				flag = true;
				states.at(j)->operationNames.push_back(nodes.at(i)->operation);
			}

		}

		if (flag == false) {
			State* newState = new State();
			newState->name = to_string(nodes.at(i)->schedule);
			newState->number = nodes.at(i)->schedule;
			newState->operationNames.push_back(nodes.at(i)->operation);
			states.push_back(newState);
		}
		flag = false;
	}
	return states;
}

