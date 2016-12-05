#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Translator.h"
#include "Node.h"
#include "vardef.h"
#include "State.h"
using namespace std;

int size = 0;
//Gets the Netlist Lines.
vector<string> getLines(string str) {

	vector<string> v;
	string delimiter = " ";
	char chars[] = ",";

	str.erase(remove(str.begin(), str.end(), chars[0]), str.end());
	
	size_t pos = 0;
	string token;
	while ((pos = str.find(delimiter)) != string::npos) {
		token = str.substr(0, pos);
		//cout << token << endl;
		str.erase(0, pos + delimiter.length());
		v.push_back(token);
	}
	if (str != "") {
		v.push_back(str);
	}

	return v;

}

vector<int> determineSign(vector<vector<string> > v) {
	int i, j, k, h, check, match;
	vector<string> temp;
	vector<string> signedVars;
	vector<int> signs;
	check = 0;
	match = 0;
	for (i = 0; i < v.size(); ++i) {
		temp = v[i];
		if (temp[0] == "input" || temp[0] == "output" || temp[0] == "wire") { //find all unsigned variables, if any
			if (temp[1] == "UInt1" || temp[1] == "UInt2" || temp[1] == "UInt4" || temp[1] == "UInt8" || temp[1] == "UInt16" || temp[1] == "UInt32" || temp[1] == "UInt64") {
				for (j = 2; j < temp.size(); ++j) {
					signedVars.push_back(temp[j]);
				}
				signs.push_back(1);
				check = 1;
			}
			else
				signs.push_back(0);
		}
		else { //if a module line, check against all unsigned variables, if any
			match = 0;
			for (k = 0; k < temp.size(); ++k) {
				for (h = 0; h < signedVars.size(); ++h) {
					if (temp[k] == signedVars[h])
						match = 1;
				}
			}
			if (match == 1)
				signs.push_back(1);
			else
				signs.push_back(0);
		}	
	}
	return signs;
}

vector<vector<string> > masterTranslate(vector<string> v) {
	int i = 0;
	vector<string> v1;
	vector<vector<string> > master;
	for (i = 0; i < v.size(); ++i) {
		v1 = getLines(v[i]);
		if (v1.size() != 0)
			master.push_back(v1);
	}

	return master;
}

vector<string> separator(vector<string> v, int flag) {
	int i = 0;
	vector<string> output;
	if (flag == 0) { //takes the spaces out of original v vector
		for (i = 0; i < v.size(); ++i) {
			if (v[i] != "")
				output.push_back(v[i]);
		}
	}
	else if (flag == 1) { //gets the module strings only
		for (i = 0; i < v.size(); i++) {
			if (v.at(i).find('=') != string::npos) {
				output.push_back(v.at(i));
			}
		}
	}
	else if (flag == 2) { //gets the input strings only
		for (i = 0; i < v.size(); i++) {
			if (v.at(i).find('=') == string::npos) {
				output.push_back(v.at(i));
			}
		}
	}
	
	return output;
}

vector<string> decipher(vector<State*> states, vector<vector<string> > v) {
	//This will be the master function for translating the nodes into strings that can be output the the file
	vector<string> master;
	vector<string> vectorTemp;
	int i, j, max, bits;
	string temp;

	//module definition
	temp = "module HLSM (Clk, Rst, Start, Done,";
	temp.append(module(v));
	master.push_back(temp);
	master.push_back("	input Clk, Rst, Start;");
	master.push_back("	output reg Done;");

	//call variable definition translation and push it into master
	vectorTemp = vardef(v);
	for (i = 0; i < vectorTemp.size(); ++i) {
		temp = "	";
		temp.append(vectorTemp.at(i));
		master.push_back(temp);
	}

	master.push_back("");
	//get bit length for state
	for (i = 0; i < states.size(); ++i) {
		if (states.at(i)->name == "Final")
			max = states.at(i)->number;
	}
	if (max <= 1)
		bits = 0;
	else if (max <= 3)
		bits = 1;
	else if (max <= 7)
		bits = 2;
	else if (max <= 15)
		bits = 3;
	else if (max <= 31)
		bits = 4;
	else if (max <= 63)
		bits = 5;

	temp = "reg[";
	temp.append(to_string(bits));
	temp.append(":0] State;");
	master.push_back(temp);
	temp = "reg[";
	temp.append(to_string(bits));
	temp.append(":0] NextState;");
	master.push_back(temp);
	master.push_back("");
	master.push_back("parameter Wait = 0;");
	temp = "			Final = ";
	temp.append(to_string(max));
	temp.append(";");
	master.push_back(temp);

	//states start here
//	for (i = 0; i < states.size(); ++i) {

//	}
	
	//Synchronous state transition always@ block
	master.push_back("always @(posedge Clk) begin");
	master.push_back("	if (Rst) State <= Wait;");
	master.push_back("	else State <= NextState;");
	master.push_back("end");

	return master;
}