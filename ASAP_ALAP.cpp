#include <vector>
#include "Node.h"
using namespace std;

void ASAP(vector<Node*> Nodes) {
	int i, j, count1, count2, count3 = 0;
	Node* currNode = NULL;
	Node* predNode = NULL;
	for (i = 0; Nodes.size(); ++i) {
		currNode = Nodes.at(i);
		currNode->ASAP_Time = 0;
		//Trace back up the tree to see how many nodes are above it
		while (currNode->predNodes.at(0) != NULL) {
			predNode = currNode->predNodes.at(0);
			++count1;
		}
		currNode->ASAP_Time = count1;
	}

	return;
}
void ALAP(vector<Node*> Nodes) {
	int i, j, count;
	Node* currNode = NULL;
	Node* succNode = NULL;
	count = 0;
	for (i = 0; Nodes.size(); ++i) {
		currNode = Nodes.at(i);
		currNode->ALAP_Time = 0;
		while (currNode->succNodes.at(0) != NULL) {
			succNode = currNode->succNodes.at(0);
			++count;
		}
		currNode->ALAP_Time = count;
	}

	return;
}