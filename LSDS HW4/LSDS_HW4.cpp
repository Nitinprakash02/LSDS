// LSDS_HW4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <math.h>
#include "Queries_NW.h"
#include "Queries_BL.h"
using namespace std;

int main(int argc, char* argv[])
{
	cout << "LSDS HW4\n";

	//Variable declaration
	bool test = false;
	long long int fragmentLength = 16;
	
	//Collecting data from cmd
	string humenGenomesfilePath = (test) ? "C:\\Users\\np679\\Downloads\\human.txt" : argv[1];
	string fragmentFilePath = (test) ? "C:\\Users\\np679\\Downloads\\human_reads_trimmed.fa" : argv[2];
	long long int maxSearchValue = (test) ? 10 : atoi(argv[3]);
	int maxTolerance = (test) ? 2 : atoi(argv[4]);


	if (atoi(argv[5]) == 1) {
		//Read HumanGenomes Data
		Queries_NW queriesNW = Queries_NW(maxSearchValue, humenGenomesfilePath, fragmentFilePath, maxTolerance);
		queriesNW.GetTheLengthOfHumenGenome();
		queriesNW.readHumanGenomes();

		//Read Fragments Data
		queriesNW.GetTheLengthOfFragments();
		queriesNW.readFragmentData();

		//File content details
		cout << "Total number of scaffolds:" << queriesNW.totalNoOfScaffold << endl;
		cout << "Total number of Fragments: " << queriesNW.totalNoOfFragments << endl;
		cout << "Total number of Human Genome: " << queriesNW.totalLengthOfhumenGenome << endl;


		//Problem 1 || for both part: 0 || Part A:1 || Part B:2
		if (atoi(argv[6]) == 0) {
			queriesNW.checkRandomFragmentFromSubject();
			queriesNW.createAndSearchRandomFuzzyFragment();
		}
		else if (atoi(argv[6]) == 1) {
			queriesNW.checkRandomFragmentFromSubject();
		}
		else {
			queriesNW.createAndSearchRandomFuzzyFragment();
		}
	}
	
	if (atoi(argv[7]) == 1) {
		//Read HumanGenomes Data
		Queries_BL queriesBL = Queries_BL(humenGenomesfilePath, fragmentFilePath, maxTolerance);
		queriesBL.GetTheLengthOfHumenGenome();
		queriesBL.readHumanGenomes();
		cout << "Scaffold Read done" << endl;

		//Read Fragments Data
		queriesBL.GetTheLengthOfFragments();
		cout << "Total number of Fragments: " << queriesBL.totalNoOfFragments << endl;
		
		queriesBL.readFragmentData();
		cout << "Fragment Read done" << endl;
    
		//File content details
		cout << "Total number of scaffolds:" << queriesBL.totalNoOfScaffold << endl;
		cout << "Total number of Fragments: " << queriesBL.totalNoOfFragments << endl;
		cout << "Total number of Human Genome: " << queriesBL.totalLengthOfhumenGenome << endl;


		//Problem 1 || for both part: 0 || Part A:1 || Part B:2
		
		queriesBL.checkRandomFragmentFromSubject(atoi(argv[8]));
	}


}
