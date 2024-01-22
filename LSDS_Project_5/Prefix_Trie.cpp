#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include "Prefix_Trie.h"
using namespace std;


// Trie node structure


// Default constructor
Prefix_Trie::Prefix_Trie() {
	root = new TrieNode();
}

Prefix_Trie::Prefix_Trie(const char* queries[], long long int n) {
	root = new TrieNode();
	for (long long int i = 0; i < n; i++) {
		insert(queries[i]);
	}
}

// Destructor
Prefix_Trie::~Prefix_Trie() {
	clear(root);
}

// Copy constructor
Prefix_Trie::Prefix_Trie(const Prefix_Trie& other) {
	root = copy_trie(other.root);
}

void Prefix_Trie::insert(const char* query) {
	TrieNode* current = root;
	while (*query != '\0') {
		char c = *query;
		if (current->children.find(c) == current->children.end()) {
			current->children[c] = new TrieNode();
		}
		current = current->children[c];
		query++;
	}
	current->is_end_of_sequence = true;
}


Prefix_Trie::Prefix_Trie::TrieNode* root;

void Prefix_Trie::clear(TrieNode* node) {
	if (!node) {
		return;
	}
	for (auto& child : node->children) {
		clear(child.second);
	}
	delete node;
}

Prefix_Trie::TrieNode* Prefix_Trie::copy_trie(const TrieNode* node) {
	if (!node) {
		return nullptr;
	}
	TrieNode* new_node = new TrieNode();
	new_node->is_end_of_sequence = node->is_end_of_sequence;
	for (const auto& child : node->children) {
		new_node->children[child.first] = copy_trie(child.second);
	}
	return new_node;
}



// Count the number of nodes in the trie using a depth-first search
long long int Prefix_Trie::count_nodes(Prefix_Trie::TrieNode* node) {
	if (!node) {
		return 0;
	}
	long long int count = 1;
	for (auto& child : node->children) {
		count += count_nodes(child.second);
	}
	return count;
}

long long int Prefix_Trie::count_matching_36_mers(const char* segment, long long int segment_size, int fragLength, int toleranceLvl) {

	long long int count = 0;
	for (long long int i = 0; i < segment_size - fragLength - 2; i++) {

		char* query = new char[fragLength + 1];
		//strncpy(query, segment + i, fragLength);
		copy(segment + i, segment + i + fragLength, query);
		query[fragLength] = '\0';
		if (fuzzy_search_V3(root, query, fragLength, toleranceLvl)) {
			//cout <<query <<":  Found a match and checked with up to "<<toleranceLvl<<" mismatches!" << endl;
			count++;
		}
		else {
			//cout << "No match found with up to 2 mismatches." << endl;
		}
		delete[] query;
	}
	return count;
}


// Function to perform fuzzy search of query string in a prefix trie
bool Prefix_Trie:: fuzzy_search_V3(TrieNode* node, const char* query, long long int query_size, int mismatches_left) {
	if (node == nullptr || mismatches_left < 0) {
		return false;
	}
	if (*query == '\0') {
		return node->is_end_of_sequence;
	}
	char c = *query;
	bool found_match = false;
	// Try matching the current character exactly
	if (node->children.find(c) != node->children.end()) {
		found_match = fuzzy_search_V3(node->children[c], query + 1, query_size - 1, mismatches_left);
	}
	// Try allowing for a mismatch
	if (!found_match) {
		for (const auto& kv : node->children) {
			if (kv.first != c) {
				found_match = fuzzy_search_V3(kv.second, query + 1, query_size - 1, mismatches_left - 1);
				if (found_match) {
					break;
				}
			}
		}
	}
	return found_match;
}






