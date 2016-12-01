#pragma once
#include <vector>
#include <algorithm>
#include "Node.h"
using namespace std;
//determine_width
//determine_probability
//determine_type distribution
void detWidth(vector<Node*> Nodes);
void detProb(vector<Node*> Nodes);
int seeIfNodeContainsPredNode(Node* node1, Node* node2);
int seeIfNodeContainsSuccNode(Node* node1, Node* node2);
vector<vector<double>> detTypeDist(vector<Node*> Nodes);