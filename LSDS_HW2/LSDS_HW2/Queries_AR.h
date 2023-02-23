#ifndef Queries_h
#define Queries_h
#include <string>
#include <stdlib.h>
using namespace std;

#pragma once

class Queries_AR
{

	private:
		
		string QueriesFilePath;

	public:

		char** fragQueries;

		int fragLength = 32;

		long long int totalNoOfFragments = 0, fragmentFileLength = 0;

		Queries_AR();

		Queries_AR(string fPath);

		bool GetTheLengthOfFragments();

		bool ReadQuery();

		void insertionSort();

		~Queries_AR();

};

#endif

