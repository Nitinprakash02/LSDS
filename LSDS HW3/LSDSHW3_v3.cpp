// LSDSHW3_v3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <math.h>
#include "Queries_HT.h"
using namespace std;

int main(int argc, char* argv[])
{
	cout << "LSDS HW3\n";
	bool test = false;
	long long int fragmentLength = 16;
	//const long long int m[] = { 1000000, 10000000, 30000000, 60000000 }; // hash table sizes
	/*if (atoi(argv[3]) == 0 || atoi(argv[3]) == 1) {

	}
	if (atoi(argv[3]) == 0 || atoi(argv[3]) == 2) {
	}
	int mSize = sizeof(m) / sizeof(m[0]);*/

	//Humen genomes file path
	string humenGenomesfilePath = (test) ? "C:\\Users\\np679\\Downloads\\human.txt" : argv[1];
	string fragmentFilePath = (test) ? "C:\\Users\\np679\\Downloads\\human_reads_trimmed.fa" : argv[2];
	long long int mValue = (test) ? 10 : atoi(argv[3]);
	Queries_HT queriesHt = Queries_HT(humenGenomesfilePath, fragmentFilePath, mValue, fragmentLength);
	queriesHt.GetTheLengthOfHumenGenome();
	queriesHt.readHumengenomes();
	queriesHt.GetTheLengthOfFragments();
	queriesHt.readFragmentData();

	//Fragment file path
	cout << "Total number of Fragments: " << queriesHt.totalNoOfFragments << endl;
	cout << "Total number of Human Genome: " << queriesHt.totalLengthOfhumenGenome << endl;

	if (atoi(argv[4]) == 1) {
		queriesHt.runMyHW();
	}
	else {
		queriesHt.runMyHW1();
	}
	

	//queriesHt.runMyHW(atoi(argv[3]), totalNoOfFragments, queryAR.fragQueries, totalLengthOfhumenGenome, humenGenome, atoi(argv[4]));

}
