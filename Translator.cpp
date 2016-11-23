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
vector<string> getInputs(string str) {

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

vector<int> determinewidth(vector<vector<string> > v ) {

	int i = 0;
	int k = 0;
	int x = 0; //variable for creating vardef vector
	int y = 0;
	int found = 0;
	int temp;
	vector<int> width;
	vector<int> temp_width;
	vector<vector<string>> vd;
	int DELETEME = 0;
	vd = v;
	
		
		//delete all non variable definition statements from vd. vd becomes a separated variable definition vector
		for (x = vd.size()-1; x >= 0; x--) {
			if (vd.at(x).at(0).compare("input") != 0 && vd.at(x).at(0).compare("output") != 0 && vd.at(x).at(0).compare("register") != 0 && vd.at(x).at(0).compare("wire") != 0) {
				vd.pop_back();
			}
			//if (vd.at(x).at(0) == "input" || vd.at(x).at(0) == "output" || vd.at(x).at(0) == "wire" || vd.at(x).at(0) == "register") {
			//	//erase the rest of it 
			//	vd.pop_back();
			//}
		}
			
		for (x = 0; x < vd.size(); x++) {//extract number from vd.at(i).at(1)
			if (vd.at(x).at(1).at(0) == 'U') {
				vd.at(x).at(1).erase(0, 4);
			}
			else {
				vd.at(x).at(1).erase(0, 3);
			}
			/*else if (vd.at(x).at(1).find("int") == std::string::npos) {
				vd.at(x).at(1).erase(0, 3);
			}*/
		}
		
		for (i = 0; i < v.size(); ++i) {
			//look at v to determine if line 
			if (v.at(i).at(0) == "input" || v.at(i).at(0) == "output" || v.at(i).at(0) == "wire" || v.at(i).at(0) == "register" || v.at(i).at(0) == "") {}//do nothing
			else {
				//determine if compare module
				for (y = 0; y < v.at(i).size(); y++) {
					if (v.at(i).at(y).compare(">") == 0 || v.at(i).at(y).compare("<") == 0 || v.at(i).at(y).compare("==") == 0) {
						found = 1;
					}
				}
				if (found == 1) {//if line is a comparator 
					found = 0;
					for (x = 0; x < vd.size(); x++) {
						for (y = 0; y < vd.at(x).size(); y++) {
							if (vd.at(x).at(y).compare(v.at(i).at(2)) == 0 ) { //find variables located locations 3 and 5
								temp = stoi(vd.at(x).at(1));																							//add to temp for compare
								temp_width.push_back(temp);	//how to make vd.at(x).at(1) an int instead of string
							}
							if (vd.at(x).at(y).compare(v.at(i).at(4)) == 0) {
								temp = stoi(vd.at(x).at(1));																							//add to temp for compare
								temp_width.push_back(temp);	//how to make vd.at(x).at(1) an int instead of string
							}
						}
					}
					if (temp_width.at(0) > temp_width.at(1)) {
						width.push_back(temp_width.at(0));
					}
					else {
						width.push_back(temp_width.at(1));
					}
				}
				else {//size of output
					//search vd for variable
					for (x = 0; x < vd.size(); x++) {
						for (y = 0; y < vd.at(x).size(); y++) {
							if (vd.at(x).at(y).compare(v.at(i).at(0)) == 0) {
								temp = stoi(vd.at(x).at(1));
								width.push_back(temp);
							}
						}
					}
				}

			}
		}
	return width;
}
