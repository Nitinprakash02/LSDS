#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "Queries_AR.h"
#define headerSymbol ">"
using namespace std;

char* humenGenome;
string filePath, filePath1;
int fragLength = 0;
char** fragQueries;
long long int totalNoOfFragments = 0;

//Scaffold Variable
long long int fileLength = 0, totalLengthOfhumenGenome = 0, totalNoOfScaffold = 0;

bool GetTheLengthOfHumenGenome() {

	string line = "";
	string header = ">";

	ifstream file(filePath1);

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

bool ReadHumenGenome() {

	string line = "";
	string header = ">";
	long long int i = 0;
	int	j = 0;

	humenGenome = new char [totalLengthOfhumenGenome];

	ifstream file(filePath1);

	if (!file.is_open()) {
		cout << "Invaild File";
		return false;
	}

	while (getline(file, line)) {

		if (line.compare(0, header.length(), header) != 0 && line.compare("") != 0) {

			for (j = 0; j < line.length(); j++) {

				humenGenome[i] = line[j];
				i++;
			}
			
		}

	}

	//Closing the file instance after reading the file data
	file.close();
	return true;
}

bool CheckFragInHumanGenome(char* fragToSearch) {
	
	bool result = false;
	long long int i = 0,f=0;
	long long int foundat = -1;
	while (i <= totalLengthOfhumenGenome - fragLength-1 && f <= fragLength) {
		


			if (humenGenome[i] == fragToSearch[f]) {
				if (foundat == -1) {
					foundat = i;
					f = 0;
				}
				i++;
				f++;
			}
			else {
				i++;
				f=0;
				if (foundat != -1) {
					i = foundat+1;
					foundat = -1; 
				}

			}
			if (f == fragLength) {
				return true;
			}

		
		

	}
	return false;

}

void normalSearch() {

	long long int hGenome = 0, foundCount=0;
	long long int i = 0;

	auto startTime = chrono::high_resolution_clock::now();
	auto endTime = chrono::high_resolution_clock::now();
	long long int querySearchCount = 0;

	for (hGenome = 0; hGenome <= totalLengthOfhumenGenome - 31; hGenome++) {
		querySearchCount++;
		string fragmentName = "";
		//long long int tempHGenome = hGenome;
		i = 0;
		/*while (i < fragLength) {
			check[i] = humenGenome[tempHGenome];
			fragmentName += humenGenome[tempHGenome];
			tempHGenome++;
			i++;
		}*/
		long long int k = 0;
		bool notFound = false;
		for (k = 0; k < totalNoOfFragments; k++) {
			long long int tempHGenome = hGenome;
			fragmentName = "";
			for (i = 0; i < fragLength; i++) {
				fragmentName += humenGenome[tempHGenome];

				if (fragQueries[k][i] != humenGenome[tempHGenome]) {
					notFound = true;
					break;
				}
				tempHGenome++;

			}
			if (notFound == false) {
				
				if (foundCount % 5 == 0) {
					cout << "Found: " << fragmentName << endl;
					
				}
				foundCount++;
				break;
				//hGenome += fragLength;
			}
			notFound = false;

		}
		if (querySearchCount == 10000 || querySearchCount == 100000 || querySearchCount == 1000000) {

			string searchQ = "";
			switch (querySearchCount) {
			case 10000:
				searchQ = "10K";
				break;
			case 100000:
				searchQ = "100K";
				break;
			case 1000000:
				searchQ = "1M";
				break;
			default:
				searchQ = "";
			}

			endTime = chrono::high_resolution_clock::now();
			auto totalTimeTakenInSec = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
			// Displaying the time taken for computeNumOfChar function
			cout << "Our Progrom took " << (totalTimeTakenInSec.count()) / 1000000.0 << " seconds to search "<< searchQ <<"\n";
		}
		
	}

}

	

int binarySearch(long long int left, long long int right, char* target) {
	
	long long int i = 0,j=0;
	bool aboveMid = false;
	bool belowMid = false;
	bool foundAtMid = false;
	
	while (left <= right) {
		int mid = left + (right - left) / 2;
		int count = 0;
		for (i = 0; i < fragLength; i++) {
			for (j = 0; j < fragLength; j++) {
				if (fragQueries[mid][j] > target[j]) {
					
					aboveMid = true;
					break;
				}
				else if (fragQueries[mid][j] < target[j]) {
					
					belowMid = true;
					break;
				}
				else {
					count++;
				}

			}
			if (aboveMid == true || belowMid == true) {
				break;
			}
			if (count == fragLength) {
				return mid;
			}
		}
		
		if (count == fragLength) {
			return mid;
		}
		else if (aboveMid == true) {
			right = mid - 1;
			aboveMid = false;
		}
		else {
			left = mid + 1;
			belowMid = false;
		}
	}
	return -1; // target not found
}

void binarySearch2(long long int leftC, long long int rightC) {

	long long int i = 0, j = 0, foundCount = 0;
	bool aboveMid = false;
	bool belowMid = false;
	bool foundAtMid = false;
	long long int hGenome = 0;

	auto startTime = chrono::high_resolution_clock::now();
	auto endTime = chrono::high_resolution_clock::now();
	long long int querySearchCount = 0;

	for (hGenome = 0; hGenome <= totalLengthOfhumenGenome - 31; hGenome++) {

		long long int left = leftC;
		long long int right = rightC;
		querySearchCount++;
		string fragmentName = "";
		while (left <= right) {
			int mid = left + (right - left) / 2;
			int count = 0;
			long long int temphGenome = hGenome;
			for (i = 0; i < fragLength; i++) {
				count = 0;
				fragmentName = "";
				for (j = 0; j < fragLength; j++) {
					if (fragQueries[mid][j] > humenGenome[temphGenome]) {

						aboveMid = true;
						break;
					}
					else if (fragQueries[mid][j] < humenGenome[temphGenome]) {

						belowMid = true;
						break;
					}
					else {
						fragmentName += humenGenome[temphGenome];
						count++;
					}
					temphGenome++;

				}
				if (aboveMid == true || belowMid == true) {
					break;
				}
				if (count == fragLength) {
					break;
					cout << "Found: " << fragmentName << endl;
					//hGenome += fragLength;
				}
			}

			if (count == fragLength) {
				
				if (foundCount % 5 == 0) {
					cout << "Found: " << fragmentName << endl;
				}
				foundCount++;
				break;
				//hGenome += fragLength-1;
			}
			else if (aboveMid == true) {
				right = mid - 1;
				aboveMid = false;
			}
			else {
				left = mid + 1;
				belowMid = false;
			}
		}

		if (querySearchCount == 10000 || querySearchCount == 100000 || querySearchCount == 1000000) {
			
			string searchQ = "";
			switch (querySearchCount) {
				case 10000:
					searchQ = "10K";
					break;
				case 100000:
					searchQ = "100K";
					break;
				case 1000000:
					searchQ = "1M";
					break;
				default:
					searchQ = "";
			}

			endTime = chrono::high_resolution_clock::now();
			auto totalTimeTakenInSec = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
			// Displaying the time taken for computeNumOfChar function
			cout << "Our Progrom took " << (totalTimeTakenInSec.count()) / 1000000.0 << " seconds to search "<< searchQ <<"\n";
		}
		//cout << "Not Found"; // target not found

	}
}

int main() {

	filePath = "C:/Users/np679/Downloads/human_reads.fa";
	Queries_AR queryAR = Queries_AR(filePath);
	fragLength = queryAR.fragLength;
	bool resGetTheLengthOfFragments = queryAR.GetTheLengthOfFragments();
	bool resReadQuery = queryAR.ReadQuery();
	fragQueries= queryAR.fragQueries;
	totalNoOfFragments = queryAR.totalNoOfFragments;

	filePath1 = "C:/Users/np679/Downloads/human.txt";
	GetTheLengthOfHumenGenome();
	ReadHumenGenome();
	long long int frag = 0;
	bool found = false;

	/*/auto startTime = chrono::high_resolution_clock::now();

	// Calling computeNumOfChar function to get the count of characters (A, C, G, or T)
	for (frag = 0; frag < queryAR.totalNoOfFragments; frag++) {
		found = CheckFragInHumanGenome(fragQueries[frag]);
		if (found == true) {

			cout << "Found" << endl;
		}
		else {

			cout << "Not Found" << endl;
		}

	}

	// Get the end time
	auto endTime = chrono::high_resolution_clock::now();
	auto totalTimeTakenInSec = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
	// Displaying the time taken for computeNumOfChar function
	cout << "Our Progrom took " << (totalTimeTakenInSec.count()) / 1000000.0 << " seconds to seconds for unsorted fragments.\n";

	queryAR.insertionSort();
	
	startTime = chrono::high_resolution_clock::now();
	*/

	// Calling computeNumOfChar function to get the count of characters (A, C, G, or T)
	/*for (frag = 0; frag < queryAR.totalNoOfFragments; frag++) {
		found = CheckFragInHumanGenome(fragQueries[frag]);
		if (found == true) {

			cout << "Found" << endl;
		}
		else {

			cout << "Not Found" << endl;
		}

	}*/
	for (frag = 0; frag < queryAR.totalNoOfFragments; frag++) {
		for (int k = 0; k < fragLength; k++) {
			cout << fragQueries[frag][k];
		}
		cout << endl;
	}
	cout << "Normal Search " << endl;
	auto startTime = chrono::high_resolution_clock::now();
	normalSearch();
	auto endTime = chrono::high_resolution_clock::now();
	auto totalTimeTakenInSec = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
	// Displaying the time taken for computeNumOfChar function
	cout << "Our Progrom took " << (totalTimeTakenInSec.count()) / 1000000.0 << " seconds to seconds for unsorted fragments.\n";


	cout << "After sorting"<<endl;
	queryAR.insertionSort();

	fragQueries = queryAR.fragQueries;
	for (frag = 0; frag < queryAR.totalNoOfFragments; frag++) {
		for (int k = 0; k < fragLength; k++) {
			
			cout << fragQueries[frag][k];
		}
		cout << endl;
		
	}
	long long int hGenome = 0;
	int i = 0;
	static const unsigned int constFragLength = fragLength;
	char* check= new char[constFragLength];
	
	startTime = chrono::high_resolution_clock::now();
	/*for (hGenome = 0; hGenome <= totalLengthOfhumenGenome - 31; hGenome++) {

		string fragmentName = "";
		long long int tempHGenome = hGenome;
		i = 0;
		while (i < fragLength) {
			check[i] = humenGenome[tempHGenome];
			fragmentName += humenGenome[tempHGenome];
			tempHGenome++;
			i++;
		}
		
		long long int searchResult = binarySearch(0, queryAR.totalNoOfFragments - 1, check);

		if (searchResult != -1) {

			cout << "Fragment Found: " << fragmentName <<"  index"<< hGenome << endl;
			hGenome += fragLength-1;
		}
		else{
		
			cout << "Fragment Not Found: " << fragmentName << endl;
		}
		
	}*/

	binarySearch2(0, queryAR.totalNoOfFragments - 1);

	// Get the end time
	endTime = chrono::high_resolution_clock::now();
	totalTimeTakenInSec = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
	// Displaying the time taken for computeNumOfChar function
	cout << "Our Progrom took " << (totalTimeTakenInSec.count()) / 1000000.0 << " seconds for sorted fragments.\n";
	for (frag = 0; frag < queryAR.totalNoOfFragments; frag++) {
		delete[] fragQueries[frag];
	}
	delete[] fragQueries;
	delete[] humenGenome;

	return 0;

}