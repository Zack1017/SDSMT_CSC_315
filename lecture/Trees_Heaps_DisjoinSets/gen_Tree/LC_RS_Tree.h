//
// Created by kchri on 2/01/2025.
//
#ifndef GEN_TREE_LC_RS_TREE_H
#define GEN_TREE_LC_RS_TREE_H
#include <iostream>
#include <fstream>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

class Node {
// Cheating here and make the node public
public:
    char data;
    Node* leftChild;
    Node* rightSibling;

    explicit Node(char value) : data(value), leftChild(nullptr), rightSibling(nullptr) {}
};

class LC_RS_Tree {
private:
    Node* root;
    // Add child Node to a Node
    static Node *addChild(Node * n, char data);
    // Adds a sibling to a list with starting with n
    static Node *addSibling(Node *n, char data);
    // Helper function to find a node
    static Node *findNode(Node *root, char key);
    // Helper function to traverse a tree
    static void traverseTree(Node * root);
    // Helper method to create DOT-files
    void dotHelper(std::ofstream &myfile);

public:
    // Constructor
    LC_RS_Tree() : root(nullptr) {}
    ~LC_RS_Tree() = default;

    // We insert a root into an empty tree
    void insert(char value);
    // Insert a new node as child to key
    void insert(char key, char value);
    bool find(char key);
    // Different display methods
    void printLevelOrder();
    void printDot(const std::string& filename);
    bool graph(const std::string& filename);

};

#endif //GEN_TREE_LC_RS_TREE_H
