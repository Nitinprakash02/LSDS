#ifndef Queries_HT_h
#define Queries_HT_h
#include <string>
#include <stdlib.h>
#include <cstring>

#include <fstream>

using namespace std;

class Queries_HT
{
    public:
        struct HTNode
        {
            char* key;
            HTNode* next;
        };

        char* subject_data, ** queries_data;

        HTNode** queriesHT;
        long long int fragLength = 16;
        long long int sizeOfTheHashTable = 0, CollisionsCount = 0;
        char* humenGenome;
        string fragmentFilePath, humenGenomesfilePath;
        char** fragQueries;
        long long int totalNoOfFragments = 0;

        //Scaffold Variable
        long long int fileLength = 0, totalLengthOfhumenGenome = 0, totalNoOfScaffold = 0;

        //Queries_HT();
        Queries_HT(string HGfilepath, string fragmentFilepath, long long int mVal, long long int fragmentSize);

        bool readHumengenomes();

        bool readFragmentData();

        long long int convertSeqToRedix(char* seq);

        ~Queries_HT();

        void insertNMerSeq(char* sequence);

        bool searchBMerSeq(char* sequence);
        bool GetTheLengthOfHumenGenome();

        bool GetTheLengthOfFragments();


        void runMyHW();
        void runMyHW1();

        void createHashTable();

        void removeHTData(HTNode* head);

};

#endif