#include "Calc.h"

void detWidth(vector<Node*> Nodes) {
	
	for (int i = 0; i < Nodes.size(); i++) {
		Nodes.at(i)->width = Nodes.at(i)->ALAP_Time - Nodes.at(i)-> ASAP_Time;
	}

	return;
}
void detProb(vector<Node*> Nodes) {
	int count = 0;
	for (int i = 0; i < Nodes.size(); i++) {
		count = 0;
		for (int j = Nodes.at(i)->ALAP_Time; j < Nodes.at(i)->ALAP_Time; j++) {
			Nodes.at(i)->probability.at(count) = 1.0 / (Nodes.at(i)->width);
			count++;
		}
	}

}
vector<vector<double>> detTypeDist(vector<Node*> Nodes) {
	vector<vector<double>> typeDist;
	


}