#include "Calc.h"

void detWidth(vector<Node*> Nodes) {
	
	for (int i = 0; i < Nodes.size(); i++) {
		Nodes.at(i)->width = Nodes.at(i)->ALAP_Time - Nodes.at(i)-> ASAP_Time;
	}

	return;
}
void detProb(vector<Node*> Nodes) {
	for (int i = 0; i < Nodes.size(); i++) {
		for (int j = 0; j < Nodes.at(i)->latency; j++) {

			if (j >= Nodes.at(i)->ASAP_Time && j <= Nodes.at(i)->ALAP_Time) {
				Nodes.at(i)->probability.push_back( 1.0 / (Nodes.at(i)->width));
			}
			else {
				Nodes.at(i)->probability.push_back(0);
			}
		}
	}

}

//
vector<vector<double>> detTypeDist(vector<Node*> Nodes) {
	vector<vector<double>> typeDist;

	
	vector<double> add_sub;
	vector<double> mult;
	vector<double> logic;
	vector<double> divd_modulo;

	//initilize all of the vectors to have a zero value;
	for (int i = 0; i < Nodes.at(0)->latency; i++) {
		add_sub.at.push_back(0);
		mult.push_back(0);
		logic.push_back(0);
		divd_modulo.push_back(0);
	}

	//Look through all of the nodes
	for (int i = 0; i < Nodes.at(0)->latency; i++) {
		
		//Operation Type of 0 Means adder-subtractor
		if (Nodes.at(i)->operationType == 0) {

			for (int j = 0; j < Nodes.at(i)->latency; j++) {
				add_sub.at(i) = add_sub.at(i) + Nodes.at(i)->probability.at(i);
			}

		}

		//Operation Type of 1 Means mult
		if (Nodes.at(i)->operationType == 1) {

			for (int j = 0; j < Nodes.at(i)->latency; j++) {
				mult.at(i) = mult.at(i) + Nodes.at(i)->probability.at(i);
			}

		}

		//Operation Type of 2 Means logic
		if (Nodes.at(i)->operationType == 2) {

			for (int j = 0; j < Nodes.at(i)->latency; j++) {
				logic.at(i) = logic.at(i) + Nodes.at(i)->probability.at(i);
			}

		}

		//Operation Type of 3 Means divd_modulo
		if (Nodes.at(i)->operationType == 3) {

			for (int j = 0; j < Nodes.at(i)->latency; j++) {
				divd_modulo.at(i) = divd_modulo.at(i) + Nodes.at(i)->probability.at(i);
			}

		}
}

	typeDist.push_back(add_sub);
	typeDist.push_back(mult);
	typeDist.push_back(logic);
	typeDist.push_back(divd_modulo);

	return typeDist;

}

vector<Node*> populateNodes(vector<vector<string>> in_Vec, int latency) {

	vector<string> operators = {"+", "-", "/", "*", ">", "<", "=", "==", "?", ":", ">>", "<<", "%", "1"};
	vector<Node*> nodes;
	//Iterate through each module
	for (int i = 0; i < in_Vec.size(); i++) {
		Node* tempNode = new Node();
		tempNode->outputVar = in_Vec.at(i).at(0);
		
		
			//mult
			if (in_Vec.at(i).at(3) == "*") {
				tempNode->operationTime = 2;
				tempNode->operationType = 1;
			}
			//div mod
			else if (in_Vec.at(i).at(3) == "%" || in_Vec.at(i).at(3) == "/") {
				tempNode->operationTime = 3;
				tempNode->operationType = 3;
			}
			//add 

			else if (in_Vec.at(i).at(3) == "+" && in_Vec.at(i).at(4) != "1" && in_Vec.at(i).at(4) != "1 ") {
				tempNode->operationTime = 1;
				tempNode->operationType = 0;
			}

			//sub
			else if (in_Vec.at(i).at(3) == "-" && in_Vec.at(i).at(4) != "1" && in_Vec.at(i).at(4) != "1 ") {
				tempNode->operationTime = 1;
				tempNode->operationType = 0;
			}
			else {
				tempNode->operationTime = 1;
				tempNode->operationType = 2;
			}

			




		
		


		//Iterate through each variable in the module, skipping the first
		for (int j = 1; j < in_Vec.at(i).size(); j++) {

			//If it's a variable add it to input list
			if (find(operators.begin(), operators.end(), in_Vec.at(i).at(j)) == operators.end()) {
				tempNode->inputVars.push_back(in_Vec.at(i).at(j));
			}
		}

		//full module name

		for (int z = 0; z < in_Vec.at(i).size(); z++) {
			tempNode->operation = tempNode->operation + in_Vec.at(i).at(z);
		}

		tempNode->name = "node" + to_string(i);
		tempNode->latency = latency;
		nodes.push_back(tempNode);
	}

	//Find the Pred Nodes
	Node* tempNode2;
	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes.at(i)->inputVars.size(); j++) {
			for (int k = 0; k < nodes.size(); k++) {
				if (nodes.at(i)->inputVars.at(j) == nodes.at(k)->outputVar) {
					//check if its already in there
					if (seeIfNodeContainsPredNode(nodes.at(i), nodes.at(k)) == 0) {
						nodes.at(i)->predNodes.push_back(nodes.at(k));
					}

				}
			}

		}
	}

	//Find the Succ Nodes
	

	for (int i = 0; i < nodes.size(); i++) {
		for (int j = 0; j < nodes.size(); j++) {
			for (int k = 0; k < nodes.at(j)->inputVars.size(); k++) {
				if (nodes.at(i)->outputVar == nodes.at(j)->inputVars.at(k)) {
					//check if its already in there
					if (seeIfNodeContainsSuccNode(nodes.at(i), nodes.at(j)) == 0) {
						nodes.at(i)->succNodes.push_back(nodes.at(j));
					}
				}
			}
		}

	}
	return nodes;
}

//returns 0 if it is not in there 1 if its in there
int seeIfNodeContainsPredNode(Node* node1, Node* node2) {
	int boolVal = 0;

	for (int i = 0; i < node1->predNodes.size(); i++) {
		if (node2->name == node1->predNodes.at(i)->name) {
			boolVal = 1;
		}
	}

	return boolVal;

}

int seeIfNodeContainsSuccNode(Node* node1, Node* node2) {
	int boolVal = 0;

	for (int i = 0; i < node1->succNodes.size(); i++) {
		if (node2->name == node1->succNodes.at(i)->name) {
			boolVal = 1;
		}
	}

	return boolVal;
}