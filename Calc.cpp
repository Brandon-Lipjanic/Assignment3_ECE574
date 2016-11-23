#include "Calc.h"

void detWidth(vector<Node*> Nodes) {
	
	for (int i = 0; i < Nodes.size(); i++) {
		Nodes.at(i)->width = Nodes.at(i)->ALAP_Time - Nodes.at(i)-> ASAP_Time;
	}

	return;
}
void detProb(vector<Node*> Nodes) {
	for (int i = 0; i < Nodes.size(); i++) {
		for (int j = 0; j < Nodes.at(i)->ALAP_Time; j++) {

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
	//adder-subtractor
	for (int i = 0; i < Nodes.at(i)->latency; i++) {
		
	}


}