#include "ForceD.h"
#define latency1 7 //FIX ME command line argument
using namespace std;

void selfForce(vector<Node*> Nodes, vector<vector<double>> typeDef) {
	int i = 0, j = 0, k = 0;
	//calculate the self force for each node
	for (i = 0; i < Nodes.size(); i++) {
		Nodes.at(i)->selfForce.clear();
		//calculate the self force for each time slot
		for (j = 0; j < Nodes.at(i)->availableTimes.size(); j++) {
			//create new self force
			Nodes.at(i)->selfForce.push_back(0);
			for (k = Nodes.at(i)->ASAP_Time; k <= Nodes.at(i)->ALAP_Time; k++) {
				//1-probability
				if (k == j + Nodes.at(i)->ASAP_Time) {
					Nodes.at(i)->selfForce.at(j) = Nodes.at(i)->selfForce.at(j) + typeDef.at(Nodes.at(i)->operationType).at(k)*(1 - Nodes.at(i)->probability.at(k));
				}
				//0-probability 
				else {
					Nodes.at(i)->selfForce.at(j) = Nodes.at(i)->selfForce.at(j) + typeDef.at(Nodes.at(i)->operationType).at(k)*(0 - Nodes.at(i)->probability.at(k));
				}
			}
			if (Nodes.at(i)->selfForce.at(j) < .000000001 && Nodes.at(i)->selfForce.at(j)> -.00000001) {
				Nodes.at(i)->selfForce.at(j) = 0;
			}
		}
	}
}


void PredForce(vector<Node*> Nodes) {
	int i = 0, j = 0, k = 0, l = 0, m = 0;
	int x = 0, find = 0;
	vector<int> UsedTime;
	vector<int> compare;
	//initialize predForces
	for (i = 0; i < Nodes.size(); i++) {//for every node
		Nodes.at(i)->predForce.clear();
		for (j = 0; j < Nodes.at(i)->availableTimes.size(); j++ ) {
			Nodes.at(i)->predForce.push_back(0);
		}
	}

	//determine predecessor force for every node
	for (i = 0; i < Nodes.size(); i++) {
		UsedTime.clear();
		// for every time slot scheduled determine which time slots are used/unavailable
		for (j = 0; j < Nodes.at(i)->availableTimes.size(); j++) { 
			////0 for adder/sub, 1 for mult, 2 for logic/logical, 3 for divider/modulo
			m = j;

			if (Nodes.at(i)->operationType == 0) {//adder subtractor 
				UsedTime.push_back(Nodes.at(i)->availableTimes.at(m));
			}
			else if (Nodes.at(i)->operationType == 1) {//multiplier
				while (m < Nodes.at(i)->availableTimes.size() && m < 2) {
					UsedTime.push_back(Nodes.at(i)->availableTimes.at(m));
					m++;
				}
			}
			else if (Nodes.at(i)->operationType == 2) {//logic
			}
			else if (Nodes.at(i)->operationType == 3) {
				while (m < Nodes.at(i)->availableTimes.size() && m < 3) { //divider modulo
					UsedTime.push_back(Nodes.at(i)->availableTimes.at(m));
					m++;
				}
			}
		}
			
		//itterate through all predecessor nodes to determine if they are forced into one slot
			for (k = 0; k < Nodes.at(i)->predNodes.size(); k++) {
				compare = Nodes.at(i)->predNodes.at(k)->availableTimes;	//make compare vector to flag times
				//flag all times which overlap with usedTime
				for (l = 0; l < Nodes.at(i)->predNodes.at(k)->availableTimes.size(); l++) {
					for (m = 0; m < UsedTime.size(); m++) {
						if (compare.at(l) == UsedTime.at(m)) {
							compare.at(l) = -1;
						}
					}
				}
				//rm all flagged
				for (m = compare.size()-1; m >= 0; m--) {
					if (compare.at(m) == -1) {
						compare.pop_back(); // delete 
						
					}
				}
				//assign predecessor force if there is only one time slot available and the width is greater than 1
				if (compare.size() == 1) {
					for (x = 0; x < Nodes.at(i)->predNodes.at(k)->availableTimes.size(); x++) {
						if (Nodes.at(i)->predNodes.at(k)->availableTimes.at(x) == compare.at(0)) {
							find = x;
						}
					}
					Nodes.at(i)->predForce.at(Nodes.at(i)->predForce.size() - 1) = Nodes.at(i)->predForce.at(Nodes.at(i)->predForce.size() - 1) + Nodes.at(i)->predNodes.at(k)->selfForce.at(find);
				}
			}
			
	}
}


