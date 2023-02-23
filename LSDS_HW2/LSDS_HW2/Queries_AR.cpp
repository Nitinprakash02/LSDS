#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

#include "Queries_AR.h"

Queries_AR::Queries_AR() {

	QueriesFilePath = "";

}

Queries_AR::Queries_AR(string fPath) {

	QueriesFilePath = fPath;
}

bool Queries_AR:: GetTheLengthOfFragments() {

	string line = "";
	string frag = ">Fragment";

	ifstream file(QueriesFilePath);

	if (!file.is_open()) {
		cout << "Invaild File";
		return -1;
	}

	while (getline(file, line)) {

		// Check if the string starts with the ">Fragment"
		if (line.compare(0, frag.length(), frag) == 0) {
			totalNoOfFragments++;
		}
		if (line.compare(0, frag.length(), frag) != 0 && line.compare("") != 0) {
			//counting each line data into fragmentFileLength
			fragmentFileLength += line.length();

		}

	}
	file.close();
	return 0;

}

bool Queries_AR::ReadQuery() {

	string line = "";
	string frag = ">Fragment";
	long long int i = 0;
	int	j = 0;

	fragQueries = new char* [totalNoOfFragments];
	for (int i = 0; i < totalNoOfFragments; i++) {
		fragQueries[i] = new char[fragLength];
	}

	ifstream file(QueriesFilePath);

	if (!file.is_open()) {
		cout << "Invaild File";
		return -1;
	}

	while (getline(file, line)) {

		if (line.compare(0, frag.length(), frag) != 0 && line.compare("") != 0) {

			for (j = 0; j < line.length(); j++) {

				fragQueries[i][j] = line[j];
			}
			i++;
		}

	}

	//Closing the file instance after reading the file data
	file.close();
	return 0;
}

void Queries_AR:: insertionSort() {

	long long int i = 0;
	long long int k = 0;
	
	
	for (i = 1; i < totalNoOfFragments; i++) {

		char* key = fragQueries[i];
		int j = i - 1;
		bool greterChar = false;
		bool lesserChar = false;
		bool equalChar = false;
		bool sValue = false;
		while (j >= 0) {

			int frag = 0;
			
			for (k = 0; k < fragLength; k++) {

				if (fragQueries[j][k] > key[k]) {

					sValue = true;
					//cout<<"\n"<< fragQueries[j][k] << " greter " << key[k];
					greterChar = true;
					break;
				}
				else if (fragQueries[j][k] < key[k]) {

					lesserChar = true;
					break;
				}
				else {
					frag++;
				}
			}
			if (greterChar == true) {
				fragQueries[j + 1] = fragQueries[j];
				greterChar = false;
			}
			if (lesserChar == true) {
				lesserChar = false;
				break;
			}
			j--;

		}
		greterChar = false;
		lesserChar = false;
		equalChar = false;

	if (sValue == true) {
		fragQueries[j + 1] = key;
	}

	}

}


Queries_AR::~Queries_AR() {
}

