#include "ForceD.h"

using namespace std;

void selfForce(vector<Node*> Nodes) {

}

void PreForce(vector<Node*> Nodes) {

}

void SucForce(vector<Node*> Nodes) {

}

void TotForce(vector<Node*> Nodes) {

}

//Look through all of the nodes and every timeslot in each node and determine the minimim total force.
//Update that node to be schedule in that timeslot
//Change the ALAP and ASAP time so that it fits the new schedule, i.e. if we choose to schedule in time 4 change ASAP = 4 and ALAP = 4
void Schedule(vector<Node*> Nodes){
	double minTemp = 1000000;
	Node* minNode = NULL;
	int timeSlot = -1;




	//Find which node has the minimim total force and what time slot it occurs in.
	for (int i = 0; i < Nodes.size(); i++) {
		for (int j = 0; j < Nodes.at(i)->latency; j++) {
			if (Nodes.at(i)->totalForce.at(j) < minTemp) {
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

	return;


}