#include <vector>
#include "Node.h"
using namespace std;

void ASAP(vector<Node*> Nodes) {
	int i, j, check = 0;
	Node* currNode = NULL;
	Node* succNode = NULL;
	for (i = 0; i < Nodes.size(); ++i) {
		currNode = Nodes.at(i);
		if (currNode->predNodes.size() == 0) {
			currNode->ASAP_Time = 0;
		}
	}
	while (check == 0) {
		for (i = 0; i < Nodes.size(); ++i) {
			currNode = Nodes.at(i);
			if (currNode->ASAP_Time != -1) {
				for (j = 0; j < currNode->succNodes.size(); ++j) {
					succNode = currNode->succNodes.at(j);
					if (succNode->ASAP_Time < currNode->ASAP_Time + currNode->operationTime) {
						succNode->ASAP_Time = currNode->ASAP_Time + currNode->operationTime;
					}
				}
			}
		}

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
		if (currNode->succNodes.size() == 0) {
			currNode->ALAP_Time = (currNode->latency) - (currNode->operationType);
		}
	}
	while (check == 0) {
		for (i = 0; i < Nodes.size(); ++i) {
			currNode = Nodes.at(i);
			if (currNode->ALAP_Time != 999) {
				for (j = 0; j < currNode->predNodes.size(); ++j) {
					predNode = currNode->predNodes.at(j);
					if (predNode->ALAP_Time > ((currNode->ALAP_Time) - (currNode->operationTime))) {
						predNode->ALAP_Time = (currNode->ALAP_Time) - (currNode->operationTime);
					}
				}
			}
		}

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

	for (i = 0; i < Nodes.size(); ++i) {
		if (Nodes.at(i)->ALAP_Time < 0) {
			cout << "The latency is insufficient to schedule all nodes";
			exit(0);
		}
	}

	return;
}