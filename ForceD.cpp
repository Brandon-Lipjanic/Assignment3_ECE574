#include "ForceD.h"
#define latency1 7 //FIX ME command line argument
using namespace std;

void selfForce(vector<Node*> Nodes, vector<vector<double>> typeDef) {
	int i = 0, j = 0, k = 0;
	//calculate the self force for each node
	for (i = 0; i < Nodes.size(); i++) {
		//calculate the self force for each time slot
		for (j = Nodes.at(i)->ASAP_Time; j <= Nodes.at(i)->ALAP_Time; j++) {
			//create new self force
			Nodes.at(i)->selfForce.push_back(0);
			for (k = Nodes.at(i)->ASAP_Time; k <= Nodes.at(i)->ALAP_Time; k++) {
				//1-probability
				if (k == j) {
					Nodes.at(i)->selfForce.at(j) = Nodes.at(i)->selfForce.at(j) + typeDef.at(Nodes.at(i)->operationType).at(k)*(1 - Nodes.at(i)->probability.at(k));
				}
				//0-probability 
				else {
					Nodes.at(i)->selfForce.at(j) = Nodes.at(i)->selfForce.at(j) + typeDef.at(Nodes.at(i)->operationType).at(k)*(0 - Nodes.at(i)->probability.at(k));
				}
			}
		}
	}
}


void PreForce(vector<Node*> Nodes) {
	int i = 0, j = 0, k = 0, l = 0, m = 0;
	vector<int> UsedTime;
	vector<int> compare;
	for (i = 0; i < Nodes.size(); i++) {//for every node
		for (j = 0; j < Nodes.at(i)->availableTimes.size(); j++) { // for every time slot scheduled determine which time slots are used/unavailable
																   ////0 for adder/sub, 1 for mult, 2 for logic/logical, 3 for divider/modulo
			Nodes.at(i)->predForce.push_back(0);
			m = j;
			UsedTime.clear();

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

			for (k = 0; k < Nodes.at(i)->predNodes.size(); k++) {//for each prenode
				compare = Nodes.at(i)->predNodes.at(k)->availableTimes;	//make compare vector to flag times
				for (l = 0; l < Nodes.at(i)->predNodes.at(k)->availableTimes.size(); l++) {//for prenode each time slot 
					for (m = 0; m < UsedTime.size() - 1; m++) {
						if (compare.at(l) == UsedTime.at(m)) {
							compare.at(l) = -1;
						}
					}
				}

			}
			//rm all flagged
			for (m = compare.size() - 1; m >= 0; m++) {
				if (compare.at(m) == -1) {
					compare.erase(compare.end() - (compare.size() - m)); // delete 
				}
			}
			//assign predecessor force if there is only one time slot available and the width is greater than 1
			if (compare.size() == 1 && Nodes.at(i)->predNodes.at(k)->availableTimes.size() != 1) {
				Nodes.at(i)->predForce.end() = Nodes.at(i)->predForce.end() + Nodes.at(i)->predNodes.at(k)->selfForce.at(0);
			}
		}
	}
}


void SucForce(vector<Node*> Nodes) {
	int i = 0, j = 0, k = 0;
	//calculate the self force for each node
	for (i = 0; i < Nodes.size(); i++) {
		//for each time slot 
		for (j = Nodes.at(i)->ASAP_Time; j < Nodes.at(i)->ALAP_Time; j++) {
			//determine overlap for each succsessor node
			for (k = 0; k < Nodes.at(i)->succNodes.size(); k++) {
				//create a predecessor force
				Nodes.at(i)->succForce.push_back(0);
				//determine overlap
				if (Nodes.at(i)->succNodes.at(k)->ASAP_Time >= Nodes.at(i)->ASAP_Time && Nodes.at(i)->succNodes.at(k)->ALAP_Time <= Nodes.at(i)->ALAP_Time) {
					//FIND successor force. Where do you assume that it is scheduled if it has a width greater than 2?
					//Nodes.at(i)->succForce.end() == Nodes.at(i)->succForce.end() + //successor force
				}
			}
		}
	}
}

void TotForce(vector<Node*> Nodes) {
	int i = 0, j = 0, k = 0;
	//calculate the self force for each node
	for (i = 0; i < Nodes.size(); i++) {
		//FIXME:DABS Should this be ALAP-ASAP
		for (j = 0; j < Nodes.at(i)->ASAP_Time - Nodes.at(i)->ALAP_Time + 1; j++) { 
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
		for (int j = 0; j < Nodes.at(i)->latency; j++) {
			if (Nodes.at(i)->totalForce.at(j) < minTemp && Nodes.at(i)->schedule == -1) {
				minTemp = Nodes.at(i)->totalForce.at(j);
				minNode = Nodes.at(i);
				timeSlot = j;
			}
		}
	}

	if (timeSlot != -1) {
		minNode->ALAP_Time = timeSlot;
		minNode->ASAP_Time = timeSlot;	
		minNode->schedule = timeSlot;
	}
}