#pragma once
#include <vector>
#include "Node.h"
using namespace std;
//self_force
//predecessor_force
//successor_force
//total_force
//schedule 
void selfForce(vector<Node*> Nodes, vector<vector<double>> typeDef);
void PreForce(vector<Node*> Nodes, vector<vector<double>> typeDef);
void SucForce(vector<Node*> Nodes, vector<vector<double>> typeDef);
void TotForce(vector<Node*> Nodes, vector<vector<double>> typeDef);
void Schedule(vector<Node*> Nodes);