#pragma once
#include <vector>
#include "Node.h"
using namespace std;
//self_force
//predecessor_force
//successor_force
//total_force
//schedule 
void selfForce(vector<Node*> Nodes);
void PreForce(vector<Node*> Nodes);
void SucForce(vector<Node*> Nodes);
void TotForce(vector<Node*> Nodes);
void Schedule(vector<Node*> Nodes);