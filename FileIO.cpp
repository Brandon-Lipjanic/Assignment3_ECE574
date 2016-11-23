#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "FileIO.h"
using namespace std;

std::vector<string> readFile(string inp) {

	string line;
	ifstream inFile;
	inFile.open(inp.c_str());
	vector<string> v;
	
	if (inFile.is_open()){
		while (getline(inFile, line)){
			v.push_back(line);
		}
		inFile.close();
	}

	else cout << "Unable to open file";

	return v;

}

void writeFile(string outp, std::vector<string> v) {

	int i;
	string line;
	ofstream outFile(outp.c_str());
	
	if (outFile.is_open())
	{
		for (i = 0; i < v.size(); ++i) {
			outFile << v[i];
			outFile << "\n";
		}
		outFile.close();
	}

	else cout << "Unable to open file";

	return;
}
