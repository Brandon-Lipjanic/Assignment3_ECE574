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
		
		//Operation Type of 1 Means adder-subtractor
		if (Nodes.at(i)->operationType == 1) {

			for (int j = 0; j < Nodes.at(i)->latency; j++) {
				add_sub.at(i) = add_sub.at(i) + Nodes.at(i)->probability.at(i);
			}

		}

		//Operation Type of 2 Means adder-subtractor
		if (Nodes.at(i)->operationType == 1) {

			for (int j = 0; j < Nodes.at(i)->latency; j++) {
				add_sub.at(i) = add_sub.at(i) + Nodes.at(i)->probability.at(i);
			}

		}

		//Operation Type of 1 Means adder-subtractor
		if (Nodes.at(i)->operationType == 1) {

			for (int j = 0; j < Nodes.at(i)->latency; j++) {
				add_sub.at(i) = add_sub.at(i) + Nodes.at(i)->probability.at(i);
			}

		}

		//Operation Type of 1 Means adder-subtractor
		if (Nodes.at(i)->operationType == 1) {

			for (int j = 0; j < Nodes.at(i)->latency; j++) {
				add_sub.at(i) = add_sub.at(i) + Nodes.at(i)->probability.at(i);
			}

		}

		

	}


}