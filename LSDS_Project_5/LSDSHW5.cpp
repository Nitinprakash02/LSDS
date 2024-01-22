#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>
#include "Prefix_Trie.h"

using namespace std;

char* humenGenome;
char* kmer;

int fragLength = 36;

string humenGenomesfilePath = "";

long long int  totalNoOfScaffold = 0, totalLengthOfhumenGenome = 0;

bool GetTheLengthOfHumenGenome() {

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

bool readHumanGenomes() {

    //Reading the human Genomes data
    string line = "";
    string header = ">";
    long long int i = 0;
    int	j = 0;

    //Creating the humenGenome char array
    humenGenome = new char[totalLengthOfhumenGenome+1];

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

    humenGenome[fragLength] = '\0';

    //Closing the file instance after reading the file data
    file.close();
    return true;
}

/*char* generateRandomHumanSegments(char *resizedHumanGenomes) {
    
    //srand(time(NULL));
    int start_pos = rand() % (totalLengthOfhumenGenome - fragLength-1);
    cout<<"start_pos: "<<start_pos;
    char* kmer = new char[fragLength+1];
    //strncpy(kmer, genome_segment + start_pos, fragLength);
    //memcpy(kmer, genome_segment + start_pos, fragLength);
    //copy(resizedHumanGenomes + start_pos, resizedHumanGenomes + start_pos + fragLength, kmer);
    //char kmer[KMER_LENGTH + 1];
    for (int j = 0; j < fragLength; j++) {
        
        kmer[j] = resizedHumanGenomes[start_pos + j];
    }
    kmer[fragLength] = '\0';
    
    return kmer;
}*/

char* reduceTheHumanGenoms(long long int hGSize) {

    long long int start_pos = rand() % (totalLengthOfhumenGenome - hGSize-1);
    char *resizedHumanGenomes = new char[hGSize+1];
    //strncpy(resizedHumanGenomes, humenGenome + start_pos, hGenomesSize);
    //memcpy(resizedHumanGenomes, humenGenome + start_pos, fragLength);
    
    for(long long int i =0; i < hGSize;i++){
        resizedHumanGenomes[i]=humenGenome[start_pos+i];
    }
    //copy(humenGenome + start_pos, humenGenome + start_pos + hGSize, resizedHumanGenomes);
    resizedHumanGenomes[hGSize] = '\0';
    //cout<<"resizedHumanGenomes"<<resizedHumanGenomes<<endl;
    return resizedHumanGenomes;
}

char* generate_random_kmer(char *resizedHumanGenomes, long long int fragLength) {
    int k = 36;
    char* kmer = new char[k + 1];
    int startVal=rand() % fragLength;
    for (int i = 0; i < k; i++) {
        char base = resizedHumanGenomes[startVal+i];
        // introduce 5% per-base error rate
        if (rand() % 100 < 5) {
            // picking a random base different from the original one
            do {
                base = resizedHumanGenomes[rand() % fragLength];
            } while (base == kmer[i]);
        }
        kmer[i] = base;
    }
    kmer[k] = '\0';
    return kmer;
}


int main(int argc, char* argv[])
{
    
    cout<<"////////////////////////////////////////////\n";
    cout << "LSDS HW5: Prefix Trie\n";
    cout<<"////////////////////////////////////////////\n\n\n";

    //Variable declaration
    bool test = false;

    long long int fragmentLength = 16;

    //Collecting data from cmd
    humenGenomesfilePath = (test) ? "C:\\Users\\np679\\Downloads\\human.txt" : argv[1];

    string problem = (test) ? "ProbAB" : argv[2];

    long long int humenGenomesSize= (test) ? 50000 : atoi(argv[3]);

    int maxTolerance = (test) ? 1 : atoi(argv[4]);

    fragLength = (test) ? 36 : atoi(argv[5]);
    
    long long int noOfFragment = (test) ? 5000 : atoi(argv[6]);

    
    GetTheLengthOfHumenGenome();
    readHumanGenomes();

    // File content details
    cout << "Total number of scaffolds:" << totalNoOfScaffold << endl;

    cout << "Total number of Human Genome: " << totalLengthOfhumenGenome << endl;

    char* resizedHumanGenomes= reduceTheHumanGenoms(noOfFragment);
    


    cout << "Total number of Human Genome after reduced: " << humenGenomesSize <<"."<< endl;
    //cout<<"Data: "<<endl<<resizedHumanGenomes <<endl<<endl;
    cout<<"Running for "<< noOfFragment<<" numbers of fragment.\n\n\n";

    string searchQ = "";
    switch (noOfFragment) {
    case 5000:
        searchQ = "5K";
        break;
    case 50000:
        searchQ = "50K";
        break;
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
        searchQ = "full data";
    }

    srand(time(NULL));
    if (problem.compare("ProbA") == 0 ||problem.compare("ProbAB") == 0) {
        
        cout<<"======================\n";
        cout<<"Problem A";
        cout<<"\n======================\n";
        
        Prefix_Trie trie_Ak=Prefix_Trie();
        char kmerFrag[37];
        for (long long int i = 0; i < noOfFragment; i++) {
            long long int start_pos = rand() % (noOfFragment - fragLength-1);
            //cout<< "noOfFragment: "<<noOfFragment<<endl;
            
            
            for (int j = 0; j < fragLength; j++) {
                long long int indx =start_pos+j;
                //char a= resizedHumanGenomes[indx];
                //cout<<"indx: "<<indx<<endl;
                
                kmerFrag[j]=resizedHumanGenomes[indx];
            }
            kmerFrag[fragLength] = '\0';
            
            //cout<<"kmerFrag "<<i<<": "<<kmerFrag<<endl;
            //char* kmer = generate_random_kmer();

            trie_Ak.insert(kmerFrag);
            //delete[] kmerFrag;
            
        }
        
        long long int size_Ak = trie_Ak.count_nodes(trie_Ak.root);

        cout << "Size of trie for "<<searchQ<<" 36 - mers: " << size_Ak << endl;

        long long int matchCount = 0;

        matchCount = trie_Ak.count_matching_36_mers(resizedHumanGenomes, noOfFragment, fragLength, maxTolerance);

        cout << "Match Count for " << searchQ << " 36 mers: " << matchCount<<"\n\n\n\n";

    }
    
    if (problem.compare("ProbB") == 0 ||problem.compare("ProbAB") == 0) {
        
        cout<<"======================\n";
        cout<<"Problem B";
        cout<<"\n======================\n";
        Prefix_Trie trie_Bk=Prefix_Trie();
        for (long long int i = 0; i < noOfFragment; i++) {
            //char* kmer = generateRandomHumanSegments(resizedHumanGenomes);
            char* kmer = generate_random_kmer(resizedHumanGenomes, noOfFragment);
            //cout<<"kmeer: "<< kmer<<endl;
            trie_Bk.insert(kmer);

        }
        
        long long int size_Bk = trie_Bk.count_nodes(trie_Bk.root);

        cout << "Size of trie for " << searchQ << " 36-mers: " << size_Bk << endl;

        long long int matchCount = 0;

        matchCount = trie_Bk.count_matching_36_mers(resizedHumanGenomes, noOfFragment, fragLength, maxTolerance);

        cout << "Match Count for " << searchQ << " 36 mers: " << matchCount<<"\n\n\n\n";

        
    }
    
    delete resizedHumanGenomes;
    delete humenGenome;

    return 0;
}
    
