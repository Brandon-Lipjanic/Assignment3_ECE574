#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Node.h"
using namespace std;
//when you create a node initilize schedule to -1;
Node::Node() {
	;
	 ALAP_Time = -1;
	 ASAP_Time = -1;
	 width = -1;
	 latency = -1;
	 schedule = -1; 
	 operationType = -1;
	 operation = "blank";
	 name = "blank";
}


