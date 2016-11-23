#pragma once
#include <vector>
#include "Node.h"
using namespace std;
//determine_width
//determine_probability
//determine_type distribution
void detWidth(vector<Node*> Nodes);
void detProb(vector<Node*> Nodes);
vector<vector<double>> detTypeDist(vector<Node*> Nodes);