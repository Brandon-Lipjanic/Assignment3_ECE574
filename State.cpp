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


vector <State*> createStatesNew(vector<Node*> nodes, int latency) {

	vector<State*> states;
	bool flag = false;
	int i = 0;

	State* waitState = new State();
	waitState->name = "Wait";
	waitState->number = 0;
	waitState->flag = true;
	states.push_back(waitState);

	//create all the states.
	for (i = 1; i < latency + 1; i++) {

		State* newState = new State();
		newState->name = to_string(i);
		newState->number = i;
		newState->flag = false;
		states.push_back(newState);
	}

	//populate the states with nodes
	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < states.size(); j++) {
			if (nodes.at(i)->schedule + 1 == states.at(j)->number) {
				states.at(j)->nodes.push_back(nodes.at(i));
				states.at(j)->operationNames.push_back(nodes.at(i)->operation);
			}
		}
	}


	//flag as needed if any nodes are there
	for (int i = 0; i < states.size(); i++) {
		if (states.at(i)->operationNames.size() != 0) {
			states.at(i)->flag = true;
		}
	}
	

	//flag states at needed, true is keep false is remove
	int tempMaxLatency = -1;

	for (int i = 1; i < states.size(); i++) {
		tempMaxLatency = -1;
		for (int j = 0; j < states.at(i)->nodes.size(); j++) {
			if (tempMaxLatency < states.at(i)->nodes.at(j)->operationTime) {
				tempMaxLatency = states.at(i)->nodes.at(j)->operationTime;
			}
		}

		for (int k = i + 1; k < tempMaxLatency + i; k++) {
			states.at(k)->flag = true;
		}
	}








	here:	

	for (int i = 0; i < states.size(); i++) {
		if (states.at(i)->flag == false) {
			if (i != states.size() - 1) {
				states.at(i + 1)->number = states.at(i)->number;
				if (states.at(i + 1)->name != "Final") {
					states.at(i + 1)->name = states.at(i)->name;
				}
			}
			states.erase(states.begin() + i);
			goto here;
		}
	}

	State* finalState = new State();
	finalState->name = "Final";
	finalState->flag = true;
	finalState->number = latency + 1;
	states.push_back(finalState);

	for (int i = 0; i < states.size(); i++) {
		if (states.at(i)->name == "Wait" || states.at(i)->name == "Final") {

		}
		else {
			states.at(i)->name = to_string(i);
		}
		states.at(i)->number = i;

	}

	return states;
}



