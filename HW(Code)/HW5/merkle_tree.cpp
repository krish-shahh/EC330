// Krish Shah, U75802512, kshah26@bu.edu

/*
The insert function in the merkleTree class adds a new value to the Merkle tree by first appending it to the data vector, which holds the tree's underlying values. 
It then triggers a reconstruction of the tree through the initializeMerkleTree() function. 
This reconstruction begins at the leaves, hashing the updated set of values, and proceeds upwards. 
At each level, groups of four child nodes are combined into a new parent node by hashing their collective hashes until a singular new root hash is derived. 
This methodical rehashing ensures that the tree reflects the current set of data, maintaining the integrity and verifiability of the entire structure after the insertion of the new value.
*/

#include "merkle_tree.h"

using namespace std;

/* Hash function*/
inline string fnv1a(string const & text) {
    // 64 bit params
    uint64_t constexpr fnv_prime = 1099511628211ULL;
    uint64_t constexpr fnv_offset_basis = 14695981039346656037ULL;
    
    uint64_t hash = fnv_offset_basis;
    
    for(auto c: text) {
        hash ^= c;
        hash *= fnv_prime;
    }

    return to_string(hash);
}

/* Merkle Tree method for computing the hash of the concatenated hashes of children nodes 
   Using the provided hash function, concatenates child hashes from left to right and returns the hash 
   of the concatenation */
string merkleTree::concatenateHash(const vector<Node*>& nodes){
    string merged;
    //concatenate hashes of all inputed nodes 
    for(const Node* node: nodes){
        merged += node->key;
    }

    //take hash of concatenated nodes
    string mergedHash = fnv1a(merged);

    return mergedHash;
}

// Reads integers from file "filename"
vector<int> readIntsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file " + filename);
    }

    vector<int> int_from_file_vector;
    int data;
    while (file >> data) {
        int_from_file_vector.push_back(data);
    }

    return int_from_file_vector;
}

// Node Constructor
Node::Node(const string& val)
{
    this->key = val;        // sets hash = val
}

// Merkle Tree Default Constructor
merkleTree::merkleTree()
{
    this->root = nullptr;
}

// Merkle Tree Data Constructor
merkleTree::merkleTree(const vector<int>& data)
{
    this->data = data;
    this->initializeMerkleTree();
}

// Helper function to create a new Node with hashed children
Node* merkleTree::createNodeWithHashedChildren(const vector<Node*>& children) {
    string hashed_message = this->concatenateHash(children);
    Node* node = new Node(hashed_message);
    node->children = children;
    return node;
}

// Helper function to process levels of the tree
void merkleTree::processLevel(vector<Node*>& prev_level_nodes, vector<Node*>& current_level_nodes) {
    vector<Node*> concatenated_children;
    for (int j = 0; j < prev_level_nodes.size(); j++) {
        concatenated_children.push_back(prev_level_nodes[j]);
        if (concatenated_children.size() % 4 == 0 || j == prev_level_nodes.size() - 1) {
            current_level_nodes.push_back(createNodeWithHashedChildren(concatenated_children));
            concatenated_children.clear();
        }
    }
}

// Initializes proper merkle tree and assigns root node
void merkleTree::initializeMerkleTree() {
    int height = ceil(log(this->data.size()) / log(4)); // calculates height of merkle tree to be made

    vector<Node*> prev_level_nodes;
    vector<Node*> current_level_nodes;

    for (int h = 0; h <= height; h++) {
        if (h == 0) {   // initializes the bottom row of the merkle tree
            for (int value : this->data) {
                current_level_nodes.push_back(new Node(fnv1a(to_string(value))));
            }
        } else {    // groups the nodes in groups of 4
            processLevel(prev_level_nodes, current_level_nodes);
        }

        // Prepare for the next iteration
        prev_level_nodes.swap(current_level_nodes);
        current_level_nodes.clear();
    }

    // The root is the last remaining node after processing all levels
    if (!prev_level_nodes.empty()) {
        this->root = prev_level_nodes[0];
    }
}

// Helper function to collect all nodes at each level of the tree
void merkleTree::collectNodesAtEachLevel(Node* node, vector<vector<Node*>>& all_nodes, int level) {
    if (node == nullptr) {
        return; // Base case: node is null
    }

    // Resize the all_nodes vector to ensure it is large enough to hold this level
    if (all_nodes.size() == level) {
        all_nodes.push_back({});
    }

    // Add the current node to its level
    all_nodes[level].push_back(node);

    // Recursively collect nodes for each child
    for (Node* child : node->children) {
        collectNodesAtEachLevel(child, all_nodes, level + 1);
    }
}

// Helper function to print nodes at each level
void merkleTree::printNodesAtEachLevel(const vector<vector<Node*>>& all_nodes) {
    string spaces = "";
    for (int i = 0; i < all_nodes.size(); ++i) {
        for (Node* node : all_nodes[i]) {
            cout << spaces << "Level " << i << ": " << node->key << endl;
        }
        spaces += "  "; // Increase indentation for the next level
    }
}

void merkleTree::printTree(const Node* node, int depth) {
    // Vector to hold all nodes at each level
    vector<vector<Node*>> all_nodes;

    // Collect all nodes at each level starting from the root
    collectNodesAtEachLevel(this->root, all_nodes, 0);

    // Print all nodes at each level with proper formatting
    printNodesAtEachLevel(all_nodes);
}

// Verifies integrity of tree. Returns true iff integrity holds
void merkleTree::verify()
{
    // story original hash
    string original_hash = this->root->key;
    
    // rebuild the tree
    this->initializeMerkleTree();

    cout << (original_hash == this->root->key ? "True" : "False");
}

// Overwritres originalValue with newValue if originalValue exists in data. Rehashes tree
void merkleTree::overwrite(int originalValue, int newValue)
{
    auto it = find(this->data.begin(), this->data.end(), originalValue);
    if (it != this->data.end()) {
        *it = newValue;
        initializeMerkleTree();
    }
    
}

// Inserts newValue into the data vector and rehashes the tree
void merkleTree::insert(int newValue)
{
    // adds newValue to end of data vector
    this->data.push_back(newValue);

    // rehashes the tree
    this->initializeMerkleTree();
}

// Prints root of tree
void merkleTree::printRoot()
{
    cout << this->root->key << endl;
}

// Returns root of tree
Node* merkleTree::getRoot()
{
    return this->root;
}
