#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Translator.h"
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

