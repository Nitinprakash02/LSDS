#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include "Queries_BL.h"

using namespace std;

Queries_BL::Queries_BL(string HumenGenomesfilePath, string FragmentFilePath, int ToleranceLevel)
{

	humenGenome = NULL;

	fragQueries = NULL;

	humenGenomesfilePath = HumenGenomesfilePath;

	fragmentFilePath = FragmentFilePath;

	toleranceLevel = ToleranceLevel;


}

Queries_BL::Queries_BL() {

	humenGenome = NULL;

	fragQueries = NULL;

	humenGenomesfilePath = "";

	fragmentFilePath = "";

	toleranceLevel = 2;

}
bool Queries_BL::GetTheLengthOfHumenGenome() {

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

bool Queries_BL::readHumanGenomes() {

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

bool Queries_BL::GetTheLengthOfFragments() {

	string line = "";
	string frag = ">fragment";
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
bool Queries_BL::readFragmentData() {

	string line = "";
	string frag = ">fragment";
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

long long int Queries_BL::needleman_wunsch(char* qFragment, char* subFragment) {

	int fLen = 16;
	long long int dp[17][17];
	cout << "\n";
	cout << "Q Fragment: " << qFragment;
	cout << "	Sub Fragment: " << subFragment;

	for (int i = 0; i <= fLen; i++) {
		for (int j = 0; j <= fLen; j++) {
			if (i == 0) {

				dp[i][j] = j * gapPoint;
			}
			else if (j == 0) {

				dp[i][j] = i * gapPoint;
			}
			else {

				int match = dp[i - 1][j - 1] + (qFragment[i - 1] == subFragment[j - 1] ? matchPoint : misMatchPoint);
				int gap1 = dp[i - 1][j] + gapPoint;
				int gap2 = dp[i][j - 1] + gapPoint;
				dp[i][j] = max({ match, gap1, gap2 });
			}
		}
	}

	return dp[fLen][fLen];
}

long long int Queries_BL::convertSeqToRedix(char* seq) {

	long long int baseVal = 5, charValue = -1;
	long long int radixValue = 0, i;

	for (i = 0; i < fragLength; i++) {
		switch (seq[i]) {
		case 'A':
			//cVal = A;
			charValue = 0;
			break;

		case 'C':
			//cVal = C;
			charValue = 1;
			break;;

		case 'G':
			//cVal = G;
			charValue = 2;
			break;

		case 'T':
			//cVal = T;
			charValue = 3;
			break;

		case 'N':
			//cVal = N;
			charValue = 4;
			break;

		default:
			charValue = -1;
		}
		if (charValue != -1) {
			radixValue = radixValue + (charValue * pow(baseVal, fragLength - i - 1));
		}

	}

	return radixValue;
}

void Queries_BL::checkRandomFragmentFromSubject( int Choice) {

	htLength = totalLengthOfhumenGenome * 2;

	blastHT = new Node * [htLength];

	for (long long int i = 0; i < htLength; i++) {

		blastHT[i] = NULL;
	}


	long long int random_number = rand() % totalLengthOfhumenGenome + 1;

	cout << "Random number: " << random_number << std::endl;

	long long int startIndex = random_number % (totalLengthOfhumenGenome - fragLength);
	long long int searchForSubLen=0, hitsCount=0;
	
	for (long long int i = 0; i < 4; i++) {

		hitsCount = 0;
		switch (i) {
		case 0:
			searchForSubLen = 10000;
			//subjectData = new char[searchForSubLen + 1];
			break;
		case 1:
			searchForSubLen = 100000;
			//subjectData = new char[searchForSubLen + 1];
			break;
		case 2:
			searchForSubLen = 1000000;
			//subjectData = new char[searchForSubLen + 1];
			break;
		case 3:
			searchForSubLen = totalLengthOfhumenGenome;
			//subjectData = new char[searchForSubLen + 1];
			break;
		}

        char* subjectData=new char[searchForSubLen + 1];


		long long int startIndex = rand() % searchForSubLen;

		if (Choice == 1 || Choice == 0) {
			copy(humenGenome + startIndex, humenGenome + startIndex + searchForSubLen, subjectData);
		}

		else {

			char humanGenomesChars[] = { 'A','C','G','N','T' };

			//for (long long int i = 0; i < maxQueryFind; i++) {


			for (int idx = 0; idx < searchForSubLen; idx++) {

				//int random_number = dist(gen);
		
				//srand(std::time(nullptr));

				//long long int random_number = rand() % totalLengthOfhumenGenome + 1;

				subjectData[idx] = humanGenomesChars[rand() % 5];

			}


			//}

		}
		subjectData[searchForSubLen] = '\0';

		insertDatainHT(subjectData, startIndex, searchForSubLen);

		applyBlastAlgo();

	}
}

void Queries_BL::insertDatainHT(char* subjectData, long long int sIndex, long long int subLength) {

	for (long long int idx = 0; idx < subLength - kSize + 1; idx++)
	{
		char kFragment[4 + 1];

		copy(subjectData + idx, subjectData + idx + kSize, kFragment);

		kFragment[kSize] = '\0';


		long long int fragPos = convertSeqToRedix(kFragment) % htLength;

		Node* temp = new Node;
		temp->data = kFragment;
		temp->index = sIndex + idx;
		temp->next = NULL;

		if (blastHT[fragPos] == NULL) {

			blastHT[fragPos] = temp;
		}
		else{

			temp->next = blastHT[fragPos];
			blastHT[fragPos] = temp;
		}


	}

}

void Queries_BL::applyBlastAlgo() {

	long long int subIndex;
	bool found = false;
	long long int similarityScore = ((fragLength - toleranceLevel) * matchPoint) + (toleranceLevel * misMatchPoint);

	for (long long int frag = 0; frag < totalNoOfFragments; frag++){

		for (long long int fragChar = 0; fragChar < fragLength - kSize + 1; fragChar++){
			char seedFrag[4 + 1];

			copy(fragQueries[frag] + fragChar, fragQueries[frag] + kSize + fragChar, seedFrag);

			seedFrag[kSize] = '\0';


			long long int frgLoc = convertSeqToRedix(seedFrag) % htLength;

			if (blastHT[frgLoc] != NULL){

				Node* curr = blastHT[frgLoc];

				while (curr != NULL){

					if (strcmp(curr->data, seedFrag) == 0)
						subIndex = curr->index;
						found = true;
						break;

					curr = curr->next;
					found = false;
				}
			}

			char subFrags[16 + 1];
			if (found == true)
				
				
				copy(humenGenome + (subIndex - fragChar), humenGenome + (subIndex - fragChar) + fragLength, subFrags);
				subFrags[fragLength] = '\0';

				if (needleman_wunsch(fragQueries[frag], subFrags) >= similarityScore) {

					similarQueryFoundcount++;
					cout << "Query found: " << similarQueryFoundcount << " || Subject [" << subFrags << "] is found in fragment queries [" << fragQueries[frag] << "] with similarity score of " << similarityScore << ".";
					break;
				}
				
				break;
		}
	}
}