void SucForce(vector<Node*> Nodes) {
	int i = 0, j = 0, k = 0, l = 0, m = 0;
	int x = 0, find = 0;
	vector<int> UsedTime;
	vector<int> compare;
	
	//initialize predForces
	for (i = 0; i < Nodes.size(); i++) {//for every node
		Nodes.at(i)->succForce.clear();
		for (j = 0; j < Nodes.at(i)->availableTimes.size(); j++) {
			Nodes.at(i)->succForce.push_back(0);
		}
	}

	//determine predecessor force for every node
	for (i = 0; i < Nodes.size(); i++) {
		UsedTime.clear();
		// for every time slot scheduled determine which time slots are used/unavailable
		for (j = 0; j < Nodes.at(i)->availableTimes.size(); j++) {
			////0 for adder/sub, 1 for mult, 2 for logic/logical, 3 for divider/modulo
			m = j;

			if (Nodes.at(i)->operationType == 0) {//adder subtractor 
				UsedTime.push_back(Nodes.at(i)->availableTimes.at(m));
			}
			else if (Nodes.at(i)->operationType == 1) {//multiplier
				while (m < Nodes.at(i)->availableTimes.size() && m < 2) {
					UsedTime.push_back(Nodes.at(i)->availableTimes.at(m));
					m++;
				}
			}
			else if (Nodes.at(i)->operationType == 2) {//logic
			}
			else if (Nodes.at(i)->operationType == 3) {
				while (m < Nodes.at(i)->availableTimes.size() && m < 3) { //divider modulo
					UsedTime.push_back(Nodes.at(i)->availableTimes.at(m));
					m++;
				}
			}
		}

		//itterate through all predecessor nodes to determine if they are forced into one slot
		for (k = 0; k < Nodes.at(i)->succNodes.size(); k++) {
			compare = Nodes.at(i)->succNodes.at(k)->availableTimes;	//make compare vector to flag times
																	//flag all times which overlap with usedTime
			for (l = 0; l < Nodes.at(i)->succNodes.at(k)->availableTimes.size(); l++) {
				for (m = 0; m < UsedTime.size(); m++) {
					if (compare.at(l) == UsedTime.at(m)) {
						compare.at(l) = -1;
					}
				}
			}
			//rm all flagged
			reverse(compare.begin(), compare.end());
			for (m = compare.size() - 1; m >= 0; m--) {
				if (compare.at(m) == -1) {
					compare.pop_back(); // delete 

				}
			}
			//assign predecessor force if there is only one time slot available and the width is greater than 1
			if (compare.size() == 1) {
				for (x = 0; x < Nodes.at(i)->succNodes.at(k)->availableTimes.size(); x++) {
					if (Nodes.at(i)->succNodes.at(k)->availableTimes.at(x) == compare.at(0)) {
						find = x;
					}
				}
				Nodes.at(i)->succForce.at(0) = Nodes.at(i)->succForce.at(0) + Nodes.at(i)->succNodes.at(k)->selfForce.at(find);
			}
		}

	}
}

void TotForce(vector<Node*> Nodes) {

	int i = 0, j = 0, k = 0;
	//calculate the self force for each node
	for (i = 0; i < Nodes.size(); i++) {
		Nodes.at(i)->totalForce.clear();
		//FIXME:DABS Should this be ALAP-ASAP
		for (j = 0; j < Nodes.at(i)->availableTimes.size(); j++) { 
			Nodes.at(i)->totalForce.push_back(Nodes.at(i)->selfForce.at(j) + Nodes.at(i)->predForce.at(j) + Nodes.at(i)->succForce.at(j));
		}
	}
}
//Look through all of the nodes and every timeslot in each node and determine the minimim total force.
//Update that node to be schedule in that timeslot
//Change the ALAP and ASAP time so that it fits the new schedule, i.e. if we choose to schedule in time 4 change ASAP = 4 and ALAP = 4
void Schedule(vector<Node*> Nodes) {
	double minTemp = 1000000;
	Node* minNode = NULL;
	int timeSlot = -1;




	//Find which node has the minimim total force and what time slot it occurs in.
	for (int i = 0; i < Nodes.size(); i++) {
		for (int j = 0; j < Nodes.at(i)->availableTimes.size(); j++) {
			if (Nodes.at(i)->totalForce.at(j) < minTemp && Nodes.at(i)->schedule == -1) {
				minTemp = Nodes.at(i)->totalForce.at(j);
				minNode = Nodes.at(i);
				timeSlot = Nodes.at(i)->availableTimes.at(j);
			}
		}
	}

	if (timeSlot != -1) {
		minNode->ALAP_Time = timeSlot;
		minNode->ASAP_Time = timeSlot;	
		minNode->schedule = timeSlot;
	}
}