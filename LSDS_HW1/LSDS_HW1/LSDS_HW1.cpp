// LSDS_HW1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct charCount {
	char charName;
	int count;
};

struct scaffolds {
	string scaffoldsName;
	int scaffoldsLength;
};

string getDataFromFile(string filePathn) {

	//Variable initializations
	string filePath = filePathn;
	string k = "";
	string line = "";
	//Making the instance of file path
	ifstream file(filePath);
	//Checking whether file is open or not
	/*if (file.good() == 0) {
		fileData = "File not found!";
	}
	else */
	if (file.is_open()==true)
	{
		//Reading file data line by line
		while (getline(file, line)) {
			//appending each line data into fileData with newline
			//fileData += line +"\n";
		}
		//Closing the file instance after reading the file data
		//file.close();
	}
	else
	{
		//If our program is unable to open the file than our program will set the fileData as "Unable to open file"
		//fileData = "Unable to open file";
	}
	file.close();
	return k;
}

int main(int argc, char* argv[]) {

	//Variable initializations
	//string filePath = argv[1];
	string filePath = "C:/Users/np679/Downloads/human.txt";
	/*scaffolds* sfoldData = new scaffolds[0];
	int i = 0, scaffoldsCount=0;
	int maxScaffoldsLength = 0, minScaffoldsLength = 0;
	string maxScaffoldsName = "", minScaffoldsName = "";*/
	//Colecting data from filepath
	string fileDataKl = getDataFromFile(filePath);
	return 0;
}

