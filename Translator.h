#include <stdio.h>
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

vector<string> getLines(string str);
vector<int> determineSign(vector<vector<string> > v);
vector<vector<string> > masterTranslate(vector<string> v);
vector<string> separator(vector<string> v, int flag);
vector<string> decipher(vector<Node*> nodes, vector<vector<string> > v);