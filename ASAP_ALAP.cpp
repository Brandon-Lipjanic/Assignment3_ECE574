#include <vector>
#include "Node.h"
using namespace std;

void ASAP(vector<Node*> Nodes) {
	int i, j, check = 0;
	Node* currNode = NULL;
	Node* succNode = NULL;
	for (i = 0; i < Nodes.size(); ++i) {
		currNode = Nodes.at(i);
		//set all nodes that have no predecessors to have 0 asap time, since they can be scheduled first
		if (currNode->predNodes.size() == 0) {
			currNode->ASAP_Time = 0;
		}
	}
	while (check == 0) {
		for (i = 0; i < Nodes.size(); ++i) {
			currNode = Nodes.at(i);
			//if the current node has not been assigned an ASAP time already:
			if (currNode->ASAP_Time != -1) {
				//parse through its successor nodes
				for (j = 0; j < currNode->succNodes.size(); ++j) {
					succNode = currNode->succNodes.at(j);
					//if the successor node has been scheduled already, if it had a asap time sooner than
					//what would be scheduled, replace it.
					if (succNode->ASAP_Time < currNode->ASAP_Time + currNode->operationTime) {
						succNode->ASAP_Time = currNode->ASAP_Time + currNode->operationTime;
					}
				}
			}
		}
		//checks if all the nodes have been scheduled/assigned an asap time.
		for (i = 0; i < Nodes.size(); ++i) {
			if (Nodes.at(i)->ASAP_Time == -1) {
				check = 0;
				break;
			}
			else {
				check = 1;
			}
		}
	}
	//checks if any nodes are larger or equal to the latency, then it went over and cannot be scheduled.
	for (i = 0; i < Nodes.size(); ++i) {
		if (Nodes.at(i)->ASAP_Time >= Nodes.at(i)->latency) {
			cout << "The latency is insufficient to schedule all nodes";
			exit(0);
		}
	}

	return;
}
void ALAP(vector<Node*> Nodes) {
	int i, j, check = 0;
	Node* currNode = NULL;
	Node* predNode = NULL;
	
	for (i = 0; i < Nodes.size(); ++i) {
		currNode = Nodes.at(i);
		//set all nodes that have no successors to have =latency-operationtime alap time, since they can be scheduled last
		if (currNode->succNodes.size() == 0) {
			currNode->ALAP_Time = (currNode->latency) - (currNode->operationTime);
		}
	}
	while (check == 0) {
		for (i = 0; i < Nodes.size(); ++i) {
			currNode = Nodes.at(i);
			//if the current node has not been assigned an ALAP time already:
			if (currNode->ALAP_Time != 999) {
				//parse through the predecessor nodes
				for (j = 0; j < currNode->predNodes.size(); ++j) {
					predNode = currNode->predNodes.at(j);
					//if the predecessor node has been scheduled already, if it had a alap time later than
					//what would be scheduled, replace it.
					if (predNode->ALAP_Time > ((currNode->ALAP_Time) - (predNode->operationTime))) {
						predNode->ALAP_Time = (currNode->ALAP_Time) - (predNode->operationTime);
					}
				}
			}
		}
		//checks if all the nodes have been scheduled/assigned an alap time.
		for (i = 0; i < Nodes.size(); ++i) {
			if (Nodes.at(i)->ALAP_Time == 999) {
				check = 0;
				break;
			}
			else {
				check = 1;
			}
		}
	}
	//checks if any nodes are larger or equal to the latency, then it went over and cannot be scheduled.
	for (i = 0; i < Nodes.size(); ++i) {
		if (Nodes.at(i)->ALAP_Time < 0) {
			cout << "The latency is insufficient to schedule all nodes";
			exit(0);
		}
	}

	return;
}