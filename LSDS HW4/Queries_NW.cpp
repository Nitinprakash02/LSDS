#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "Queries_NW.h"
#include <random>
#include <algorithm>

using namespace std;



Queries_NW::Queries_NW(int MaxQueryFind, string HumenGenomesfilePath, string FragmentFilePath, int ToleranceLevel)
{

	humenGenome = NULL;

	fragQueries = NULL;

	maxQueryFind = MaxQueryFind;

	humenGenomesfilePath = HumenGenomesfilePath;

	fragmentFilePath = FragmentFilePath;

	toleranceLevel = ToleranceLevel;


}

Queries_NW::Queries_NW() {

	humenGenome = NULL;

	fragQueries = NULL;

	maxQueryFind = 0;

	humenGenomesfilePath = "";

	fragmentFilePath = "";

	toleranceLevel = 2;

}
bool Queries_NW::GetTheLengthOfHumenGenome() {

	//Getting the length of Humen Genome 
	string line = "";
	string header = ">";

	ifstream file(humenGenomesfilePath);

	if (!file.is_open()) {
		cout << "Invaild File";
		return false;
	}

	while (getline(file, line)) {

		// Check if the string starts with the ">Fragment"
		if (line.compare(0, header.length(), header) == 0) {
			totalNoOfScaffold++;
		}
		if (line.compare(0, header.length(), header) != 0 && line.compare("") != 0) {
			//counting each line data into totalLengthOfInputfile
			totalLengthOfhumenGenome += line.length();

		}

	}
	file.close();
	return true;
}

bool Queries_NW::readHumanGenomes() {

	//Reading the human Genomes data
	string line = "";
	string header = ">";
	long long int i = 0;
	int	j = 0;

	//Creating the humenGenome char array
	humenGenome = new char[totalLengthOfhumenGenome];

	ifstream file(humenGenomesfilePath);

	if (!file.is_open()) {
		cout << "Invaild File";
		return false;
	}

	while (getline(file, line)) {
		//Checking if line does not contain header or empty data
		if (line.compare(0, header.length(), header) != 0 && line.compare("") != 0) {

			for (j = 0; j < line.length(); j++) {
				//storing the humen genomes data
				humenGenome[i] = line[j];
				i++;
			}

		}

	}

	//Closing the file instance after reading the file data
	file.close();
	return true;
}

bool Queries_NW::GetTheLengthOfFragments() {

	string line = "";
	string frag = ">Fragment";
	//opening the file 
	ifstream file(fragmentFilePath);

	if (!file.is_open()) {
		cout << "Invaild File";
		return false;
	}
	//taking the total number of the framents
	while (getline(file, line)) {

		// Check if the string starts with the ">Fragment"
		if (line.compare(0, frag.length(), frag) == 0) {
			totalNoOfFragments++;
		}
		/*if (line.compare(0, frag.length(), frag) != 0 ) {
			//counting each line data into fragmentFileLength
			fragmentFileLength += line.length();

		}*/

	}
	//closing the file
	file.close();
	return true;

}

//Reading data from fragment file
bool Queries_NW::readFragmentData() {

	string line = "";
	string frag = ">Fragment";
	long long int i = 0;
	int	j = 0;
	//Creating the fragQueries 2d array
	fragQueries = new char* [totalNoOfFragments];
	for (long long int i = 0; i < totalNoOfFragments; i++) {
		fragQueries[i] = new char[fragLength + 1];
		//fragQueries[i]=nullptr;
	}

	ifstream file(fragmentFilePath);

	if (!file.is_open()) {
		cout << "Invaild File";
		return false;
	}
	// Reading the fragments 
	while (getline(file, line)) {

		if (line.compare(0, frag.length(), frag) != 0) {

			for (j = 0; j < fragLength; j++) {

				fragQueries[i][j] = line[j];
			}
			fragQueries[i][fragLength] = '\0';
			i++;
		}

	}

	//Closing the file instance after reading the file data
	file.close();
	return true;
}

long long int Queries_NW::needleman_wunsch(char* qFragment, char* subFragment) {
    
	int fLen = 16;
	long long int dp[17][17];
	//cout << "\n";
	//cout << "Q Fragment: " << qFragment;
	//cout << "	Sub Fragment: " << subFragment;

    for (int i = 0; i <= fLen; i++) {
        for (int j = 0; j <= fLen; j++) {
            if (i == 0) {

                dp[i][j] = j * gapPoint;
            } 
			else if (j == 0) {

                dp[i][j] = i * gapPoint;
            } 
			else {

                int match = dp[i-1][j-1] + (qFragment[i-1] == subFragment[j-1] ? matchPoint : misMatchPoint);
                int gap1 = dp[i-1][j] + gapPoint;
                int gap2 = dp[i][j-1] + gapPoint;
				dp[i][j] = max({ match, gap1, gap2 });
            }
        }
    }



    return dp[fLen][fLen];
}


