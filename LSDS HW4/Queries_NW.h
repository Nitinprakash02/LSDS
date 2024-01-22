#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <math.h>

using namespace std;

class Queries_NW
{

private:

    char* humenGenome;

    char** fragQueries;

    long long int maxQueryFind = 0, toleranceLevel = 2, similarQueryFoundcount=0;

    const int fragLength = 16;

    string fragmentFilePath = "", humenGenomesfilePath = "";

    int gapPoint = -1, misMatchPoint = -1, matchPoint = 2;

public:

    long long int  totalNoOfScaffold = 0, totalLengthOfhumenGenome = 0, totalNoOfFragments = 0;

    Queries_NW();

    Queries_NW(int MaxQueryFind, string HumenGenomesfilePath, string FragmentFilePath, int ToleranceLevel);

    bool GetTheLengthOfHumenGenome();

    bool readHumanGenomes();

    bool GetTheLengthOfFragments();

    bool readFragmentData();

    long long int needleman_wunsch(char* qFragment, char* subFragment);

    void checkRandomFragmentFromSubject();

    void createAndSearchRandomFuzzyFragment();
};

