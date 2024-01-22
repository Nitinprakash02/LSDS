#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <math.h>
#include "Queries_HT.h"
using namespace std;

long long int Queries_HT::convertSeqToRedix(char* seq) {

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


void Queries_HT::insertNMerSeq(char* sequence) {


	long long position = convertSeqToRedix(sequence) % sizeOfTheHashTable;


	HTNode* temp = new HTNode;

	temp->key = sequence;

	temp->next = NULL;

	if (queriesHT[position] == NULL)
		queriesHT[position] = temp;

	else
	{

		CollisionsCount++;

		temp->next = queriesHT[position];

		queriesHT[position] = temp;

	}

}

bool Queries_HT::searchBMerSeq(char* sequence) {

	long long int position = convertSeqToRedix(sequence) % sizeOfTheHashTable;

	if (queriesHT[position] == NULL) {

		return false;
	}
	else {

		HTNode* temp = queriesHT[position];

		while (temp != NULL) {

			if (strcmp(temp->key, sequence) == 0) {

				return true;
			}

			temp = temp->next;
		}

		return false;
	}
}
bool Queries_HT::GetTheLengthOfHumenGenome() {

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

bool Queries_HT ::readHumengenomes() {

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



bool Queries_HT::GetTheLengthOfFragments() {

	string line = "";
	string frag = ">Fragment";
	//opening the file 
	ifstream file(fragmentFilePath);

	if (!file.is_open()) {
		cout << "Invaild File";
		return -1;
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
	return 0;

}

//Reading data from fragment file
bool Queries_HT::readFragmentData() {

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
		return -1;
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
	return 0;
}

Queries_HT::Queries_HT(string HGfilepath, string fragmentFilepath, long long int mVal, long long int fragmentSize) {

	humenGenomesfilePath=HGfilepath;
	fragmentFilePath = fragmentFilepath;
	sizeOfTheHashTable = mVal;
	fragLength = fragmentSize;
	CollisionsCount = 0;


}

Queries_HT::~Queries_HT(){

	delete[] humenGenome;

	for (long long i = 0; i < totalNoOfFragments; i++)
		delete[] fragQueries[i];

	delete[] fragQueries;

	// deallocating the hashtable
	for (long long i = 0; i < sizeOfTheHashTable; i++)
	{
		// deleting the linked list
		removeHTData(queriesHT[i]);

		queriesHT[i] = NULL;

		delete[] queriesHT[i];
	}

	delete[] queriesHT;
}


void Queries_HT::removeHTData(HTNode* head)
{
	while (head != NULL)
	{
		HTNode* current = head;
		head = head->next;
		delete current;
	}
}


void Queries_HT::runMyHW() {


	// Get the end time
	auto startTime = chrono::high_resolution_clock::now();

	cout << "\nSize of the HashTable:" << sizeOfTheHashTable;

	createHashTable();

	for (long long int frag = 0; frag < totalNoOfFragments; frag++) {
		//cout << "\nfrag: " << frag << " Query:" << fragQueries[frag];
		if (frag % 100000 == 0) {
			cout << "\nfrag: " << frag << " Query:" << fragQueries[frag];
		}
		insertNMerSeq(fragQueries[frag]);

	}

	// Get the end time
	auto endTime = chrono::high_resolution_clock::now();
	auto totalTimeTakenInSec = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
	// Displaying the time taken for computeNumOfChar function
	string mValue = "";
	switch (sizeOfTheHashTable) {
	case 1000000:
		mValue = "1 Million";
		break;

	case 10000000:
		mValue = "10 Million";
		break;

	case 30000000:
		mValue = "30 Million";
		break;

	case 60000000:
		mValue = "60 Million";
		break;

	}
	cout << "\nOur Progrom took " << (totalTimeTakenInSec.count()) / 1000000.0 << " seconds for populating " << mValue << " fragments into hash table.\n";

	cout << "\ninsertion done";
	cout << "\nCollision count:" << CollisionsCount;

}

void Queries_HT::runMyHW1() {


	// Get the end time
	auto startTime = chrono::high_resolution_clock::now();

	cout << "\nSize of the HashTable:" << sizeOfTheHashTable;

	createHashTable();

	for (long long int frag = 0; frag < totalNoOfFragments; frag++) {
		//cout << "\nfrag: " << frag << " Query:" << fragQueries[frag];
		if (frag % 100000 == 0) {
			cout << "\nfrag: " << frag << " Query:" << fragQueries[frag];
		}
		insertNMerSeq(fragQueries[frag]);

	}

	// Get the end time
	auto endTime = chrono::high_resolution_clock::now();
	auto totalTimeTakenInSec = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
	// Displaying the time taken for computeNumOfChar function
	string mValue = "";
	switch (sizeOfTheHashTable) {
	case 1000000:
		mValue = "1 Million";
		break;

	case 10000000:
		mValue = "10 Million";
		break;

	case 30000000:
		mValue = "30 Million";
		break;

	case 60000000:
		mValue = "60 Million";
		break;

	}
	cout << "\nOur Progrom took " << (totalTimeTakenInSec.count()) / 1000000.0 << " seconds for populating " << mValue << " fragments into hash table.\n";

	cout << "\ninsertion done";
	cout << "\nCollision count:" << CollisionsCount;
	long long int fragCount = 0;
	startTime = chrono::high_resolution_clock::now();
	//cout << "\ntotalLengthOfhumenGenome" << totalLengthOfhumenGenome;
	//cout << "\nsizeOfTheHashTable:" << sizeOfTheHashTable;
	for (long long int hGData = 0; hGData < totalLengthOfhumenGenome - fragLength + 1; hGData++) {

		char* seqToSearch = new char[fragLength + 1];
		string stS = "";
		for (long long int sFrag = 0; sFrag < fragLength; sFrag++) {

			seqToSearch[sFrag] = humenGenome[hGData + sFrag];
			stS += humenGenome[hGData + sFrag];
		}
		//cout << "\nserching for " << stS;
		seqToSearch[fragLength] = '\0';
		if (searchBMerSeq(seqToSearch)) {
			if (fragCount < 10)
				cout << "\nFound :" << stS;
			fragCount++;

		}
	}
	endTime = chrono::high_resolution_clock::now();
	totalTimeTakenInSec = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
	cout << "\nfragment found: " << fragCount;
	cout << "\n.Our Progrom took " << (totalTimeTakenInSec.count()) / 1000000.0 << " seconds to search for every possible 16-character long fragment of the subject dataset within the query dataset for m value " << mValue << " into hash table.\n";

	//}

}


void Queries_HT::createHashTable() {

	queriesHT = new HTNode * [sizeOfTheHashTable];

	for (long long int i = 0; i < sizeOfTheHashTable; i++) {

		queriesHT[i] = NULL;
	}

}