void Queries_NW::checkRandomFragmentFromSubject()
{

	cout << "\n Problem 1 Part A || Randomly pick 10K, 100K, 1M n-mers of the subject dataset to conduct fuzzy searching within the query dataset using NW algorithm.\n";
	// generating a random number

	//random_device rd;

	//mt19937 gen(rd());

	auto startTime = chrono::high_resolution_clock::now();

	for (long long int i = 0; i < maxQueryFind; i++) {

		//uniform_int_distribution<int> dist(1, 30000000000);

		//long long int random_number = dist(gen);
		//srand(time(nullptr));
		long long int random_number= rand() % totalLengthOfhumenGenome + 1;

		//cout << "Random number: " << random_number << std::endl;

		long long int startIndex = random_number % (totalLengthOfhumenGenome - fragLength);

		char* randomFragment = new char[fragLength + 1];

		copy(humenGenome + startIndex, humenGenome + startIndex + fragLength, randomFragment);

		randomFragment[fragLength] = '\0';

		long long int similarityScore = ((fragLength - toleranceLevel) * matchPoint) + (toleranceLevel * misMatchPoint);

		for (long long int i = 0; i < totalNoOfFragments; i++) {

			if (needleman_wunsch(fragQueries[i], randomFragment) >= similarityScore) {

				similarQueryFoundcount++;
				cout << "Query found: " << similarQueryFoundcount << " || Subject [" << randomFragment << "] is found in fragment queries [" << fragQueries[i] << "] with similarity score of " << similarityScore << ".";
				break;
			}
		}
	
		string mValue = "";
		if (i == 10000 || i == 100000 || i == 1000000|| i== maxQueryFind-1 || i%100) {
			switch (i) {
			case 10000:
				mValue = "10k";
				break;

			case 100000:
				mValue = "100k";
				break;

			case 1000000:
				mValue = "1Million";
				break;
            default:
                mValue = "for "+ to_string(i)+ " Records";
				break;


			}
			// Get the end time
			auto endTime = chrono::high_resolution_clock::now();
			auto totalTimeTakenInSec = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
			cout << "\nOur Progrom took " << (totalTimeTakenInSec.count()) / 1000000.0 << " seconds for checking " << mValue << " fragments similarity scores.\n";
			cout << "\Hits count:" << similarQueryFoundcount;

		}
	}
	
}


void Queries_NW::createAndSearchRandomFuzzyFragment()
{
	// generating a random number

	cout << "\n Problem 1 Part B || Completely random 10K, 100K, 1M n-mers to conduct fuzzy searching within the query dataset using NW algorithm.\n";

	//random_device rd;

	//mt19937 gen(rd());
	similarQueryFoundcount = 0;
	auto startTime = chrono::high_resolution_clock::now();
	char humanGenomesChars[] = { 'A','C','G','N','T' };

	for (long long int i = 0; i < maxQueryFind; i++) {

		//uniform_int_distribution<int> dist(0, 100);

		

		char* randomFragment = new char[fragLength + 1];
		
		for (int idx = 0; idx < fragLength; idx++) {

			//int random_number = dist(gen);
			//srand(std::time(nullptr));

			//long long int random_number = rand() % totalLengthOfhumenGenome + 1;

			int startIndex = rand() % 5;

			randomFragment[idx] = humanGenomesChars[startIndex];

		}

		randomFragment[fragLength] = '\0';

		long long int similarityScore = ((fragLength - toleranceLevel) * matchPoint) + (toleranceLevel * misMatchPoint);

		for (long long int i = 0; i < totalNoOfFragments; i++) {

			if (needleman_wunsch(fragQueries[i], randomFragment) >= similarityScore) {

				similarQueryFoundcount++;
				cout << "Query found: " << similarQueryFoundcount << " || Subject [" << randomFragment << "] is found in fragment queries [" << fragQueries[i] << "] with similarity score of " << similarityScore << ".";
				break;
			}
		}

		cout << "\nNot Found.\n";

		string mValue = "";
		if (i == 1000 || i == 100000 || i == 1000000 || i== maxQueryFind -1) {
			switch (i) {
			case 10000:
				mValue = "10k";
				break;

			case 100000:
				mValue = "100k";
				break;

			case 1000000:
				mValue = "1Million";
				break;

			default:
				mValue = "for all random";
				break;

			}
			// Get the end time
			auto endTime = chrono::high_resolution_clock::now();
			auto totalTimeTakenInSec = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
			cout << "\nOur Progrom took " << (totalTimeTakenInSec.count()) / 1000000.0 << " seconds for checking " << mValue << " fragments similarity scores.\n";
			cout << "\Hits count:" << similarQueryFoundcount;

		}
	}





}
