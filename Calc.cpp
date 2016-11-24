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
				Nodes.at(i)->probability.at(j) = 1.0 / (Nodes.at(i)->width);
			}
			else {
				Nodes.at(i)->probability.at(j) = 0;
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
		add_sub.at(i) = 0;
		mult.at(i) = 0;
		logic.at(i) = 0;
		divd_modulo.at(i) = 0;
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