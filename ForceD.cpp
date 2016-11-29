#include "ForceD.h"
#define latency1 7 //FIX ME command line argument
using namespace std;

void selfForce(vector<Node*> Nodes, vector<double> typeDef) {
	int i = 0, j = 0, k = 0;
	//calculate the self force for each node
	for (i = 0; i < Nodes.size(); i++) {
		//calculate the self force for each time slot
		for (j = Nodes.at(i)->ASAP_Time; j < Nodes.at(i)->ALAP_Time; j++) {
			//create new self force
			Nodes.at(i)->selfForce.push_back(0);
			for (k = Nodes.at(i)->ASAP_Time; k < Nodes.at(i)->ALAP_Time; k++) {
				//1-probability
				if (k == j) {
					Nodes.at(i)->selfForce.at(j) = Nodes.at(i)->selfForce.at(j) + typeDef.at(k)*(1 - Nodes.at(i)->probability.at(k));
				}
				//0-probability 
				else {
					Nodes.at(i)->selfForce.at(j) = Nodes.at(i)->selfForce.at(j) + typeDef.at(k)*(0 - Nodes.at(i)->probability.at(k));
				}
			}
		}
	}
}

void PreForce(vector<Node*> Nodes, vector<double> typeDef) {//FIXME
	int i = 0, j = 0, k = 0;
	//calculate the predecessor force for each node
	for (i = 0; i < Nodes.size(); i++) {
		//calculate the self force for each time slot
		for (j = 0; j < Nodes.at(i)->selfForce.size(); j++) {
			//for each self force determine the preForce 
			for (i = Nodes.at(i)->ASAP_Time; i < Nodes.at(i)->ALAP_Time; i++) {
				//for each predecessor node
				for (k = 0; k < Nodes.at(i)->predNodes.size(); k++) {
					//create a predecessor force
					Nodes.at(i)->predForce.push_back(0);
					//determine overlap
					if (Nodes.at(i)->predNodes.at(k)->ASAP_Time >= Nodes.at(i)->ASAP_Time && Nodes.at(i)->predNodes.at(k)->ALAP_Time <= Nodes.at(i)->ALAP_Time) {
						//FIND predecessor force. Where do you assume that it is scheduled if it has a width greater than 2?
						//Nodes.at(i)->predForce.end() == Nodes.at(i)->predForce.end() + //predecessor force
					}
				}
			}
		}
	}
}

void SucForce(vector<Node*> Nodes, vector<double> typeDef) {
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

void TotForce(vector<Node*> Nodes, vector<double> typeDef) {

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