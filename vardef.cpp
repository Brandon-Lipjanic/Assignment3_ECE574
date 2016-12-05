#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "vardef.h"

using namespace std;

vector<string> vardef(vector<vector<string> > master) {
	unsigned int i = 0;
	unsigned int k = 0;//DELETEME
	int var = 0;
	int n_int;
	string n_string;
	vector<vector<string>> inputs;	//vector of input variables
	vector<vector<string>>  outputs;	//vector of output variabels
	vector<vector<string>>  wires;	//vector of wire variabels
	vector<vector<string>>  registers;	//vector of wire variabels
	vector<string> out;
	int x = 0;
	//seperate vector into input strings and output strings

	while (i != master.size() - 1) {
		var = 0;
		//check if variable def
		if (master.at(i).at(0).compare("input") == 0 || master.at(i).at(0).compare("output") == 0 || master.at(i).at(0).compare("register") == 0 || master.at(i).at(0).compare("wire") == 0 || master.at(i).at(0).compare("variable") == 0) {
			var = 1;
			if (master.at(i).at(0).compare("register") == 0) {
				out.push_back("reg");
			}
			else {
				out.push_back(master.at(i).at(0));
			}
		}
		if (var == 1) {
			if (master.at(i).at(1).at(0) == 'U') {

				/*out.at(i).append(" int [");*/
				out.at(i).append(" [");
				master.at(i).at(1).erase(0, 4);

			}
			else {
				/*
				out.at(i).append(" uint [");*/
				out.at(i).append(" [");
				master.at(i).at(1).erase(0, 3);
			}
			//else if (master.at(i).at(1).find("int") == std::string::npos) {
			//	/*
			//	out.at(i).append(" uint [");*/
			//	out.at(i).append(" [");
			//	master.at(i).at(1).erase(0, 3);
			//}
			//add data width
			n_string = master.at(i).at(1);
			n_int = stoi(n_string);
			n_int = n_int - 1;
			n_string = std::to_string(n_int);

			out.at(i).append(n_string);
			out.at(i).append(":0] ");

			k = 2;
			while (k < master.at(i).size())
			{
				out.at(i).append(master.at(i).at(k));
				if (k != (master.at(i).size() - 1)) {

					out.at(i).append(", ");
				}
				else {
					out.at(i).append(";");
				}
				k++;
			}
		}
		i++;
	}
	return out;
}

string module(vector<vector<string> > master) {
	string output;
	int i = 0;
	int j = 0;
	while (i < master.size()) {
		if (master.at(i).at(0).compare("input") == 0 || master.at(i).at(0).compare("output") == 0) {
			for (j = 2; j < master.at(i).size(); j++) {

				output.append(" " + master.at(i).at(j) + ",");
			}
		}
		i++;
	}
	output.erase(output.size() - 1);
	output.append(");");
	return output;
}