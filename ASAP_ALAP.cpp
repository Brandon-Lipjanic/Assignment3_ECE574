#include <vector>
#include "Node.h"
using namespace std;

void ASAP(vector<Node*> Nodes) {
	int i, j, check = 0;
	Node* currNode = NULL;
	Node* succNode = NULL;
	for (i = 0; Nodes.size(); ++i) {
		currNode = Nodes.at(i);
		if (currNode->predNodes.size() == 0) {
			currNode->ASAP_Time = 0;
		}
	}
	while (check == 0) {
		for (i = 0; Nodes.size(); ++i) {
			currNode = Nodes.at(i);
			if (currNode->ASAP_Time != NULL) {
				for (j = 0; currNode->succNodes.size(); ++j) {
					succNode = currNode->succNodes.at(j);
					succNode->ASAP_Time = currNode->ASAP_Time + currNode->operationType;
				}
			}
		}

		for (i = 0; Nodes.size(); ++i) {
			if (Nodes.at(i)->ASAP_Time == NULL) {
				check = 0;
				break;
			}
			else {
				check = 1;
			}
		}
	}

	return;
}
void ALAP(vector<Node*> Nodes) {
	int i, j, check;
	Node* currNode = NULL;
	Node* predNode = NULL;
	
	for (i = 0; Nodes.size(); ++i) {
		currNode = Nodes.at(i);
		if (currNode->succNodes.size() == 0) {
			currNode->ALAP_Time = currNode->latency-1;
		}
	}
	while (check == 0) {
		for (i = 0; Nodes.size(); ++i) {
			currNode = Nodes.at(i);
			if (currNode->ALAP_Time != NULL) {
				for (j = 0; currNode->predNodes.size(); ++j) {
					predNode = currNode->predNodes.at(j);
					predNode->ALAP_Time = currNode->ALAP_Time - currNode->operationType;
				}
			}
		}

		for (i = 0; Nodes.size(); ++i) {
			if (Nodes.at(i)->ALAP_Time == NULL) {
				check = 0;
				break;
			}
			else {
				check = 1;
			}
		}
	}

	return;
}