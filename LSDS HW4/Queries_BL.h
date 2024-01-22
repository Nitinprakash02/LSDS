#pragma once

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <math.h>
#include <string.h>
#include "Queries_BL.h"

using namespace std;

class Queries_BL
{
    struct Node
    {
        char* data;
        long long int index;
        Node* next;
    };
    Node** blastHT;

    char* humenGenome;

    char** fragQueries;

    long long int maxQueryFind = 0, toleranceLevel = 2, similarQueryFoundcount = 0, htLength=0;

    const int fragLength = 16;

    string fragmentFilePath = "", humenGenomesfilePath = "";

    int gapPoint = -1, misMatchPoint = -1, matchPoint = 2;

public:

    long long int  totalNoOfScaffold = 0, totalLengthOfhumenGenome = 0, totalNoOfFragments = 0, kSize=4;

    Queries_BL();

    Queries_BL(string HumenGenomesfilePath, string FragmentFilePath, int ToleranceLevel);

    bool GetTheLengthOfHumenGenome();

    bool readHumanGenomes();

    bool GetTheLengthOfFragments();

    bool readFragmentData();

    long long int needleman_wunsch(char* qFragment, char* subFragment);

    long long int convertSeqToRedix(char* seq);

    void checkRandomFragmentFromSubject(int Choice);

    void createAndSearchRandomFuzzyFragment();

    void insertDatainHT(char* subjectData, long long int sIndex, long long int subLength);

    void applyBlastAlgo();
};

