#define _CRT_SECURE_NO_WARNINGS

#ifndef PREFIX_TRIE_H
#define PREFIX_TRIE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

class Prefix_Trie {

public:
    // Trie node structure
    struct TrieNode {
        std::unordered_map<char, TrieNode*> children;
        bool is_end_of_sequence;
        TrieNode() : is_end_of_sequence(false) {}
    };

    // Default constructor
    Prefix_Trie();

    // Custom constructor
    Prefix_Trie(const char* queries[], long long int n);

    // Destructor
    ~Prefix_Trie();

    // Copy constructor
    Prefix_Trie(const Prefix_Trie& other);

    // Function to insert a query into the trie
    void insert(const char* query);

    // Function to search the trie using a genome of size G with 1 mismatch tolerance
    char** search(const char* genome, long long int genome_size, long long int query_size, long long int num_matches);

    TrieNode* root;

    void clear(TrieNode* node);

    //TrieNode* copy_trie(const TrieNode* node);
    TrieNode* copy_trie(const TrieNode* node);

    bool fuzzy_search(const char* query, long long int query_size, long long int allowed_mismatches);

    long long int count_nodes(Prefix_Trie::TrieNode* node);

    long long int count_matching_36_mers(const char* segment, long long int segment_size, int fragLength, int maxTolerance);

    bool fuzzy_search_V3(TrieNode* node, const char* query, long long int query_size, int mismatches_left);
};

#endif // PREFIX_TRIE_H
