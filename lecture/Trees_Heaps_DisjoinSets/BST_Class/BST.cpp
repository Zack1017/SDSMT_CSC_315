//
// Created by kchri on 11/24/2024.
//
#include <iostream>
#include <queue>
#include <string>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include "BST.h"

// Constructor
BST::BST() {
    root = nullptr;
}
// Destructor
BST::~BST() {
    root = erase(root);
}

/* All the public methods for the BST Tree */
/* Method to insert a new node */
void BST::insert(int d) {
    root = insertNode(root, d);
}
/* Method to remove a node */
void BST::remove(int key) {
    deleteNode(root, key);
}
/* method to find a value in the tree */
bool BST::search(int x) {
    if(nullptr == find(root, x))
        return false;
    else
        return true;
}
/* Method to clear the tree */
void BST::clear() {
    root = erase(root);
}
/* Method to print the tree in in-order */
void BST::printTree() {
    std::cout << "{";
    inorderTree(root);
    std::cout << "\b\b}" << std::endl;
}
/* All the private methods and utility functions */
/* Recursive utility function to add a node */
BST::node* BST::insertNode(node* curr, int data) {
    if (nullptr == curr)
        return new node(data);

    if (curr->data >= data)
        curr->left = insertNode(curr->left, data);
    else
        curr->right = insertNode(curr->right, data);

    return curr;
}
/* Recursive utility function to remove a node */
BST::node* BST::deleteNode(node* &nd, int key) {
    // base case: the key is not found in the tree
    if (nullptr == nd) {
        std::cout << "Unable to delete " << key << std::endl;
        return nullptr;
    }
    // if the given key is less than the nd node, recur for the left subtree
    if (key < nd->data) {
        deleteNode(nd->left, key);
    }
    // if the given key is more than the nd node, recur for the right subtree
    else if (key > nd->data) {
        deleteNode(nd->right, key);
    }
    // key found
    else {
        std::cout << "Moved or deleted " << key << std::endl;
        // Case 1: node to be deleted has no children (it is a leaf node)
        if (nd->left == nullptr && nd->right == nullptr) {
            // deallocate the memory and update nd to null
            delete nd;
            nd = nullptr;
        }
        // Case 2: node to be deleted has one child
        // Note: as we already know it is not childless that means we only
        //  need to exclude two children, and not do an XOR.
        else if (!(nd->left && nd->right)) {
            // choose a child node
            node *child = (nd->left) ? nd->left : nd->right;
            node *curr = nd;
            // make child the nd
            nd = child;
            // deallocate the memory
            delete curr;
        }
        // Case 3: node to be deleted has two children
        else {
            // find its inorder predecessor node
            node *predecessor = findMaximumKey(nd->left);
            // copy value of the predecessor to the current node
            nd->data = predecessor->data;
            // recursively delete the predecessor. Note that the
            // predecessor will have at most one child (left child)
            deleteNode(nd->left, predecessor->data);
        }
    }
    return nd;
}
/* Utility function to erase all the keys in the tree */
BST::node* BST::erase(node* curr) {
    if(nullptr != curr) {
        erase(curr->left);
        erase(curr->right);
        delete curr;
    }
    return nullptr;
}
/* Utility function to traverse in-order */
void BST::inorderTree(node *curr) {
    if(nullptr != curr) {
        inorderTree(curr->left);
        std::cout << curr->data << ", ";
        inorderTree(curr->right);
    }
}
/* Utility function to find the node with a key value */
BST::node* BST::find(node* curr, int key) {
    if(nullptr == curr)
        return nullptr;
    else if(key < curr->data)
        return find(curr->left, key);
    else if(key > curr->data)
        return find(curr->right, key);
    else
        return curr;
}
/* Find the maximum key value in
 * the tree rooted at current */
BST::node* BST::findMaximumKey(node* curr) {
    while (nullptr != curr->right) {
        curr = curr->right;
    }
    return curr;
}
/* Utility function to create a graph in
 * png-format, using graphviz libraries */
bool BST::graph(const std::string& filename){
    std::queue<node*> Q;
    Q.push(root);
    // set up a graphviz context
    GVC_t *gvc = gvContext();
    // Create a simple digraph
    Agraph_t *g = agopen((char*)"g", Agdirected, nullptr);
    // It is a tree so maximum three nodes
    Agnode_t *ro;
    Agnode_t *le;
    Agnode_t *ri;
    // Iterate through all the nodes in the tree
    while (!Q.empty()) {
        // If the root of the subtree is not empty
        if (nullptr != Q.front()) {
            // Create a graph node for the root of the subtree
            ro = agnode(g, (char *) std::to_string(Q.front()->data).c_str(), 1);
            // Is there a left child?
            if (nullptr != Q.front()->left) {
                // Create a graph node for the left child
                le = agnode(g, (char *) std::to_string(Q.front()->left->data).c_str(), 1);
                // Create an edge from root to left child
                agedge(g, ro, le, nullptr, 1);
                // Push left child on the queue
                Q.push(Q.front()->left);
            }
            // Is there a right child?
            if (nullptr != Q.front()->right) {
                // Create a graph node for the right child
                ri = agnode(g, (char *) std::to_string(Q.front()->right->data).c_str(), 1);
                // Create an edge from root to right child
                agedge(g, ro, ri, nullptr, 1);
                // Push right child on the queue
                Q.push(Q.front()->right);
            }
            // Pop the root of the subtree off the queue
            Q.pop();
        }
    }
    // Use the directed graph layout engine
    gvLayout(gvc, g, "dot");
    // Output the graph in .png format
    gvRender(gvc, g, "png", fopen((filename+".png").c_str(), "w"));
    // Free layout data
    gvFreeLayout(gvc, g);
    // Free graph structures
    agclose(g);

    return (gvFreeContext(gvc));
}