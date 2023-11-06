/*
Header file for merkle tree implementation
*/

/*
Updated by Krish Shah, U75802512, kshah26@bu.edu
*/

#ifndef MerkleTree_h
#define MerkleTree_h

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <fstream>

using namespace std;

class Node {
public:
    string key;                                           // Store hash
    vector<Node*> children;                               // Store vector of children nodes
    Node(const string& val);                              // Constructor
};

class merkleTree {
private:
    Node* root;                                           // Pointer to root node
    void initializeMerkleTree();                          // Initializes the Merkle Tree with current data
    Node* createNodeWithHashedChildren(const vector<Node*>& children); // Helper to create node with hashed children
    void processLevel(vector<Node*>& prev_level_nodes, vector<Node*>& current_level_nodes); // Helper to process tree level
    void collectNodesAtEachLevel(Node* node, vector<vector<Node*>>& all_nodes, int level); // Helper function to recursively collect nodes at each level of the tree.
    void printNodesAtEachLevel(const vector<vector<Node*>>& all_nodes); // Helper function to print the nodes of the tree at each level.

public:
    vector<int> data;                                     // Store data that tree is built on
    merkleTree();                                         // Default constructor
    merkleTree(const vector<int>& data);                  // Constructor with arguments
    string concatenateHash(const vector<Node*>& nodes);   // Merge and rehash nodes
    void printTree(const Node* node, int depth = 0);      // Visualization of tree
    void verify();                                        // Verify integrity of tree
    void overwrite(int originalValue, int newValue);      // Overwrite given value with new value and rehash tree
    void insert(int newValue);                            // Insert new value to the end of data vector and rehash tree
    void printRoot();                                     // Print root of tree
    Node* getRoot();                                      // Returns root of tree
};

vector<int> readIntsFromFile(const string& filename);     // Helper function to read from inputed file

#endif /* MerkleTree_h */
